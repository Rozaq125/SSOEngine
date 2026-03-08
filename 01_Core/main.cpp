#include "raylib.h"
#include "game.h"

int main(void) {
    // Initial Window Configuration
    InitWindow(1280, 720, "SSOEngine v1.0");
    SetTargetFPS(60);

    // Execute user's startup logic
    Start(); 

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // 1. Process Game Logic
        Update(deltaTime); 

        // 2. Render Graphics
        BeginDrawing();
            ClearBackground(BLACK);
            
            // Execute user's render logic
            Render(); 
            
            // Engine Watermark
            DrawText("Powered by SSOEngine", 1100, 700, 10, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}