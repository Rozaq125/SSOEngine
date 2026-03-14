#ifndef SSO_TEXT_H
#define SSO_TEXT_H

#include "raylib.h"
#include <string>
#include <vector>

namespace SSO {
    namespace Text {
        inline Font currentFont;
        inline bool isFontLoaded = false;

        void LoadFont(const char* fileName) {
            currentFont = ::LoadFont(fileName);
            isFontLoaded = true;
        }

        void UnloadFont() {
            if (isFontLoaded) {
                ::UnloadFont(currentFont);
                isFontLoaded = false;
            }
        }

        Font GetActiveFont() {
            return isFontLoaded ? currentFont : GetFontDefault();
        }

        void DrawShadow(const char* text, int x, int y, int fontSize, Color color, int offset) {
            Vector2 pos = {(float)x, (float)y};
            DrawTextEx(GetActiveFont(), text, {pos.x + offset, pos.y + offset}, (float)fontSize, 1, BLACK);
            DrawTextEx(GetActiveFont(), text, pos, (float)fontSize, 1, color);
        }

        void DrawCentered(const char* text, int y, int fontSize, Color color) {
            Vector2 textSize = MeasureTextEx(GetActiveFont(), text, (float)fontSize, 1);
            Vector2 pos = {(float)GetScreenWidth() / 2 - textSize.x / 2, (float)y};
            DrawTextEx(GetActiveFont(), text, pos, (float)fontSize, 1, color);
        }

        void DrawCodeBlock(const char* code, int x, int y, int fontSize, Color textColor, Color bgColor) {
            int padding = 10;
            Vector2 textSize = MeasureTextEx(GetActiveFont(), code, (float)fontSize, 1);
            DrawRectangle(x - padding, y - padding, (int)textSize.x + (padding * 2), fontSize + (padding * 2), bgColor);
            DrawRectangleLines(x - padding, y - padding, (int)textSize.x + (padding * 2), fontSize + (padding * 2), DARKGRAY);
            DrawTextEx(GetActiveFont(), code, {(float)x, (float)y}, (float)fontSize, 1, textColor);
        }

        void DrawTypewriter(const char* text, int x, int y, int fontSize, float speed, float time, Color color) {
            int length = (int)(time * speed);
            int totalLen = (int)TextLength(text);
            if (length > totalLen) length = totalLen;
            DrawTextEx(GetActiveFont(), TextSubtext(text, 0, length), {(float)x, (float)y}, (float)fontSize, 1, color);
        }

        void DrawWrapped(const char* text, int x, int y, int maxWidth, int fontSize, Color color) {
            float spacing = 1.0f;
            int currentY = y;
            std::string textStr = text;
            std::string line = "";
            std::string word = "";
            size_t i = 0;

            while (i <= textStr.length()) {
                if (i < textStr.length() && textStr[i] != ' ') {
                    word += textStr[i];
                } else {
                    std::string testLine = line + (line.empty() ? "" : " ") + word;
                    Vector2 textSize = MeasureTextEx(GetActiveFont(), testLine.c_str(), (float)fontSize, spacing);

                    if (textSize.x > maxWidth) {
                        DrawTextEx(GetActiveFont(), line.c_str(), {(float)x, (float)currentY}, (float)fontSize, spacing, color);
                        line = word;
                        currentY += fontSize + 5;
                    } else {
                        line = testLine;
                    }
                    word = "";
                }
                i++;
            }
            if (!line.empty()) DrawTextEx(GetActiveFont(), line.c_str(), {(float)x, (float)currentY}, (float)fontSize, spacing, color);
        }

        void DrawOutline(const char* text, int x, int y, int fontSize, Color color, Color outlineColor) {
            float fSize = (float)fontSize;
            Vector2 pos = {(float)x, (float)y};
            DrawTextEx(GetActiveFont(), text, {pos.x - 1, pos.y - 1}, fSize, 1, outlineColor);
            DrawTextEx(GetActiveFont(), text, {pos.x + 1, pos.y - 1}, fSize, 1, outlineColor);
            DrawTextEx(GetActiveFont(), text, {pos.x - 1, pos.y + 1}, fSize, 1, outlineColor);
            DrawTextEx(GetActiveFont(), text, {pos.x + 1, pos.y + 1}, fSize, 1, outlineColor);
            DrawTextEx(GetActiveFont(), text, pos, fSize, 1, color);
        }

        void DrawVertical(const char* text, int x, int y, int fontSize, Color color) {
            int len = TextLength(text);
            for (int i = 0; i < len; i++) {
                DrawTextEx(GetActiveFont(), TextSubtext(text, i, 1), {(float)x, (float)(y + (i * fontSize))}, (float)fontSize, 1, color);
            }
        }

        void DrawGradient(const char* text, int x, int y, int fontSize, Color topColor, Color bottomColor) {
            for (int i = 0; i < fontSize; i++) {
                float factor = (float)i / (float)fontSize;
                Color lineCol = {
                    (unsigned char)(topColor.r + (bottomColor.r - topColor.r) * factor),
                    (unsigned char)(topColor.g + (bottomColor.g - topColor.g) * factor),
                    (unsigned char)(topColor.b + (bottomColor.b - topColor.b) * factor),
                    255
                };
                BeginScissorMode(x, y + i, GetScreenWidth(), 1);
                DrawTextEx(GetActiveFont(), text, {(float)x, (float)y}, (float)fontSize, 1, lineCol);
                EndScissorMode();
            }
        }
    }
}

#endif