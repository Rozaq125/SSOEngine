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

        /**
         * Core Function: Extracts raw binary data from the .sso bundle.
         * Returns a pointer to the data allocated in memory. 
         * User is responsible for freeing the memory if not handled by Raylib loaders.
         */
        inline unsigned char* LoadRawDataFromBundle(const std::string& bundlePath, const std::string& targetFile, int* dataSize) {
            std::ifstream file(bundlePath, std::ios::binary);
            if (!file) {
                TraceLog(LOG_ERROR, "SSO_PROVIDER: Failed to open bundle at %s", bundlePath.c_str());
                return nullptr;
            }

            AssetHeader header;
            file.read(reinterpret_cast<char*>(&header), sizeof(AssetHeader));

            // Validate SSO Signature
            if (std::memcmp(header.signature, "SSO ", 4) != 0) {
                TraceLog(LOG_ERROR, "SSO_PROVIDER: Invalid bundle signature!");
                file.close();
                return nullptr;
            }

            for (int i = 0; i < header.fileCount; ++i) {
                FileMetadata meta;
                file.read(reinterpret_cast<char*>(&meta), sizeof(FileMetadata));
                
                if (targetFile == meta.fileName) {
                    unsigned char* buffer = (unsigned char*)RL_MALLOC(meta.fileSize);
                    file.seekg(meta.offset);
                    file.read(reinterpret_cast<char*>(buffer), meta.fileSize);
                    file.close();
                    
                    *dataSize = (int)meta.fileSize;
                    TraceLog(LOG_INFO, "SSO_PROVIDER: Found and extracted %s (%d bytes)", targetFile.c_str(), *dataSize);
                    return buffer;
                }
            }

            TraceLog(LOG_WARNING, "SSO_PROVIDER: File '%s' not found in bundle", targetFile.c_str());
            file.close();
            return nullptr;
        }

        // --- Resource Specific Loaders ---

        // Load 2D Textures (.png, .jpg, .tga)
        inline Texture2D LoadTextureFromBundle(const std::string& bPath, const std::string& fName) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) return { 0 };

            Image img = LoadImageFromMemory(GetFileExtension(fName.c_str()), data, size);
            Texture2D tex = LoadTextureFromImage(img);
            UnloadImage(img);
            RL_FREE(data); 
            return tex;
        }

        // Load Custom Fonts (.ttf, .otf)
        inline Font LoadFontFromBundle(const std::string& bPath, const std::string& fName, int fontSize) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) return GetFontDefault();

            Font font = LoadFontFromMemory(GetFileExtension(fName.c_str()), data, size, fontSize, NULL, 0);
            RL_FREE(data);
            return font;
        }

        // Load Audio Waves for Sound Effects (.wav, .ogg)
        inline Wave LoadWaveFromBundle(const std::string& bPath, const std::string& fName) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) return { 0 };

            Wave wave = LoadWaveFromMemory(GetFileExtension(fName.c_str()), data, size);
            RL_FREE(data);
            return wave;
        }

        // Load Music Streams (.mp3, .ogg)
        // NOTE: Memory must remain allocated for the duration of the stream.
        inline Music LoadMusicFromBundle(const std::string& bPath, const std::string& fName) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) return { 0 };

            return LoadMusicStreamFromMemory(GetFileExtension(fName.c_str()), data, size);
        }

        // Load 3D Models (.obj, .gltf, .iqm) - NEW 3D SUPPORT
        inline Model LoadModelFromBundle(const std::string& bPath, const std::string& fName) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) return { 0 };

            Model model = LoadModelFromMemory(GetFileExtension(fName.c_str()), data, size);
            RL_FREE(data);
            return model;
        }

        // Load 3D Meshes for custom processing
        inline Mesh LoadMeshFromBundle(const std::string& bPath, const std::string& fName) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) return { 0 };

            Mesh mesh = LoadMeshFromMemory(GetFileExtension(fName.c_str()), data, size);
            RL_FREE(data);
            return mesh;
        }

        // Load 3D Materials
        inline Material LoadMaterialFromBundle(const std::string& bPath, const std::string& fName) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) return LoadMaterialDefault();

            Material mat = LoadMaterialDefault();
            // Parse custom material file format if needed
            // For now, return default material
            
            RL_FREE(data);
            return mat;
        }

        // Load 3D Animations
        inline ModelAnimation LoadAnimationFromBundle(const std::string& bPath, const std::string& fName, int* animCount) {
            int size = 0;
            unsigned char* data = LoadRawDataFromBundle(bPath, fName, &size);
            if (!data) {
                *animCount = 0;
                return { 0 };
            }

            ModelAnimation* anims = LoadModelAnimationsFromMemory(GetFileExtension(fName.c_str()), data, size, animCount);
            RL_FREE(data);
            
            if (*animCount > 0) {
                return anims[0]; // Return first animation
            }
            return { 0 };
        }

        // Load Raw Video Buffer (.mp4, .mkv)
        inline unsigned char* LoadVideoDataFromBundle(const std::string& bPath, const std::string& fName, int* size) {
            return LoadRawDataFromBundle(bPath, fName, size);
        }
    }
}

#endif