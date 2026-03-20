#ifndef SSO_CONTAINER_H
#define SSO_CONTAINER_H

#include "raylib.h"
#include "raymath.h"
#include <string>
#include <vector>

namespace SSO {
    namespace Container {
        
        // Theme System
        enum Theme {
            THEME_LIGHT = 0,
            THEME_DARK = 1,
            THEME_SSO_BLUE = 2
        };
        
        struct ThemeColors {
            Color background;
            Color panel;
            Color button;
            Color buttonHover;
            Color buttonPressed;
            Color text;
            Color border;
            Color accent;
        };
        
        // Widget Types
        enum WidgetType {
            WIDGET_BUTTON,
            WIDGET_LABEL,
            WIDGET_CHECKBOX,
            WIDGET_SLIDER,
            WIDGET_TEXTBOX
        };
        
        struct Widget {
            WidgetType type;
            std::string label;
            Rectangle bounds;
            bool isActive;
            bool isChecked;
            float value;
            std::string text;
            
            Widget(WidgetType t, const std::string& l) 
                : type(t), label(l), isActive(false), isChecked(false), value(0.0f) {}
        };
        
        struct Panel {
            Rectangle area;
            std::vector<Widget> widgets;
            Theme currentTheme;
            float yOffset;
            bool isCollapsed;
            
            Panel(Rectangle a, Theme theme = THEME_DARK) 
                : area(a), currentTheme(theme), yOffset(10), isCollapsed(false) {}
        };
        
        // Global theme management
        static ThemeColors currentThemeColors;
        static Theme globalTheme;
        
        // Theme Setup
        inline void SSO_SetTheme(int themeID) {
            globalTheme = (Theme)themeID;
            
            switch (themeID) {
                case THEME_LIGHT:
                    currentThemeColors = {
                        .background = {240, 240, 240, 255},
                        .panel = {255, 255, 255, 255},
                        .button = {200, 200, 200, 255},
                        .buttonHover = {180, 180, 180, 255},
                        .buttonPressed = {160, 160, 160, 255},
                        .text = {0, 0, 0, 255},
                        .border = {150, 150, 150, 255},
                        .accent = {0, 120, 215, 255}
                    };
                    break;
                    
                case THEME_DARK:
                    currentThemeColors = {
                        .background = {30, 30, 30, 255},
                        .panel = {45, 45, 45, 255},
                        .button = {60, 60, 60, 255},
                        .buttonHover = {80, 80, 80, 255},
                        .buttonPressed = {100, 100, 100, 255},
                        .text = {255, 255, 255, 255},
                        .border = {80, 80, 80, 255},
                        .accent = {0, 162, 232, 255}
                    };
                    break;
                    
                case THEME_SSO_BLUE:
                    currentThemeColors = {
                        .background = {15, 25, 35, 255},
                        .panel = {25, 40, 55, 255},
                        .button = {40, 65, 85, 255},
                        .buttonHover = {55, 85, 110, 255},
                        .buttonPressed = {70, 105, 135, 255},
                        .text = {220, 240, 255, 255},
                        .border = {60, 95, 125, 255},
                        .accent = {0, 200, 255, 255}
                    };
                    break;
            }
        }
        
        // Panel Management
        inline Panel* currentPanel = nullptr;
        
        inline void SSO_BeginPanel(Rectangle area) {
            static Panel panel(area, globalTheme);
            currentPanel = &panel;
            panel.widgets.clear();
            panel.yOffset = 10;
            
            // Draw panel background
            DrawRectangleRec(area, currentThemeColors.panel);
            DrawRectangleLinesEx(area, 2.0f, currentThemeColors.border);
        }
        
        // Widget System - Auto-stacking
        inline void SSO_PushWidget(const char* label) {
            if (!currentPanel) return;
            
            Widget widget(WIDGET_BUTTON, label);
            widget.bounds = {
                currentPanel->area.x + 10,
                currentPanel->area.y + currentPanel->yOffset,
                currentPanel->area.width - 20,
                30
            };
            
            currentPanel->widgets.push_back(widget);
            currentPanel->yOffset += 40; // Auto-stack
        }
        
        inline void SSO_PushLabel(const char* text) {
            if (!currentPanel) return;
            
            Widget widget(WIDGET_LABEL, text);
            widget.bounds = {
                currentPanel->area.x + 10,
                currentPanel->area.y + currentPanel->yOffset,
                currentPanel->area.width - 20,
                20
            };
            
            currentPanel->widgets.push_back(widget);
            currentPanel->yOffset += 25;
        }
        
        inline void SSO_PushCheckbox(const char* label, bool checked = false) {
            if (!currentPanel) return;
            
            Widget widget(WIDGET_CHECKBOX, label);
            widget.isChecked = checked;
            widget.bounds = {
                currentPanel->area.x + 10,
                currentPanel->area.y + currentPanel->yOffset,
                currentPanel->area.width - 20,
                25
            };
            
            currentPanel->widgets.push_back(widget);
            currentPanel->yOffset += 30;
        }
        
        inline void SSO_PushSlider(const char* label, float value = 0.0f, float min = 0.0f, float max = 100.0f) {
            if (!currentPanel) return;
            
            Widget widget(WIDGET_SLIDER, label);
            widget.value = value;
            widget.bounds = {
                currentPanel->area.x + 10,
                currentPanel->area.y + currentPanel->yOffset,
                currentPanel->area.width - 20,
                30
            };
            
            currentPanel->widgets.push_back(widget);
            currentPanel->yOffset += 40;
        }
        
        // Widget Interaction
        inline bool SSO_IsButtonClicked(const char* label) {
            if (!currentPanel) return false;
            
            for (auto& widget : currentPanel->widgets) {
                if (widget.type == WIDGET_BUTTON && widget.label == label) {
                    return widget.isActive;
                }
            }
            return false;
        }
        
        inline bool SSO_IsCheckboxChecked(const char* label) {
            if (!currentPanel) return false;
            
            for (auto& widget : currentPanel->widgets) {
                if (widget.type == WIDGET_CHECKBOX && widget.label == label) {
                    return widget.isChecked;
                }
            }
            return false;
        }
        
        inline float SSO_GetSliderValue(const char* label) {
            if (!currentPanel) return 0.0f;
            
            for (auto& widget : currentPanel->widgets) {
                if (widget.type == WIDGET_SLIDER && widget.label == label) {
                    return widget.value;
                }
            }
            return 0.0f;
        }
        
        // Rendering System
        inline void SSO_RenderPanel() {
            if (!currentPanel) return;
            
            Vector2 mousePos = GetMousePosition();
            
            for (auto& widget : currentPanel->widgets) {
                bool isHover = CheckCollisionPointRec(mousePos, widget.bounds);
                
                switch (widget.type) {
                    case WIDGET_BUTTON:
                        {
                            Color buttonColor = currentThemeColors.button;
                            if (isHover) {
                                buttonColor = currentThemeColors.buttonHover;
                                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                    buttonColor = currentThemeColors.buttonPressed;
                                    widget.isActive = true;
                                } else {
                                    widget.isActive = false;
                                }
                            } else {
                                widget.isActive = false;
                            }
                            
                            DrawRectangleRec(widget.bounds, buttonColor);
                            DrawRectangleLinesEx(widget.bounds, 1.0f, currentThemeColors.border);
                            
                            int textWidth = MeasureText(widget.label.c_str(), 10);
                            DrawText(widget.label.c_str(), 
                                   widget.bounds.x + (widget.bounds.width - textWidth) / 2,
                                   widget.bounds.y + (widget.bounds.height - 10) / 2,
                                   10, currentThemeColors.text);
                        }
                        break;
                        
                    case WIDGET_LABEL:
                        DrawText(widget.label.c_str(), 
                               widget.bounds.x, widget.bounds.y,
                               10, currentThemeColors.text);
                        break;
                        
                    case WIDGET_CHECKBOX:
                        {
                            Rectangle checkRect = {
                                widget.bounds.x,
                                widget.bounds.y,
                                20, 20
                            };
                            
                            DrawRectangleRec(checkRect, currentThemeColors.button);
                            DrawRectangleLinesEx(checkRect, 1.0f, currentThemeColors.border);
                            
                            if (widget.isChecked) {
                                DrawText("✓", checkRect.x + 2, checkRect.y, 12, currentThemeColors.accent);
                            }
                            
                            if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                                widget.isChecked = !widget.isChecked;
                            }
                            
                            DrawText(widget.label.c_str(),
                                   checkRect.x + 25,
                                   checkRect.y + 2,
                                   10, currentThemeColors.text);
                        }
                        break;
                        
                    case WIDGET_SLIDER:
                        {
                            Rectangle sliderTrack = {
                                widget.bounds.x,
                                widget.bounds.y + 10,
                                widget.bounds.width - 40,
                                10
                            };
                            
                            Rectangle sliderThumb = {
                                sliderTrack.x + (widget.value / 100.0f) * (sliderTrack.width - 20),
                                sliderTrack.y - 5,
                                20, 20
                            };
                            
                            DrawRectangleRec(sliderTrack, currentThemeColors.button);
                            DrawRectangleRec(sliderThumb, isHover ? currentThemeColors.accent : currentThemeColors.buttonHover);
                            
                            if (isHover && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                                float relativeX = mousePos.x - sliderTrack.x;
                                widget.value = (relativeX / sliderTrack.width) * 100.0f;
                                widget.value = Clamp(widget.value, 0.0f, 100.0f);
                            }
                            
                            DrawText(widget.label.c_str(),
                                   widget.bounds.x,
                                   widget.bounds.y,
                                   10, currentThemeColors.text);
                        }
                        break;
                }
            }
        }
        
        // Classic Game Drawing Functions (Jalur Game)
        inline void SSO_DrawSprite(Texture2D texture, Vector2 pos, Color tint = WHITE) {
            DrawTextureV(texture, pos, tint);
        }
        
        inline void SSO_DrawRectangle(Rectangle rect, Color color) {
            DrawRectangleRec(rect, color);
        }
        
        inline void SSO_DrawRectangleLines(Rectangle rect, Color color) {
            DrawRectangleLinesEx(rect, 1.0f, color);
        }
        
        inline void SSO_DrawCircle(Vector2 center, float radius, Color color) {
            DrawCircleV(center, radius, color);
        }
        
        inline void SSO_DrawCircleLines(Vector2 center, float radius, Color color) {
            DrawCircleLines(center.x, center.y, radius, color);
        }
        
        inline void SSO_DrawText(const char* text, Vector2 pos, int fontSize, Color color) {
            DrawText(text, pos.x, pos.y, fontSize, color);
        }
        
        inline void SSO_DrawLine(Vector2 start, Vector2 end, Color color) {
            DrawLineV(start, end, color);
        }
        
        // Initialize theme system
        inline void SSO_InitContainer() {
            SSO_SetTheme(THEME_DARK);
        }
    }
}

#endif // SSO_CONTAINER_H
