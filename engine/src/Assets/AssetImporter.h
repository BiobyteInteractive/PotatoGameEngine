#pragma once
#include <filesystem>
#ifndef ASSET_IMPORTER_H
#define ASSET_IMPORTER_H

#define DllExport __declspec( dllexport )

#include <memory>
#include <vector>

class DllExport AssetImporter {
    public:
        AssetImporter();
        ~AssetImporter();
        std::shared_ptr<std::vector<unsigned char>> ImportAsset(std::filesystem::path assetPath);
};

#endif