#ifndef SSO_3D_H
#define SSO_3D_H

#include "raylib.h"
#include "raymath.h"
#include <string>

namespace SSO {
    namespace 3D {
        
        // Model Loader - Supports .obj, .gltf, .iqm
        inline Model SSO_LoadModel(const char* path) {
            return LoadModel(path);
        }
        
        // 3D Transform - Simple model rendering
        inline void SSO_DrawModel(Model model, Vector3 pos, float scale, Color tint) {
            model.transform = MatrixScale(scale, scale, scale);
            DrawModel(model, pos, 1.0f, tint);
        }
        
        // 3D Camera System - Switch between 2D UI and 3D World
        inline void SSO_BeginMode3D(Camera3D camera) {
            BeginMode3D(camera);
        }
        
        inline void SSO_EndMode3D() {
            EndMode3D();
        }
        
        // Basic Shapes 3D - Quick prototyping
        inline void SSO_DrawCube(Vector3 pos, float size, Color color) {
            DrawCube(pos, size, size, size, color);
        }
        
        inline void SSO_DrawCubeWires(Vector3 pos, float size, Color color) {
            DrawCubeWires(pos, size, size, size, color);
        }
        
        inline void SSO_DrawSphere(Vector3 pos, float radius, Color color) {
            DrawSphere(pos, radius, color);
        }
        
        inline void SSO_DrawSphereWires(Vector3 pos, float radius, Color color) {
            DrawSphereWires(pos, radius, 16, 16, color);
        }
        
        inline void SSO_DrawCylinder(Vector3 pos, float radiusTop, float radiusBottom, float height, int slices, Color color) {
            DrawCylinder(pos, radiusTop, radiusBottom, height, slices, color);
        }
        
        inline void SSO_DrawCylinderWires(Vector3 pos, float radiusTop, float radiusBottom, float height, int slices, Color color) {
            DrawCylinderWires(pos, radiusTop, radiusBottom, height, slices, color);
        }
        
        // Grid & Gizmos - Editor helpers
        inline void SSO_DrawGrid(int slices, float spacing) {
            DrawGrid(slices, spacing);
        }
        
        inline void SSO_DrawGizmo(Vector3 pos) {
            DrawGizmo(pos);
        }
        
        // Advanced 3D Functions
        inline void SSO_DrawBillboard(Camera camera, Texture2D texture, Vector3 pos, float size, Color tint) {
            DrawBillboard(camera, texture, pos, size, tint);
        }
        
        inline void SSO_DrawPlane(Vector3 pos, Vector2 size, Color color) {
            DrawPlane(pos, size, color);
        }
        
        inline void SSO_DrawRay(Vector3 startPos, Vector3 direction, Color color) {
            DrawRay(startPos, direction, color);
        }
        
        // Model utilities
        inline void SSO_UnloadModel(Model model) {
            UnloadModel(model);
        }
        
        inline BoundingBox SSO_GetModelBoundingBox(Model model) {
            return GetModelBoundingBox(model);
        }
        
        // Collision utilities
        inline bool SSO_CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius) {
            return CheckCollisionBoxSphere(box, center, radius);
        }
        
        inline bool SSO_CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2) {
            return CheckCollisionSpheres(center1, radius1, center2, radius2);
        }
        
        inline bool SSO_CheckCollisionBoxes(BoundingBox box1, BoundingBox box2) {
            return CheckCollisionBoxes(box1, box2);
        }
    }
}

#endif // SSO_3D_H
