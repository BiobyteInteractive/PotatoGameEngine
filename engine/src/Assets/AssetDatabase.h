#pragma once
#ifndef ASSET_DATABASE_H
#define ASSET_DATABASE_H

#define DllExport __declspec( dllexport )

#include <efsw/efsw.hpp>
#include <sqlite3.h>

#include <memory>
#include <string>

#include "Asset.h"

class DllExport AssetDatabase : public efsw::FileWatchListener {
    public:
        AssetDatabase(std::string directory);
        ~AssetDatabase();

        void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) override;

        std::shared_ptr<std::vector<Asset>> GetAssets(std::string query);
        std::string GetWatchedDirectory();

    private:
        void InsertAsset(std::string directory, std::string filename);
        void UpdateAsset(std::string directory, std::string filename, std::string old_filename);
        void DeleteAsset(std::string directory, std::string filename);
        void ResetScans();
        void Cleanup();
        void ScanFolder(std::string folderPath);
        
    private:
        std::string m_WatchedDirectory;
        sqlite3* m_AssetDb;
        efsw::FileWatcher* m_FileWatcher;
        efsw::WatchID m_WatchId;
};
#endif