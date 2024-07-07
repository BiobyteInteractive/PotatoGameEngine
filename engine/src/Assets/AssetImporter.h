#pragma once

#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif

#include <filesystem>
#include <memory>
#include <vector>

namespace Engine {
    class DllExport AssetImporter {
        public:
            AssetImporter() = default;
            ~AssetImporter() = default;
            virtual std::shared_ptr<std::vector<unsigned char>> ImportAsset(std::filesystem::path assetPath) = 0;
    };
}