#include "raylib.h"
#include "tools/sso_window.h"
#include "game.h"

int main(void) {
    SSO::Window::Init(1280, 720, "SSOEngine - Game Loaded");
    
    SSO::Window::DisableResizing();
    
    SetTargetFPS(60);
    
    Start();
    
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        if (IsKeyPressed(KEY_F11)) {
            SSO::Window::ToggleFull();
        }
        
        Update(dt);
        
        SSO::Window::BeginDrawingVirtual();
        Render();
        SSO::Window::EndDrawingVirtual();
    }
    
    Shutdown();
    SSO::Window::Close();
    
    return 0;
}