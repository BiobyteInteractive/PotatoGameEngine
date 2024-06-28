#pragma once

#define DllExport __declspec( dllexport )

#include <filesystem>
#include <memory>
#include <vector>

class DllExport AssetImporter {
    public:
        AssetImporter() = default;
        ~AssetImporter() = default;
        virtual std::shared_ptr<std::vector<unsigned char>> ImportAsset(std::filesystem::path assetPath) = 0;
};