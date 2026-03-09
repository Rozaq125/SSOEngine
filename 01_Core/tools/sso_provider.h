#ifndef SSO_PROVIDER_H
#define SSO_PROVIDER_H

#include "raylib.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

namespace SSO {
    namespace Provider {

        struct AssetHeader {
            char signature[4];
            int version;
            int fileCount;
        };

        struct FileMetadata {
            char fileName[64];
            long long fileSize;
            long long offset;
        };

        // Memuat Texture langsung dari file .sso tanpa ekstrak ke folder
        inline Texture2D LoadTextureFromBundle(const std::string& bundlePath, const std::string& targetFile) {
            std::ifstream file(bundlePath, std::ios::binary);
            if (!file) {
                TraceLog(LOG_ERROR, "SSO_PROVIDER: Could not open bundle %s", bundlePath.c_str());
                return { 0 };
            }

            // 1. Read Header
            AssetHeader header;
            file.read(reinterpret_cast<char*>(&header), sizeof(AssetHeader));

            if (std::memcmp(header.signature, "SSO ", 4) != 0) {
                TraceLog(LOG_ERROR, "SSO_PROVIDER: Invalid .sso signature!");
                return { 0 };
            }

            // 2. Search Metadata for the target file
            FileMetadata targetMeta;
            bool found = false;
            for (int i = 0; i < header.fileCount; ++i) {
                FileMetadata meta;
                file.read(reinterpret_cast<char*>(&meta), sizeof(FileMetadata));
                if (targetFile == meta.fileName) {
                    targetMeta = meta;
                    found = true;
                    break;
                }
            }

            if (!found) {
                TraceLog(LOG_ERROR, "SSO_PROVIDER: File %s not found in bundle!", targetFile.c_str());
                return { 0 };
            }

            // 3. Read Binary Data from Offset
            std::vector<unsigned char> buffer(targetMeta.fileSize);
            file.seekg(targetMeta.offset);
            file.read(reinterpret_cast<char*>(buffer.data()), targetMeta.fileSize);
            file.close();

            // 4. Convert Binary to Raylib Texture
            // Get file extension for Raylib loader
            std::string ext = targetFile.substr(targetFile.find_last_of("."));
            Image img = LoadImageFromMemory(ext.c_str(), buffer.data(), (int)targetMeta.fileSize);
            Texture2D tex = LoadTextureFromImage(img);
            UnloadImage(img); // Clean up CPU memory

            TraceLog(LOG_INFO, "SSO_PROVIDER: Successfully loaded %s from bundle", targetFile.c_str());
            return tex;
        }
    }
}

#endif