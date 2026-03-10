#ifndef SSO_UI_H
#define SSO_UI_H

#include "raylib.h"
#include <vector>
#include <string>
#include <math.h> // Required for fminf and fmaxf

namespace SSO {
    namespace UI {

        // --- DATA STRUCTURES ---
        
        struct UIStyle {
            Color baseColor;
            Color hoverColor;
            Color textColor;
            float roundness;
            float borderThickness;
        };

        inline UIStyle DefaultButtonStyle = { { 40, 40, 40, 255 }, { 80, 80, 80, 255 }, WHITE, 0.2f, 2.0f };
        inline UIStyle PanelStyle = { { 30, 30, 30, 240 }, { 30, 30, 30, 240 }, WHITE, 0.1f, 1.5f };

        // --- UTILITIES ---

        inline void DrawBackground(Texture2D tex, Color tint = WHITE) {
            if (tex.id <= 0) return;
            DrawTexturePro(tex, { 0, 0, (float)tex.width, (float)tex.height },
                { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.0f, tint);
        }

        inline void DrawOverlay(float alpha = 0.5f) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
        }

        inline void DrawTextShadow(Font font, const char* text, Vector2 pos, float size, float spacing, Color color) {
            DrawTextEx(font, text, { pos.x + 2, pos.y + 2 }, size, spacing, BLACK);
            DrawTextEx(font, text, pos, size, spacing, color);
        }

        // --- 1. CORE INTERACTIVE ELEMENTS ---
        // Moved up to ensure visibility for DrawPopUp
        inline bool DrawButton(Rectangle rect, const char* text, Font font, UIStyle style = DefaultButtonStyle) {
            Vector2 mouse = GetMousePosition();
            bool hovering = CheckCollisionPointRec(mouse, rect);
            Color currentBg = hovering ? style.hoverColor : style.baseColor;
            
            DrawRectangleRounded(rect, style.roundness, 8, currentBg);
            DrawRectangleRoundedLines(rect, style.roundness, 8, style.borderThickness, WHITE);

            float fontSize = rect.height * 0.4f;
            Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);
            Vector2 textPos = {
                rect.x + (rect.width / 2) - (textSize.x / 2),
                rect.y + (rect.height / 2) - (textSize.y / 2)
            };

            DrawTextEx(font, text, textPos, fontSize, 1, style.textColor);
            return (hovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
        }

        // --- 2. PANEL SYSTEM ---

        inline void DrawPanel(Rectangle rect, const char* title, Font font, UIStyle style = PanelStyle) {
            DrawRectangleRounded(rect, style.roundness, 8, style.baseColor);
            DrawRectangleRoundedLines(rect, style.roundness, 8, style.borderThickness, DARKGRAY);

            Rectangle header = { rect.x, rect.y, rect.width, 30 };
            DrawRectangleRounded(header, style.roundness, 8, MAROON); 
            DrawTextEx(font, title, { rect.x + 10, rect.y + 7 }, 18, 1, WHITE);
        }

        // --- 3. SCROLLABLE AREA ---

        inline void BeginScrollArea(Rectangle rect, float* scrollPos, float contentHeight) {
            DrawRectangleRec(rect, { 20, 20, 20, 255 }); 
            *scrollPos += GetMouseWheelMove() * 20.0f;
            
            if (*scrollPos > 0) *scrollPos = 0;
            if (contentHeight > rect.height) {
                if (*scrollPos < -(contentHeight - rect.height)) *scrollPos = -(contentHeight - rect.height);
            } else {
                *scrollPos = 0;
            }
            BeginScissorMode((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height);
        }

        inline void EndScrollArea() {
            EndScissorMode();
        }

        // --- 4. MODAL SYSTEM ---

        inline bool DrawPopUp(Rectangle rect, const char* title, const char* msg, Font font, bool* active) {
            if (!*active) return false;

            DrawOverlay(0.7f); 
            DrawPanel(rect, title, font);
            DrawTextEx(font, msg, { rect.x + 20, rect.y + 60 }, 20, 1, LIGHTGRAY);

            if (DrawButton({ rect.x + rect.width/2 - 50, rect.y + rect.height - 50, 100, 35 }, "OK", font)) {
                *active = false;
                return true;
            }
            return false;
        }

        // --- 5. STATUS BARS ---

        inline void DrawHealthBar(Rectangle rect, float current, float max, Color fill, Color bg) {
            float perc = fmaxf(0.0f, fminf(1.0f, (float)current / (float)max));
            DrawRectangleRec(rect, bg); 
            DrawRectangle(rect.x, rect.y, rect.width * perc, rect.height, fill); 
            DrawRectangleLinesEx(rect, 1.5f, WHITE); 
        }
    }
}

#endif