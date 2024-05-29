#pragma once
#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#define DllExport __declspec( dllexport )

#include <efsw/efsw.hpp>
#include <sqlite3.h>

#include <memory>
#include <vector>

DllExport void InitAssetManager();

typedef struct Asset {

} Asset;

class FileUpdateListener : public efsw::FileWatchListener {
    public:
        void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) override;
};

class DllExport AssetDatabase {
    public:
        AssetDatabase(std::string& directory);
        ~AssetDatabase();

        std::unique_ptr<Asset> GetAssetById(int id);
        std::unique_ptr<Asset> GetAssetByPath(std::string path);
        std::unique_ptr<std::vector<Asset>> GetAssetsByDirectory(std::string directory);
        std::unique_ptr<std::vector<Asset>> GetAssetsByExtension(std::string extension);
    private:
        sqlite3* asset_db;

        FileUpdateListener* file_update_listener;
        efsw::FileWatcher* file_watcher;
        efsw::WatchID watch_id;
};
#endif