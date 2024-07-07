#pragma once

#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#include <efsw/efsw.hpp>
#include <sqlite3.h>

#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Asset.h"

namespace Engine {
    class DllExport AssetDatabase : public efsw::FileWatchListener {
        public:
            AssetDatabase(std::string directory);
            ~AssetDatabase();

            void handleFileAction(efsw::WatchID watchid, const std::string& dir, const std::string& filename, efsw::Action action, std::string oldFilename) override;
            
            std::vector<size_t> SelectAssets(std::string query, size_t argc, ...);
            std::shared_ptr<Asset> GetAssetByID(size_t id);
            std::string GetWatchedDirectory();
            

        private:
            friend int callback(void* NotUsed, int argc, char** argv, char** azColName);
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
            std::unordered_map<size_t, std::shared_ptr<Asset>> m_AssetCache;
    };
}