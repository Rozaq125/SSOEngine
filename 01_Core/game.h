#ifndef GAME_H
#define GAME_H

#include "raylib.h"

inline bool gameActive = true;
inline float timer = 0.0f;

inline void Start() {
    timer = 0.0f;
}

inline void Update(float dt) {
    timer += dt;
}

inline void Render() {
    int screenWidth = 1280;
    int screenHeight = 720;
    
    const char* text = "Game Loaded";
    int fontSize = 60;
    int textWidth = MeasureText(text, fontSize);
    int textX = (screenWidth - textWidth) / 2;
    int textY = (screenHeight - fontSize) / 2;
    
    DrawRectangleGradientV(0, 0, screenWidth, screenHeight, 
                          (Color){240, 240, 255, 255}, 
                          (Color){220, 220, 240, 255});
    
    Color shadowColor = (Color){100, 100, 120, 100};
    DrawText(text, textX + 6, textY + 6, fontSize, shadowColor);
    
    DrawText(text, textX - 2, textY - 2, fontSize, WHITE);
    DrawText(text, textX + 2, textY - 2, fontSize, WHITE);
    DrawText(text, textX - 2, textY + 2, fontSize, WHITE);
    DrawText(text, textX + 2, textY + 2, fontSize, WHITE);
    DrawText(text, textX, textY, fontSize, (Color){50, 50, 70, 255});
    
    const char* info = "SSOEngine v1.0 - Press F11 for Fullscreen";
    int infoWidth = MeasureText(info, 20);
    DrawText(info, (screenWidth - infoWidth) / 2, screenHeight - 80, 20, (Color){80, 80, 100, 255});
    
    DrawText(TextFormat("Session: %.1f s", timer), 30, 30, 16, (Color){100, 100, 120, 255});
    
    const char* statusText = IsWindowFullscreen() ? "FULLSCREEN" : "WINDOWED";
    Color statusColor = IsWindowFullscreen() ? (Color){50, 180, 50, 255} : (Color){50, 100, 180, 255};
    DrawText(statusText, screenWidth - 120, 30, 16, statusColor);
    
    DrawText("SSO", screenWidth - 80, screenHeight - 40, 20, (Color){150, 150, 170, 100});
}

inline void Shutdown() {
}

#endif