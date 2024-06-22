#include "Asset.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cstddef>

Asset::Asset(size_t id, std::string path, std::string directory, std::string extension, bool deleted) {
    this->m_Id = id;
    this->m_Path = path;
    this->m_Directory = directory;
    this->m_Extension = extension;
    this->m_Deleted = deleted;
}

void Asset::LoadAsset() {
    // Open the file in binary mode
    std::ifstream file(this->m_Path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file: " + this->m_Path);
    }

    // Determine the file size
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file contents into the vector
    if (!file.read(reinterpret_cast<char*>(this->m_Blob->data()), fileSize)) {
        throw std::runtime_error("Error reading file: " + this->m_Path);
    }
}

void Asset::UnloadAsset() {
    this->m_Blob.reset();
}