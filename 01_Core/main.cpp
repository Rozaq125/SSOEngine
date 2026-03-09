#include "raylib.h"
#include "game.h"

/**
 * SSOEngine v1.0 - Main Entry Point
 * Designed for High-Performance 2D Game Development
 */
int main(void) {
    // 1. Initial Engine Configuration
    const int screenWidth = 1280;
    const int screenHeight = 720;
    
    InitWindow(screenWidth, screenHeight, "SSOEngine v1.0 - Professional Build");
    SetTargetFPS(60);

    // 2. Initialize Game Logic & Assets
    Start(); 

    // 3. Main Engine Loop
    while (!WindowShouldClose()) {
        // Calculate Frame Time (Delta Time)
        float deltaTime = GetFrameTime();

        // --- UPDATE PHASE ---
        Update(deltaTime); 

        // --- RENDER PHASE ---
        BeginDrawing();
            ClearBackground(SKYBLUE); // Default sky color
            
            // Render all objects from game.h
            Render(); 
            
            // Permanent Engine Watermark
            DrawText("Powered by SSOEngine", 1100, 700, 10, DARKGRAY);
        EndDrawing();
    }

    // 4. Memory Cleanup
    Shutdown(); 
    CloseWindow();
    
    return 0;
}