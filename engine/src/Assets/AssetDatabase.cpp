#include "efsw/efsw.hpp"
#include <sqlite3.h>

#include <cstdarg>
#include <cstddef>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Asset.h"
#include "AssetDatabase.h"

std::string normalizePath(const std::string& pathString) {
    std::filesystem::path pathObj(pathString);
    pathObj.make_preferred();
    pathObj = pathObj.lexically_normal();
    if (!pathObj.empty() && pathObj.string().back() == std::filesystem::path::preferred_separator) {
        return pathObj.string().substr(0, pathObj.string().size() - 1);
    }
    return pathObj.string();
}

int callback(void* NotUsed, int argc, char** argv, char** azColName){
    return 0;
}

AssetDatabase::AssetDatabase(std::string directory) {
    char* zErrMsg = 0;
    int rc;
    const char* sql;

    this->m_WatchedDirectory = directory;

    rc = sqlite3_open("asset.db", &m_AssetDb);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        abort();
    } 

    sql = "CREATE TABLE IF NOT EXISTS assets(" \
          "ID        INTEGER PRIMARY KEY AUTOINCREMENT," \
          "PATH      TEXT                NOT NULL," \
          "DIRECTORY TEXT                NOT NULL," \
          "EXTENSION TEXT                NOT NULL," \
          "DELETED   BOOL                NOT NULL DEFAULT FALSE," \
          "SCANNED   BOOL                NOT NULL DEFAULT TRUE," \
          "UNIQUE(PATH, DIRECTORY)" \
          ");";

    rc = sqlite3_exec(m_AssetDb, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        abort();
    }

    this->Cleanup();

    // Initialize the file watcher
    this->m_FileWatcher = new efsw::FileWatcher();
    this->m_WatchId = this->m_FileWatcher->addWatch(directory, this, true);

    this->m_FileWatcher->watch();

    this ->ScanFolder(directory);
}

AssetDatabase::~AssetDatabase() {
    this->m_FileWatcher->removeWatch(this->m_WatchId);
    this->Cleanup();    
}

std::vector<size_t> AssetDatabase::SelectAssets(std::string query, size_t argc, ...) {
    va_list ap;
    va_start(ap, argc);

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(this->m_AssetDb, query.c_str(), -1, &stmt, nullptr);

    for(size_t i = 0; i < argc; ++i) {
        sqlite3_bind_text(stmt, 1, va_arg(ap, char*), -1, SQLITE_STATIC);
    }

    std::vector<size_t> idVector;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        idVector.push_back((size_t)id);

        if (this->m_AssetCache.find(id) == this->m_AssetCache.end())
            continue;
        
        std::string path((char*)sqlite3_column_text(stmt, 1));
        std::string directory((char*)sqlite3_column_text(stmt, 3));
        std::string extension((char*)sqlite3_column_text(stmt, 2));

        Asset asset(
            (size_t)id,
            path,
            directory,
            extension,
            (bool)sqlite3_column_int(stmt, 4)
        );

        std::shared_ptr<Asset> asset_ptr(&asset);
        this->m_AssetCache.insert_or_assign((size_t)id, asset_ptr);
    }

    sqlite3_finalize(stmt);
    return idVector;
}

std::shared_ptr<Asset> AssetDatabase::GetAssetsByID(size_t id) {
    std::unordered_map<size_t, std::shared_ptr<Asset>>::const_iterator asset = this->m_AssetCache.find(id);
        if (asset != this->m_AssetCache.end())
        return asset->second;

    this->SelectAssets("SELECT * FROM assets WHERE ID = ?", 1, std::to_string(id).c_str());

    asset = this->m_AssetCache.find(id);
    if (asset != this->m_AssetCache.end())
        return asset->second;

    return NULL;
}

std::string AssetDatabase::GetWatchedDirectory() {
    return this->m_WatchedDirectory;
}

void AssetDatabase::Cleanup() { 
    char* zErrMsg = 0;
    int rc;
    const char* sql = "DELETE FROM assets WHERE DELETED = TRUE";
    
    rc = sqlite3_exec(m_AssetDb, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        abort();
    }
}

void AssetDatabase::InsertAsset(std::string directory, std::string filename) {
    if (std::filesystem::is_directory(directory + filename)) {
        return;
    }

    std::filesystem::path file_path = std::filesystem::path(filename);

    std::string extension = file_path.extension().string();
    std::string relative_directory = normalizePath(std::filesystem::relative(directory, std::filesystem::current_path() / "assets").string());

    int rc;

    // Use parameter placeholders ('?') to prevent SQL injection
    const char* sql = "INSERT INTO assets (PATH, DIRECTORY, EXTENSION, DELETED) "
                      "VALUES (?, ?, ?, 0) "
                      "ON CONFLICT(PATH, DIRECTORY) DO UPDATE SET DELETED = FALSE, SCANNED = TRUE;";

    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(m_AssetDb, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        abort();
    }

    // Bind the parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, filename.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, relative_directory.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, extension.c_str(), -1, SQLITE_STATIC);

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        sqlite3_finalize(stmt);
        abort();
    }

    // Clean up
    sqlite3_finalize(stmt);
}

void AssetDatabase::UpdateAsset(std::string directory, std::string filename, std::string old_filename) {
    if (std::filesystem::is_directory(directory + filename)) {
        return;
    }

    std::filesystem::path file_path = std::filesystem::path(filename);


    std::string extension = file_path.extension().string();
    std::string relative_directory = normalizePath(std::filesystem::path(filename).remove_filename().string());
    std::string old_relative_directory = normalizePath(std::filesystem::path(old_filename).remove_filename().string());
    filename = std::filesystem::path(filename).filename().string();
    old_filename = std::filesystem::path(old_filename).filename().string();

    int rc;

    // Use parameter placeholders ('?') to prevent SQL injection
    const char* sql = "UPDATE assets " \
                  "SET PATH = ?, " \
                  "DIRECTORY = ?, " \
                  "EXTENSION = ?, " \
                  "DELETED = FALSE " \
                  "WHERE DIRECTORY = ? " \
                  "AND PATH = ?;";

    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(m_AssetDb, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        abort();
    }

    // Bind the parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, filename.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, relative_directory.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, extension.c_str(), -1, SQLITE_STATIC);
    
    sqlite3_bind_text(stmt, 4, old_relative_directory.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, old_filename.c_str(), -1, SQLITE_STATIC);

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        sqlite3_finalize(stmt);
        abort();
    } 

    // Clean up
    sqlite3_finalize(stmt);
}

void AssetDatabase::DeleteAsset(std::string directory, std::string filename) {
    if (std::filesystem::is_directory(directory + filename)) {
        return;
    }

    std::filesystem::path file_path = std::filesystem::path(filename);

    std::string extension = file_path.extension().string();
    std::string relative_directory = normalizePath(std::filesystem::relative(directory, std::filesystem::current_path() / "assets").string());

    int rc;

    // Use parameter placeholders ('?') to prevent SQL injection
    const char* sql = "UPDATE assets SET DELETED = TRUE WHERE PATH = ? AND DIRECTORY = ?";

    // Prepare the SQL statement
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(m_AssetDb, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        abort();
    }

    // Bind the parameters to the SQL statement
    sqlite3_bind_text(stmt, 1, filename.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, relative_directory.c_str(), -1, SQLITE_STATIC);

    // Execute the SQL statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        sqlite3_finalize(stmt);
        abort();
    } 

    // Clean up
    sqlite3_finalize(stmt);
}

void AssetDatabase::handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) {
    switch ( action ) {
        case efsw::Actions::Add:
            this->InsertAsset(dir, filename);
            break;
        case efsw::Actions::Delete:
            this->DeleteAsset(dir, filename);
            break;
        case efsw::Actions::Modified:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified" << std::endl;
            break;
        case efsw::Actions::Moved:
            this->UpdateAsset(dir, filename, oldFilename);
            break;
        default:
            std::cout << "Should never happen!" << std::endl;
            abort();
    }
}

void AssetDatabase::ScanFolder(std::string folderPath) {
    for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
        if (std::filesystem::is_directory(entry.path().string())) {
            continue;
        }

        if (std::filesystem::is_regular_file(entry)) {
            std::string dir = entry.path().parent_path().string();
            std::string filename = entry.path().filename().string();
            this->InsertAsset(dir, filename);
        }
    }

    // Delete the files not scanned
    int rc;

    const char* sql = "UPDATE assets SET DELETED = TRUE WHERE SCANNED = FALSE;";

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(m_AssetDb, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        abort();
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        sqlite3_finalize(stmt);
        abort();
    } 

    sqlite3_finalize(stmt);

    // Set scanned to false on all files
    this->ResetScans();
}

void AssetDatabase::ResetScans() {
    int rc;

    const char* sql = "UPDATE assets SET SCANNED = FALSE WHERE SCANNED = TRUE;";

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(m_AssetDb, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        abort();
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_AssetDb) << std::endl;
        sqlite3_finalize(stmt);
        abort();
    } 

    sqlite3_finalize(stmt);
}