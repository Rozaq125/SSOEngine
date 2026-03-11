#ifndef SSO_WINDOW_H
#define SSO_WINDOW_H

#include "../include/raylib.h"
#include <math.h>

namespace SSO {
    class Window {
    public:
        // --- Core Internal Configuration ---
        static inline int virtualWidth = 1280;
        static inline int virtualHeight = 720;
        static inline RenderTexture2D target = { 0 };

        // --- Developer Customization Settings ---
        static inline bool showBorder = false;
        static inline Color borderColor = MAROON;
        static inline float borderThickness = 4.0f;
        static inline Texture2D customIcon = { 0 }; // Used for watermarks or logos

        /**
         * Initializes the window with specific virtual resolution and flags.
         */
        static void Init(int width, int height, const char* title) {
            virtualWidth = width;
            virtualHeight = height;

            // Enable Resizable window, VSync, and 4x Anti-Aliasing by default
            SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
            InitWindow(virtualWidth, virtualHeight, title);
            SetWindowMinSize(640, 360);

            // Create the internal canvas (Render Texture)
            target = LoadRenderTexture(virtualWidth, virtualHeight);
            SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
            
            SetTargetFPS(60);
        }

        /**
         * Sets a new internal virtual resolution and updates the window size.
         */
        static void SetResolution(int width, int height) {
            virtualWidth = width;
            virtualHeight = height;
            
            if (target.id > 0) UnloadRenderTexture(target);
            target = LoadRenderTexture(virtualWidth, virtualHeight);
            SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);
            
            SetWindowSize(virtualWidth, virtualHeight);
        }

        /**
         * Disables the ability to resize or maximize the window.
         */
        static void DisableResizing() {
            ClearWindowState(FLAG_WINDOW_RESIZABLE);
        }

        /**
         * Enables the ability to resize or maximize the window.
         */
        static void EnableResizing() {
            SetWindowState(FLAG_WINDOW_RESIZABLE);
        }

        /**
         * Starts drawing into the internal virtual canvas.
         */
        static void BeginDrawingVirtual() {
            BeginTextureMode(target);
            ClearBackground(BLACK);
        }

        /**
         * Finalizes the internal frame and scales it to the actual screen size using letterboxing.
         */
        static void EndDrawingVirtual() {
            // 1. Draw Developer Overlays (Inside the virtual space)
            if (showBorder) {
                DrawRectangleLinesEx({ 0, 0, (float)virtualWidth, (float)virtualHeight }, 
                                     borderThickness, borderColor);
            }

            if (customIcon.id > 0) {
                // Place watermark at top-right by default
                DrawTextureEx(customIcon, { (float)virtualWidth - customIcon.width - 20, 20 }, 0, 1.0f, WHITE);
            }

            EndTextureMode();

            // 2. Scale and Render to physical screen
            BeginDrawing();
            ClearBackground(BLACK);

            // Calculate scale to maintain 16:9 aspect ratio (Letterboxing)
            float scale = fminf((float)GetScreenWidth() / (float)virtualWidth, 
                                (float)GetScreenHeight() / (float)virtualHeight);

            // Calculate destination rectangle (Centered)
            Rectangle destRec = {
                (GetScreenWidth() - ((float)virtualWidth * scale)) * 0.5f,
                (GetScreenHeight() - ((float)virtualHeight * scale)) * 0.5f,
                (float)virtualWidth * scale, 
                (float)virtualHeight * scale
            };

            // Draw the render texture to screen (flipped Y axis for correct orientation)
            DrawTexturePro(target.texture,
                { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                destRec, { 0, 0 }, 0.0f, WHITE);

            EndDrawing();
        }

        /**
         * Toggles between Fullscreen and Windowed mode properly.
         */
        static void ToggleFull() {
            if (!IsWindowFullscreen()) {
                int monitor = GetCurrentMonitor();
                SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
                ToggleFullscreen();
            } else {
                ToggleFullscreen();
                SetWindowSize(virtualWidth, virtualHeight);
            }
        }

        /**
         * Cleans up resources before closing.
         */
        static void Close() {
            if (customIcon.id > 0) UnloadTexture(customIcon);
            UnloadRenderTexture(target);
            CloseWindow();
        }
    };
}

#endif