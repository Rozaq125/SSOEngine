#ifndef SSO_3D_H
#define SSO_3D_H

#include "raylib.h"
#include "raymath.h"
#include "tools/sso_provider.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace SSO {
    namespace ThreeD {
        
        // Model Management System
        struct ModelCache {
            std::unordered_map<std::string, Model> models;
            
            inline Model Load(const std::string& path) {
                auto it = models.find(path);
                if (it != models.end()) {
                    return it->second;
                }
                
                Model model = LoadModel(path.c_str());
                models[path] = model;
                return model;
            }
            
            inline void Unload(const std::string& path) {
                auto it = models.find(path);
                if (it != models.end()) {
                    UnloadModel(it->second);
                    models.erase(it);
                }
            }
            
            inline void UnloadAll() {
                for (auto& pair : models) {
                    UnloadModel(pair.second);
                }
                models.clear();
            }
        };
        
        inline static ModelCache modelCache;
        
        // Model// Shader Management
        inline Shader LoadShaderFromBundle(const std::string& bPath, const std::string& fName) {
            // Create hardcoded shader with proper vertex shader
            const char* vertexShaderCode = R"(
                #version 330
                in vec3 vertexPosition;
                in vec3 vertexNormal;
                in vec2 vertexTexCoord;
                in vec4 vertexColor;
                out vec3 fragPos;
                out vec3 normal;
                out vec2 texCoord;
                out vec4 fragColor;
                
                uniform mat4 mvp;
                uniform mat4 model;
                
                void main() {
                    fragPos = vertexPosition;
                    normal = vertexNormal;
                    texCoord = vertexTexCoord;
                    fragColor = vertexColor;
                    gl_Position = mvp * vec4(vertexPosition, 1.0);
                }
            )";
            
            const char* fragmentShaderCode = R"(
                #version 330
                in vec3 fragPos;
                in vec3 normal;
                in vec2 texCoord;
                in vec4 fragColor;
                out vec4 finalColor;
                
                uniform vec3 lightPos;
                uniform vec3 lightColor;
                uniform vec3 viewPos;
                uniform vec4 objectColor;
                uniform float time;
                uniform float effectType;
                
                void main() {
                    vec3 norm = normalize(normal);
                    vec3 lightDir = normalize(lightPos - fragPos);
                    float diff = max(dot(norm, lightDir), 0.0);
                    
                    vec3 ambient = 0.3 * lightColor;
                    vec3 diffuse = diff * lightColor;
                    vec3 lighting = (ambient + diffuse) * fragColor.rgb;
                    
                    // VERY VISIBLE effects based on type
                    if (effectType == 1.0) {
                        // BLOOM - Make everything super bright and warm
                        lighting *= 2.0; // Double brightness
                        lighting.r *= 1.5; // Very red tint
                        lighting.g *= 1.2;
                        lighting.b *= 0.5; // Less blue
                        // Add pulsing
                        float pulse = sin(time * 3.0) * 0.3 + 1.0;
                        lighting *= pulse;
                    } else if (effectType == 2.0) {
                        // CRT - Strong scanlines
                        float scanline = sin(gl_FragCoord.y * 8.0) * 0.4 + 0.6;
                        lighting *= scanline;
                        // Strong color shift
                        lighting.r *= 1.3;
                        lighting.b *= 0.7;
                        // Add flicker
                        float flicker = sin(time * 60.0) * 0.1 + 0.9;
                        lighting *= flicker;
                    } else if (effectType == 3.0) {
                        // GRAYSCALE - Complete black and white
                        float gray = dot(lighting, vec3(0.299, 0.587, 0.114));
                        lighting = vec3(gray, gray, gray);
                        // Add film grain
                        float grain = fract(sin(dot(gl_FragCoord.xy, vec2(12.9898, 78.233))) * 43758.5453);
                        lighting += grain * 0.1;
                    } else if (effectType == 4.0) {
                        // BLUR - Strong vignette effect
                        vec2 uv = gl_FragCoord.xy / vec2(1280, 720);
                        float dist = distance(uv, vec2(0.5));
                        if (dist > 0.2) {
                            float blurAmount = (dist - 0.2) * 3.0;
                            lighting *= max(0.1, 1.0 - blurAmount);
                        }
                        // Add chromatic aberration
                        lighting.r += dist * 0.2;
                        lighting.b -= dist * 0.2;
                    }
                    
                    finalColor = vec4(lighting, fragColor.a);
                }
            )";
            
            Shader shader = LoadShaderFromMemory(vertexShaderCode, fragmentShaderCode);
            return shader;
        }
        
        inline Shader LoadShaderFromFile(const std::string& path) {
            return LoadShader("", ""); // Default vertex shader
        }
        
        inline void UnloadShader(const std::string& path) {
            // Implementation for shader unloading
        }
        
        // Shader Effects
        inline void ApplyBasicLight(Shader shader, Vector3 lightPos, Vector3 lightColor, Vector3 viewPos) {
            SetShaderValue(shader, GetShaderLocation(shader, "lightPos"), &lightPos, SHADER_UNIFORM_VEC3);
            SetShaderValue(shader, GetShaderLocation(shader, "lightColor"), &lightColor, SHADER_UNIFORM_VEC3);
            SetShaderValue(shader, GetShaderLocation(shader, "viewPos"), &viewPos, SHADER_UNIFORM_VEC3);
            float effectType = 0.0f; // Basic light
            SetShaderValue(shader, GetShaderLocation(shader, "effectType"), &effectType, SHADER_UNIFORM_FLOAT);
        }
        
        inline void ApplyBloomGlow(Shader shader, float time, Vector2 resolution, float threshold = 1.0f, float intensity = 1.5f) {
            SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);
            float effectType = 1.0f; // Bloom glow
            SetShaderValue(shader, GetShaderLocation(shader, "effectType"), &effectType, SHADER_UNIFORM_FLOAT);
        }
        
        inline void ApplyRetroCRT(Shader shader, float time, Vector2 resolution, float curve = 0.1f, float scanline = 0.15f) {
            SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);
            float effectType = 2.0f; // Retro CRT
            SetShaderValue(shader, GetShaderLocation(shader, "effectType"), &effectType, SHADER_UNIFORM_FLOAT);
        }
        
        inline void ApplyGrayscaleSepia(Shader shader, float time, Vector2 resolution, float amount = 1.0f, int type = 0) {
            SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);
            float effectType = 3.0f; // Grayscale
            SetShaderValue(shader, GetShaderLocation(shader, "effectType"), &effectType, SHADER_UNIFORM_FLOAT);
        }
        
        inline void ApplyBlurBokeh(Shader shader, float time, Vector2 resolution, float blurRadius = 2.0f, float focusDist = 10.0f) {
            SetShaderValue(shader, GetShaderLocation(shader, "time"), &time, SHADER_UNIFORM_FLOAT);
            float effectType = 4.0f; // Blur
            SetShaderValue(shader, GetShaderLocation(shader, "effectType"), &effectType, SHADER_UNIFORM_FLOAT);
        }
        
        // Model Loader & Management
        inline Model SSO_LoadModel(const std::string& path) {
            return modelCache.Load(path);
        }
        
        inline void SSO_UnloadModel(const std::string& path) {
            modelCache.Unload(path);
        }
        
        inline void SSO_UnloadAllModels() {
            modelCache.UnloadAll();
        }
        
        // Rendering System with Transform
        inline void SSO_DrawModel(Model model, Vector3 position, float scale, Color tint = WHITE) {
            Matrix transform = MatrixIdentity();
            transform = MatrixMultiply(transform, MatrixTranslate(position.x, position.y, position.z));
            transform = MatrixMultiply(transform, MatrixScale(scale, scale, scale));
            
            model.transform = transform;
            DrawModel(model, position, scale, tint);
        }
        
        inline void SSO_DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, 
                                  float rotationAngle, Vector3 scale, Color tint = WHITE) {
            DrawModelEx(model, position, rotationAxis, rotationAngle, scale, tint);
        }
        
        // Camera Management
        inline void SSO_BeginMode3D(Camera3D camera) {
            BeginMode3D(camera);
        }
        
        inline void SSO_EndMode3D() {
            EndMode3D();
        }
        
        // Quick Prototyping - Primitive Shapes
        inline void SSO_DrawCube(Vector3 position, float size, Color color) {
            DrawCube(position, size, size, size, color);
        }
        
        inline void SSO_DrawCubeWires(Vector3 position, float size, Color color) {
            DrawCubeWires(position, size, size, size, color);
        }
        
        inline void SSO_DrawSphere(Vector3 position, float radius, Color color) {
            DrawSphere(position, radius, color);
        }
        
        inline void SSO_DrawSphereWires(Vector3 position, float radius, Color color) {
            DrawSphereWires(position, radius, 16, 16, color);
        }
        
        inline void SSO_DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, 
                                   float height, int slices, Color color) {
            DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
        }
        
        inline void SSO_DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, 
                                        float height, int slices, Color color) {
            DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
        }
        
        inline void SSO_DrawPlane(Vector3 position, Vector2 size, Color color) {
            DrawPlane(position, size, color);
        }
        
        inline void SSO_DrawPlaneWires(Vector3 position, Vector2 size, Color color) {
            // Custom plane wireframe implementation
            Vector3 v1 = {position.x - size.x/2, position.y, position.z - size.y/2};
            Vector3 v2 = {position.x + size.x/2, position.y, position.z - size.y/2};
            Vector3 v3 = {position.x + size.x/2, position.y, position.z + size.y/2};
            Vector3 v4 = {position.x - size.x/2, position.y, position.z + size.y/2};
            
            DrawLine3D(v1, v2, color);
            DrawLine3D(v2, v3, color);
            DrawLine3D(v3, v4, color);
            DrawLine3D(v4, v1, color);
        }
        
        // Editor Helpers - Grid & Gizmos
        inline void SSO_DrawGrid(int slices, float spacing) {
            DrawGrid(slices, spacing);
        }
        
        inline void SSO_DrawGizmo(Vector3 position, float size = 1.0f) {
            // X axis (Red)
            DrawLine3D(position, 
                      (Vector3){position.x + size, position.y, position.z}, 
                      RED);
            
            // Y axis (Green)  
            DrawLine3D(position, 
                      (Vector3){position.x, position.y + size, position.z}, 
                      GREEN);
            
            // Z axis (Blue)
            DrawLine3D(position, 
                      (Vector3){position.x, position.y, position.z + size}, 
                      BLUE);
        }
        
        inline void SSO_DrawGizmoEx(Vector3 position, Vector3 size) {
            // X axis (Red)
            DrawLine3D(position, 
                      (Vector3){position.x + size.x, position.y, position.z}, 
                      RED);
            
            // Y axis (Green)
            DrawLine3D(position, 
                      (Vector3){position.x, position.y + size.y, position.z}, 
                      GREEN);
            
            // Z axis (Blue)
            DrawLine3D(position, 
                      (Vector3){position.x, position.y, position.z + size.z}, 
                      BLUE);
        }
        
        // Advanced Utilities
        inline void SSO_DrawBillboard(Camera camera, Texture2D texture, Vector3 position, 
                                     float size, Color tint = WHITE) {
            DrawBillboard(camera, texture, position, size, tint);
        }
        
        inline void SSO_DrawBillboardRec(Camera camera, Texture2D texture, Rectangle source, 
                                        Vector3 position, Vector2 size, Color tint = WHITE) {
            DrawBillboardRec(camera, texture, source, position, size, tint);
        }
        
        inline void SSO_DrawRay(Ray ray, Color color) {
            DrawRay(ray, color);
        }
        
        // Collision System
        inline BoundingBox SSO_GetModelBoundingBox(Model model) {
            return GetModelBoundingBox(model);
        }
        
        inline BoundingBox SSO_GetMeshBoundingBox(Mesh mesh) {
            return GetMeshBoundingBox(mesh);
        }
        
        inline bool SSO_CheckCollisionBoxBox(BoundingBox box1, BoundingBox box2) {
            return CheckCollisionBoxes(box1, box2);
        }
        
        inline bool SSO_CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius) {
            return CheckCollisionBoxSphere(box, center, radius);
        }
        
        inline bool SSO_CheckCollisionSphereSphere(Vector3 center1, float radius1, 
                                                Vector3 center2, float radius2) {
            return CheckCollisionSpheres(center1, radius1, center2, radius2);
        }
        
        // Note: Ray collision functions removed - not available in this Raylib version
        
        // Advanced 3D Features
        inline void SSO_DrawGizmoMatrix(Matrix matrix, float size = 1.0f) {
            Vector3 position = {matrix.m12, matrix.m13, matrix.m14};
            SSO_DrawGizmo(position, size);
        }
        
        inline void SSO_DrawBoundingBox(BoundingBox box, Color color) {
            Vector3 v1 = {box.min.x, box.min.y, box.min.z};
            Vector3 v2 = {box.max.x, box.min.y, box.min.z};
            Vector3 v3 = {box.max.x, box.max.y, box.min.z};
            Vector3 v4 = {box.min.x, box.max.y, box.min.z};
            Vector3 v5 = {box.min.x, box.min.y, box.max.z};
            Vector3 v6 = {box.max.x, box.min.y, box.max.z};
            Vector3 v7 = {box.max.x, box.max.y, box.max.z};
            Vector3 v8 = {box.min.x, box.max.y, box.max.z};
            
            // Bottom face
            DrawLine3D(v1, v2, color);
            DrawLine3D(v2, v3, color);
            DrawLine3D(v3, v4, color);
            DrawLine3D(v4, v1, color);
            
            // Top face
            DrawLine3D(v5, v6, color);
            DrawLine3D(v6, v7, color);
            DrawLine3D(v7, v8, color);
            DrawLine3D(v8, v5, color);
            
            // Vertical edges
            DrawLine3D(v1, v5, color);
            DrawLine3D(v2, v6, color);
            DrawLine3D(v3, v7, color);
            DrawLine3D(v4, v8, color);
        }
        
        // Animation Support (Basic)
        inline void SSO_UpdateModelAnimation(Model model, ModelAnimation anim, float frame) {
            UpdateModelAnimation(model, anim, frame);
        }
        
        inline bool SSO_IsModelAnimationValid(Model model, ModelAnimation anim) {
            return IsModelAnimationValid(model, anim);
        }
        
        // Material Management - Simplified
        inline Material SSO_LoadMaterialDefault() {
            return LoadMaterialDefault();
        }
        
        inline void SSO_UnloadMaterial(Material material) {
            UnloadMaterial(material);
        }
        
        // Shader Support
        inline Shader SSO_LoadShader(const std::string& vsFileName, const std::string& fsFileName) {
            return LoadShader(vsFileName.c_str(), fsFileName.c_str());
        }
        
        inline Shader SSO_LoadShaderFromMemory(const char* vsCode, const char* fsCode) {
            return LoadShaderFromMemory(vsCode, fsCode);
        }
        
        inline int SSO_GetShaderLocation(Shader shader, const char* uniformName) {
            return GetShaderLocation(shader, uniformName);
        }
        
        inline void SSO_SetShaderValue(Shader shader, int locIndex, const void* value, int uniformType) {
            SetShaderValue(shader, locIndex, value, uniformType);
        }
        
        inline void SSO_UnloadShader(Shader shader) {
            UnloadShader(shader);
        }
        
        // Texture Management for 3D
        inline Texture2D SSO_LoadTexture(const std::string& fileName) {
            return LoadTexture(fileName.c_str());
        }
        
        inline Texture2D SSO_LoadTextureFromImage(Image image) {
            return LoadTextureFromImage(image);
        }
        
        inline Image SSO_LoadImage(const std::string& fileName) {
            return LoadImage(fileName.c_str());
        }
        
        inline void SSO_UnloadTexture(Texture2D texture) {
            UnloadTexture(texture);
        }
        
        inline void SSO_UnloadImage(Image image) {
            UnloadImage(image);
        }
        
        // Utility Functions
        inline Vector3 SSO_Vector3Zero() { return (Vector3){0, 0, 0}; }
        inline Vector3 SSO_Vector3One() { return (Vector3){1, 1, 1}; }
        inline Vector3 SSO_Vector3Up() { return (Vector3){0, 1, 0}; }
        inline Vector3 SSO_Vector3Down() { return (Vector3){0, -1, 0}; }
        inline Vector3 SSO_Vector3Left() { return (Vector3){-1, 0, 0}; }
        inline Vector3 SSO_Vector3Right() { return (Vector3){1, 0, 0}; }
        inline Vector3 SSO_Vector3Forward() { return (Vector3){0, 0, -1}; }
        inline Vector3 SSO_Vector3Backward() { return (Vector3){0, 0, 1}; }
        
        inline Matrix SSO_MatrixIdentity() { return MatrixIdentity(); }
        inline Matrix SSO_MatrixTranslate(float x, float y, float z) { return MatrixTranslate(x, y, z); }
        inline Matrix SSO_MatrixRotate(Vector3 axis, float angle) { return MatrixRotate(axis, angle); }
        inline Matrix SSO_MatrixScale(float x, float y, float z) { return MatrixScale(x, y, z); }
        
        // Camera Utilities
        inline Camera3D SSO_CreateCamera(Vector3 position, Vector3 target, Vector3 up, float fovy) {
            Camera3D camera = {0};
            camera.position = position;
            camera.target = target;
            camera.up = up;
            camera.fovy = fovy;
            camera.projection = CAMERA_PERSPECTIVE;
            return camera;
        }
        
        inline void SSO_UpdateCamera(Camera3D* camera, int mode) {
            UpdateCamera(camera, mode);
        }
        
        // Cleanup Function
        inline void SSO_Cleanup3D() {
            SSO_UnloadAllModels();
        }
    }
}

#endif // SSO_3D_H
