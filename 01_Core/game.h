#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "tools/sso_text.h"

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

    SSO::Text::DrawGradient("SSO TEXT POWER", 30, 60, 30, VIOLET, BLUE);
    SSO::Text::DrawCodeBlock("INTERNAL_LOG: ALL_SYSTEMS_GO", 30, 100, 15, GREEN, BLACK);
    SSO::Text::DrawTypewriter("Loading custom engine protocols...", 30, 130, 15, 20.0f, timer, DARKGRAY);
    SSO::Text::DrawWrapped("Testing auto-wrap feature: This text will stay within its bounds and not bleed out of the screen, unlike standard DrawText.", 30, 160, 300, 15, GRAY);
    SSO::Text::DrawOutline("NEW UI LOADED", screenWidth/2 - 100, 100, 30, (Color){50, 50, 70, 255}, WHITE);
    SSO::Text::DrawCentered("--- EXPERIMENTAL TEXT ENGINE ---", 200, 20, (Color){150, 150, 255, 255});
    SSO::Text::DrawVertical("VERSION_1", 10, 300, 15, LIGHTGRAY);
}

inline void Shutdown() {
}

#endif