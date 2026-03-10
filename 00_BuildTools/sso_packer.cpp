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
    // Path tetep sama sesuai struktur industrial lu
    std::string assetFolder = "../01_Core/assets";
    std::string outputFile = "../01_Core/build/assets.sso";

    std::cout << "==========================================" << std::endl;
    std::cout << "   SSOEngine Asset Packer v1.1 (Recursive) " << std::endl;
    std::cout << "==========================================" << std::endl;

    if (!fs::exists(assetFolder)) {
        std::cerr << "[FATAL ERROR] Source folder '" << assetFolder << "' not found!" << std::endl;
        std::cerr << "Ensure assets are located in: 01_Core/assets/" << std::endl;
        return 1;
    }

    // --- FITUR BARU: RECURSIVE SCAN ---
    // Tetap pake vector files lu, tapi sekarang masuk ke sub-folder
    std::vector<fs::path> files;
    for (const auto& entry : fs::recursive_directory_iterator(assetFolder)) {
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

    // 2. Prepare Metadata (LOGIKA OFFSET TETEP SAMA)
    std::vector<FileMetadata> metadataList;
    long long currentOffset = sizeof(AssetHeader) + (sizeof(FileMetadata) * header.fileCount);

    for (const auto& filePath : files) {
        FileMetadata meta;
        
        // --- FITUR BARU: RELATIVE PATH ---
        // Biar tersimpan "font/vampire.ttf" bukan cuma "vampire.ttf"
        std::string relativePath = fs::relative(filePath, assetFolder).generic_string();
        
        std::memset(meta.fileName, 0, 64);
        relativePath.copy(meta.fileName, relativePath.size() > 63 ? 63 : relativePath.size());

        meta.fileSize = fs::file_size(filePath);
        meta.offset = currentOffset;
        
        metadataList.push_back(meta);
        currentOffset += meta.fileSize;
    }

    // 3. Write Metadata Table
    for (const auto& meta : metadataList) {
        out.write(reinterpret_cast<const char*>(&meta), sizeof(FileMetadata));
    }

    // 4. Write Binary Data (LOGIKA BUFFER TETEP SAMA)
    for (size_t i = 0; i < files.size(); ++i) {
        std::ifstream in(files[i], std::ios::binary);
        if (!in) {
            std::cerr << "[ERROR] Could not read file: " << files[i] << std::endl;
            continue;
        }
        
        // Tetap pake istreambuf_iterator sesuai code asli lu
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