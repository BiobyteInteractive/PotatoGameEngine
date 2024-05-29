#include "AssetDatabase.h"

#include <iostream>
#include <sqlite3.h>

sqlite3* asset_db;

int InitAssetDatabase();

void InitAssetManager() {
    while (InitAssetDatabase()) {}
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    for(int i = 0; i<argc; i++){
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int InitAssetDatabase() {
    char* zErrMsg = 0;
    int rc;
    const char* sql;

    rc = sqlite3_open("asset.db", &asset_db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(asset_db) << std::endl;
        return 1;
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
        return 1;
    } else {
        std::cout << "Records created successfully" << std::endl;
    }

    return 0;
}

class FileWatcher : public efsw::FileWatchListener {
    public:
        void handleFileAction( efsw::WatchID watchid, const std::string& dir,
                               const std::string& filename, efsw::Action action,
                               std::string oldFilename) override {
            switch (action) {
                case efsw::Actions::Add:
                    break;
                case efsw::Actions::Modified:
                    break;
                case efsw::Actions::Moved:
                    break;
                case efsw::Actions::Delete:
                    break;
                default:
                    break;
            }
        }
};