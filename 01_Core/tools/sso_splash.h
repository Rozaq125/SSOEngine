#ifndef SSO_SPLASH_H
#define SSO_SPLASH_H

#include "raylib.h"

namespace SSO {
    namespace Splash {
        void Show(float duration) {
            float startTime = (float)GetTime();
            const char* title = "SSOENGINE";
            const char* sub = "Lightweight C++ Power";
            
            int titleSize = 60;
            int subSize = 20;

            while (GetTime() - startTime < duration) {
                if (WindowShouldClose()) break;

                float elapsed = (float)GetTime() - startTime;
                float alpha = 1.0f;

                if (elapsed < 0.5f) alpha = elapsed / 0.5f;
                else if (elapsed > duration - 0.5f) alpha = (duration - elapsed) / 0.5f;

                BeginDrawing();
                ClearBackground(BLACK);

                int tw = MeasureText(title, titleSize);
                DrawText(title, GetScreenWidth()/2 - tw/2, GetScreenHeight()/2 - 40, titleSize, Fade(RAYWHITE, alpha));
                
                int sw = MeasureText(sub, subSize);
                DrawText(sub, GetScreenWidth()/2 - sw/2, GetScreenHeight()/2 + 30, subSize, Fade(GRAY, alpha));

                float progress = elapsed / duration;
                DrawRectangle(0, GetScreenHeight() - 5, (int)(GetScreenWidth() * progress), 5, Fade(LIME, alpha));

                EndDrawing();
            }
        }
    }
}

#endif