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
        Asset();
        ~Asset();

        void LoadAsset();
        void UnloadAsset();
    private:
        void ImportAsset();
    public:
         size_t m_Id;
         std::string m_Path;
         std::string m_Directory;
         std::string m_Extension;
         bool m_Deleted;

        std::shared_ptr<std::vector<unsigned char>> m_Blob;
};

#endif