#ifndef SSO_UI_H
#define SSO_UI_H

#include "raylib.h"
#include <vector>
#include <string>
#include <math.h> 

namespace SSO {
    namespace UI {

        struct UIStyle {
            Color baseColor;
            Color hoverColor;
            Color textColor;
            float roundness;
            float borderThickness;
        };

        inline UIStyle DefaultButtonStyle = { { 40, 40, 40, 255 }, { 70, 70, 70, 255 }, WHITE, 0.2f, 2.0f };
        inline UIStyle PanelStyle = { { 25, 25, 25, 245 }, { 25, 25, 25, 245 }, WHITE, 0.1f, 2.0f };

        inline void DrawBackground(Texture2D tex, Color tint = WHITE) {
            if (tex.id <= 0) return;
            DrawTexturePro(tex, { 0, 0, (float)tex.width, (float)tex.height }, { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() }, { 0, 0 }, 0.0f, tint);
        }

        inline void DrawOverlay(float alpha = 0.5f) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, alpha));
        }

        inline void DrawTextShadow(Font font, const char* text, Vector2 pos, float size, float spacing, Color color) {
            DrawTextEx(font, text, { pos.x + 2, pos.y + 2 }, size, spacing, BLACK);
            DrawTextEx(font, text, pos, size, spacing, color);
        }

        inline bool DrawButton(Rectangle rect, const char* text, Font font, UIStyle style = DefaultButtonStyle) {
            Vector2 mouse = GetMousePosition();
            bool hovering = CheckCollisionPointRec(mouse, rect);
            Color currentBg = hovering ? style.hoverColor : style.baseColor;
            
            DrawRectangleRounded(rect, style.roundness, 8, currentBg);
            // FIX: Hapus borderThickness karena Raylib lo gak support thickness di fungsi ini
            DrawRectangleRoundedLines(rect, style.roundness, 8, hovering ? SKYBLUE : WHITE);

            float fontSize = rect.height * 0.4f;
            Vector2 textSize = MeasureTextEx(font, text, fontSize, 1);
            Vector2 textPos = { rect.x + (rect.width / 2) - (textSize.x / 2), rect.y + (rect.height / 2) - (textSize.y / 2) };
            DrawTextEx(font, text, textPos, fontSize, 1, style.textColor);
            return (hovering && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
        }

        inline void DrawPanel(Rectangle rect, const char* title, Font font, UIStyle style = PanelStyle) {
            DrawRectangleRounded(rect, style.roundness, 8, style.baseColor);
            // FIX: Hapus borderThickness
            DrawRectangleRoundedLines(rect, style.roundness, 8, GRAY);
            
            Rectangle header = { rect.x, rect.y, rect.width, 35 };
            DrawRectangleRounded(header, style.roundness, 8, MAROON); 
            DrawTextEx(font, title, { rect.x + 15, rect.y + 8 }, 18, 1, WHITE);
        }

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

        inline void DrawHealthBar(Rectangle rect, float current, float max, Color fill, Color bg) {
            float perc = fmaxf(0.0f, fminf(1.0f, current / max));
            DrawRectangleRounded(rect, 0.5f, 8, bg); 
            Rectangle fillRect = { rect.x + 2, rect.y + 2, (rect.width - 4) * perc, rect.height - 4 };
            if (perc > 0) DrawRectangleRounded(fillRect, 0.5f, 8, fill); 
            // FIX: Hapus 1.5f
            DrawRectangleRoundedLines(rect, 0.5f, 8, WHITE); 
        }
    }
}

#endif
