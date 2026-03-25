#include "raylib.h"
#include "tools/sso_window.h"
#include "tools/sso_splash.h"
#include "tools/sso_text.h"
#include "tools/sso_3d.h"
#include "game.h"

int main(void) {
    // Initialize window first
    SSO::Window::Init(1280, 720, "SSOEngine - 3D Physics Test");
    
    // Show splash
    SSO::Splash::Show(6.0f);
    
    // Hide cursor for FPS
    DisableCursor();
    
    SetTargetFPS(60);
    
    Start();
    
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        
        // Simple input handling
        if (IsKeyPressed(KEY_F11)) {
            SSO::Window::ToggleFull();
        }
        
        if (IsKeyPressed(KEY_ESCAPE)) {
            EnableCursor();
            break;
        }
        
        Update(dt);
        
        SSO::Window::BeginDrawingVirtual();
        
        // Clear background
        ClearBackground(BLACK);
        
        // 3D Rendering
        SSO::ThreeD::SSO_BeginMode3D(physicsGame.camera);
        
        RenderPhysicsWorld();
        
        SSO::ThreeD::SSO_EndMode3D();
        
        // 2D UI
        RenderUI();
        
        SSO::Window::EndDrawingVirtual();
    }
    
    // Cleanup
    Shutdown();
    SSO::Window::Close();
    
    return 0;
}
