#pragma once

#ifndef DllExport
#ifdef DLLBuild
#define DllExport __declspec( dllexport )
#else
#define DllExport __declspec( dllimport )
#endif
#endif

#include <filesystem>
#include <memory>
#include <vector>

namespace Engine {
    class DllExport IAssetImporter {
        public:
            IAssetImporter() = default;
            ~IAssetImporter() = default;
            virtual std::shared_ptr<std::vector<std::byte>> ImportAsset(std::filesystem::path assetPath) = 0;
    };
}