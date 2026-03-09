#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstring>

namespace fs = std::filesystem;

struct AssetHeader {
    char signature[4] = {'S', 'S', 'O', ' '}; 
    int version = 1;                         
    int fileCount = 0;                       
};

struct FileMetadata {
    char fileName[64];  
    long long fileSize; 
    long long offset;   
};

int main() {
    // Paths are now relative to the project structure
    // We look into 01_Core/assets and output to 01_Core/build
    std::string assetFolder = "../01_Core/assets";
    std::string outputFile = "../01_Core/build/assets.sso";

    std::cout << "==========================================" << std::endl;
    std::cout << "   SSOEngine Asset Packer v1.0 (English)  " << std::endl;
    std::cout << "==========================================" << std::endl;

    if (!fs::exists(assetFolder)) {
        std::cerr << "[FATAL ERROR] Source folder '" << assetFolder << "' not found!" << std::endl;
        std::cerr << "Ensure assets are located in: 01_Core/assets/" << std::endl;
        return 1;
    }

    std::vector<fs::path> files;
    for (const auto& entry : fs::directory_iterator(assetFolder)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }

    AssetHeader header;
    header.fileCount = static_cast<int>(files.size());

    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "[FATAL ERROR] Could not create " << outputFile << std::endl;
        return 1;
    }

    // 1. Write Placeholder Header
    out.write(reinterpret_cast<char*>(&header), sizeof(AssetHeader));

    // 2. Prepare Metadata
    std::vector<FileMetadata> metadataList;
    long long currentOffset = sizeof(AssetHeader) + (sizeof(FileMetadata) * header.fileCount);

    for (const auto& filePath : files) {
        FileMetadata meta;
        std::string name = filePath.filename().string();
        
        std::memset(meta.fileName, 0, 64);
        name.copy(meta.fileName, name.size() > 63 ? 63 : name.size());

        meta.fileSize = fs::file_size(filePath);
        meta.offset = currentOffset;
        
        metadataList.push_back(meta);
        currentOffset += meta.fileSize;
    }

    // 3. Write Metadata Table
    for (const auto& meta : metadataList) {
        out.write(reinterpret_cast<const char*>(&meta), sizeof(FileMetadata));
    }

    // 4. Write Binary Data
    for (size_t i = 0; i < files.size(); ++i) {
        std::ifstream in(files[i], std::ios::binary);
        if (!in) {
            std::cerr << "[ERROR] Could not read file: " << files[i] << std::endl;
            continue;
        }
        std::vector<char> buffer((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        
        out.write(buffer.data(), buffer.size());
        std::cout << "[PACKED] " << metadataList[i].fileName << " (" << metadataList[i].fileSize << " bytes)" << std::endl;
    }

    out.close();
    
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "[SUCCESS] Bundle created at: " << outputFile << std::endl;
    std::cout << "CRITICAL WARNING: DO NOT MODIFY .SSO FILES MANUALLY!" << std::endl;
    std::cout << "==========================================" << std::endl;

    return 0;
}