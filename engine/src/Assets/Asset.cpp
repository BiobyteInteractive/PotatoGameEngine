#include "Asset.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstddef>

namespace Engine {
    Asset::Asset(size_t id, std::string path, std::string directory, std::string extension, bool deleted) {
        this->m_Id = id;
        this->m_Path = path;
        this->m_Directory = directory;
        this->m_Extension = extension;
        this->m_Deleted = deleted;

        this->m_Blob = std::make_shared<std::vector<std::byte>>();
    }

    void Asset::LoadAsset() {
        std::ifstream file(this->m_Path, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Could not open file: " + this->m_Path);
        }

        file.seekg(0, std::ios::end);
        std::streamsize fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        if (fileSize <= 0) {
            throw std::runtime_error("File size is zero or an error occurred: " + this->m_Path);
        }

        // Assuming m_Blob is a std::vector or similar container
        if (!this->m_Blob) {
            throw std::runtime_error("m_Blob is not initialized");
        }

        if (this->m_Blob->size() < static_cast<size_t>(fileSize)) {
            this->m_Blob->resize(fileSize);
        }

        if (!file.read(reinterpret_cast<char*>(this->m_Blob->data()), fileSize)) {
            throw std::runtime_error("Error reading file: " + this->m_Path);
        }
    }

    void Asset::UnloadAsset() {
        this->m_Blob.reset();
    }
}