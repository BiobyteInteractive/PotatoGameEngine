#include "AssetDatabase.h"

#include "efsw/efsw.hpp"
#include <sqlite3.h>

#include <iostream>

sqlite3* asset_db;

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    for(int i = 0; i<argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

AssetDatabase::AssetDatabase(std::string directory) {
    // Initialize SQLite3 database
    char* zErrMsg = 0;
    int rc;
    const char* sql;

    rc = sqlite3_open("asset.db", &asset_db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(asset_db) << std::endl;
        abort();
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    sql = "CREATE TABLE IF NOT EXISTS assets(" \
          "ID        INT  PRIMARY KEY NOT NULL," \
          "PATH      TEXT             NOT NULL," \
          "DIRECTORY TEXT             NOT NULL," \
          "EXTENSION TEXT             NOT NULL," \
          "DELETED   BOOL             NOT NULL DEFAULT(FALSE)" \
          ");";

    rc = sqlite3_exec(asset_db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        abort();
    } else {
        std::cout << "Records created successfully" << std::endl;
    }

    // Initialize the file watcher
    this->file_watcher = new efsw::FileWatcher();
    this->file_update_listener = new FileUpdateListener();

    this->watch_id = this->file_watcher->addWatch(directory, this->file_update_listener, true);
    this->file_watcher->watch();
}

AssetDatabase::~AssetDatabase() {
    this->file_watcher->removeWatch(this->watch_id);
    
    char* zErrMsg = 0;
    int rc;
    const char* sql = "DELETE * FROM assets WHERE DELETED = TRUE";
    
    rc = sqlite3_exec(asset_db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        abort();
    } else {
        std::cout << "Asset Database cleanup successful" << std::endl;
    }
}

void FileUpdateListener::handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) {
    switch ( action ) {
        case efsw::Actions::Add:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Added" << std::endl;
            break;
        case efsw::Actions::Delete:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Delete" << std::endl;
            break;
        case efsw::Actions::Modified:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Modified" << std::endl;
            break;
        case efsw::Actions::Moved:
            std::cout << "DIR (" << dir << ") FILE (" << filename << ") has event Moved from (" << oldFilename << ")" << std::endl;
            break;
        default:
            std::cout << "Should never happen!" << std::endl;
            abort();
    }
}