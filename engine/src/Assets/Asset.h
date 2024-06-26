#pragma once
#ifndef ASSET_H
#define ASSET_H

#define DllExport __declspec( dllexport )

#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class DllExport Asset {
    public:
        Asset(size_t id, std::string path, std::string directory, std::string extension, bool deleted);
        ~Asset() = default;

        void LoadAsset();
        void UnloadAsset();
    private:
        size_t m_Id;
        std::string m_Directory;
        std::string m_Extension;
        bool m_Deleted;
    public:
        std::shared_ptr<std::vector<std::byte>> m_Blob;
        std::string m_Path;
};

#endif