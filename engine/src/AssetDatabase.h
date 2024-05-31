#pragma once
#include <string>
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

class DllExport AssetDatabase : public efsw::FileWatchListener {
    public:
        AssetDatabase(std::string directory);
        ~AssetDatabase();

        void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) override;

        std::unique_ptr<Asset> GetAssetById(int id);
        std::unique_ptr<Asset> GetAssetByPath(std::string path);
        std::unique_ptr<std::vector<Asset>> GetAssetsByDirectory(std::string directory);
        std::unique_ptr<std::vector<Asset>> GetAssetsByExtension(std::string extension);

    private:
        void InsertAsset(std::string directory, std::string filename);
        void UpdateAsset(std::string directory, std::string filename, std::string old_filename);
        void DeleteAsset(std::string directory, std::string filename);
        void Cleanup();
        
    private:
        sqlite3* asset_db;
        efsw::FileWatcher* file_watcher;
        efsw::WatchID watch_id;
};
#endif