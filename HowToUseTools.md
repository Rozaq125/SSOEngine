# How to Use SSOEngine Tools

**REAL ACTUAL GUIDE - Based on Actual Tool Files**

> ⚠️ **UPDATED**: This guide now reflects the ACTUAL tools in the repository, not the basic version I initially described.

---

## 📁 Tools Location

All tools are located in: `01_Core/tools/`

```
01_Core/tools/
├── sso_camera.h     # Advanced Camera with smoothing & shake
├── sso_timer.h      # High-precision Timer with countdown/stopwatch
├── sso_window.h     # Virtual Resolution Window Manager
├── sso_ui.h         # Advanced UI System with panels & modals
├── sso_math.h       # Collision & Math utilities
├── sso_logger.h     # Colored Console Logger
└── sso_utils.h      # (Currently empty)
```

---

## 📜 sso_text.h - Advanced Text System

### What is its function
If you find it difficult to create text in plain raylib language then use SSOText to make it easier!

### Include
```cpp
#include "tools/sso_text.h"
```

## Available Functions

#### **Font Management**
```cpp
void LoadFont(const char* fileName);
void UnloadFont();

// Example:
SSO::Text::LoadFont("assets/fonts/myfont.ttf");
```
#### **Special Effects**
```cpp
// Create typewriter dialogue
void DrawTypewriter(const char* text, int x, int y, int fontSize, float speed, float time, Color color);

// Create professional gradients
void DrawGradient(const char* text, int x, int y, int fontSize, Color top, Color bottom);

// Create text with outline
void DrawOutline(const char* text, int x, int y, int fontSize, Color color, Color outlineColor);
```

#### **Layout & Utilities**
```cpp
// Automatically wrap text within a specific width
void DrawWrapped(const char* text, int x, int y, int maxWidth, int fontSize, Color color);

// Draw text perfectly centered on screen
void DrawCentered(const char* text, int y, int fontSize, Color color);

// Create terminal-style code blocks
void DrawCodeBlock(const char* code, int x, int y, int fontSize, Color textColor, Color bgColor);
```

### Example Usage
```cpp
#include "tools/sso_text.h"

void Render() {
    SSO::Window::BeginDrawingVirtual();
    ClearBackground(BLACK);

    // 1. Title with Gradient and Outline
    SSO::Text::DrawGradient("SSO ENGINE", 50, 50, 60, YELLOW, RED);
    SSO::Text::DrawOutline("SSO ENGINE", 50, 50, 60, BLANK, WHITE);

    // 2. Automated Dialogue
    SSO::Text::DrawTypewriter("Mission Log: Connecting to base...", 50, 150, 20, 15.0f, GetTime(), LIME);

    // 3. Smart Wrap for Story/Description
    SSO::Text::DrawWrapped("This is a long description that will automatically move to the next line once it hits the maximum width limit.", 
                           50, 200, 400, 20, RAYWHITE);

    // 4. Centered Footer
    SSO::Text::DrawCentered("PRESS START TO CONTINUE", 600, 25, GRAY);

    SSO::Window::EndDrawingVirtual();
}
```

## 🎥 sso_camera.h - Advanced Camera System

### What it ACTUALLY Does
High-performance 2D Camera with smooth interpolation, zoom control, and dynamic screen shake effects.

### Include
```cpp
#include "tools/sso_camera.h"
```

### Available Functions

#### **Initialize Camera**
```cpp
SSO::Camera camera(Vector2 target, int screenWidth = 1280, int screenHeight = 720);

// Example:
SSO::Camera camera(Vector2{400, 300}, 1280, 720);
```

#### **Camera Following with Smoothing**
```cpp
void Follow(Vector2 targetPos, float dt);

// Example:
camera.Follow(playerPosition, deltaTime);
```

#### **Screen Shake Effects**
```cpp
void Shake(float intensity, float duration);

// Example:
camera.Shake(10.0f, 0.5f); // Shake for 0.5 seconds with intensity 10
```

#### **Configuration**
```cpp
void SetZoom(float zoom);
float GetZoom() const;

void SetSmoothing(float s);  // 0.0 = very smooth, 1.0 = stiff
float GetSmoothing() const;
```

#### **Camera Rendering**
```cpp
camera.Begin();  // BeginMode2D
// Draw your game objects here
camera.End();    // EndMode2D
```

### Example Usage
```cpp
#include "tools/sso_camera.h"
#include "tools/sso_timer.h"

int main() {
    SSO::Window::Init(800, 600, "Advanced Camera Demo");
    
    SSO::Camera camera(Vector2{0, 0}, 800, 600);
    SSO::Timer timer;
    
    Vector2 playerPos = {0, 0};
    
    while (!WindowShouldClose()) {
        float dt = timer.GetDeltaTime();
        
        // Player movement
        if (IsKeyDown(KEY_RIGHT)) playerPos.x += 200 * dt;
        if (IsKeyDown(KEY_LEFT)) playerPos.x -= 200 * dt;
        
        // Camera follow with smoothing
        camera.Follow(playerPos, dt);
        
        // Trigger shake on space
        if (IsKeyPressed(KEY_SPACE)) {
            camera.Shake(15.0f, 0.3f);
        }
        
        // Rendering
        SSO::Window::BeginDrawingVirtual();
        
        camera.Begin();
        DrawCircleV(playerPos, 20, BLUE);
        DrawGrid(20, 50);
        camera.End();
        
        SSO::Window::EndDrawingVirtual();
    }
    
    SSO::Window::Close();
    return 0;
}
```

---

## ⏱️ sso_timer.h - High-Precision Timer

### What it ACTUALLY Does
Universal Time Management System with high-precision delta time and flexible game timers.

### Include
```cpp
#include "tools/sso_timer.h"
```

### Available Functions

#### **Core Engine Timing**
```cpp
SSO::Timer timer;

float deltaTime = timer.GetDeltaTime();    // Frame duration
float totalTime = timer.GetTotalTime();    // Total elapsed time
```

#### **Game Timer Management**
```cpp
// Countdown timer (waktu mundur)
timer.SetValue(60.0f);  // Set 60 seconds
timer.Start();          // Start countdown
timer.UpdateCountdown(deltaTime);  // Update each frame

if (timer.IsFinished()) {
    // Timer reached zero
}

// Stopwatch timer (waktu maju)
timer.Reset();
timer.Start();
timer.UpdateStopwatch(deltaTime);  // Count up

float currentTime = timer.GetValue();  // Get current value
```

#### **Timer Control**
```cpp
timer.Start();     // Start/resume
timer.Stop();      // Pause
timer.Reset();     // Reset to zero
bool isRunning = timer.IsRunning();
```

### Example Usage
```cpp
#include "tools/sso_timer.h"
#include "tools/sso_logger.h"

int main() {
    SSO::Window::Init(800, 600, "Timer Demo");
    
    SSO::Timer engineTimer;
    SSO::Timer gameTimer;
    
    // Set 10-second countdown
    gameTimer.SetValue(10.0f);
    gameTimer.Start();
    
    while (!WindowShouldClose()) {
        float dt = engineTimer.GetDeltaTime();
        
        // Update countdown
        gameTimer.UpdateCountdown(dt);
        
        SSO::Window::BeginDrawingVirtual();
        ClearBackground(RAYWHITE);
        
        DrawText(TextFormat("Time Left: %.1f", gameTimer.GetValue()), 
                300, 250, 30, BLACK);
        
        if (gameTimer.IsFinished()) {
            DrawText("TIME'S UP!", 320, 300, 20, RED);
        }
        
        SSO::Window::EndDrawingVirtual();
    }
    
    SSO::Window::Close();
    return 0;
}
```

---

## 🪟 sso_window.h - Virtual Resolution Manager

### What it ACTUALLY Does
Advanced window management with virtual resolution, letterboxing, and render-to-texture system.

### Include
```cpp
#include "tools/sso_window.h"
```

### Available Functions

#### **Window Initialization**
```cpp
SSO::Window::Init(width, height, title);

// Example:
SSO::Window::Init(1280, 720, "Game Title");
```

#### **Virtual Resolution System**
```cpp
// Change internal resolution (maintains aspect ratio)
SSO::Window::SetResolution(1920, 1080);

// Window resizing controls
SSO::Window::EnableResizing();
SSO::Window::DisableResizing();
```

#### **Virtual Canvas Rendering**
```cpp
SSO::Window::BeginDrawingVirtual();
// Draw everything here - it's rendered to virtual canvas
ClearBackground(BLACK);
DrawCircle(640, 360, 100, RED);
SSO::Window::EndDrawingVirtual();
// This automatically handles letterboxing and scaling
```

#### **Fullscreen Toggle**
```cpp
SSO::Window::ToggleFull();  // Proper fullscreen with resolution restore
```

#### **Developer Features**
```cpp
// Show debug border around virtual area
SSO::Window::showBorder = true;
SSO::Window::borderColor = MAROON;
SSO::Window::borderThickness = 4.0f;

// Custom watermark/icon
SSO::Window::customIcon = LoadTexture("watermark.png");
```

#### **Cleanup**
```cpp
SSO::Window::Close();  // Proper resource cleanup
```

### Example Usage
```cpp
#include "tools/sso_window.h"
#include "tools/sso_camera.h"

int main() {
    // Initialize with virtual resolution
    SSO::Window::Init(1280, 720, "Virtual Resolution Demo");
    
    // Enable debug features
    SSO::Window::showBorder = true;
    SSO::Window::borderColor = GREEN;
    
    SSO::Camera camera(Vector2{0, 0}, 1280, 720);
    
    while (!WindowShouldClose()) {
        // Handle fullscreen toggle
        if (IsKeyPressed(KEY_F11)) {
            SSO::Window::ToggleFull();
        }
        
        // Virtual canvas rendering
        SSO::Window::BeginDrawingVirtual();
        
        camera.Begin();
        DrawGrid(40, 100);
        DrawRectangle(-100, -100, 200, 200, BLUE);
        camera.End();
        
        SSO::Window::EndDrawingVirtual();
    }
    
    SSO::Window::Close();
    return 0;
}
```

---

## 🎨 sso_ui.h - Advanced UI System

### What it ACTUALLY Does
Complete UI system with styled buttons, panels, scrollable areas, modals, and status bars.

### Include
```cpp
#include "tools/sso_ui.h"
```

### Available Functions

#### **UI Styling**
```cpp
SSO::UI::UIStyle buttonStyle = {
    .baseColor = {40, 40, 40, 255},      // Normal color
    .hoverColor = {80, 80, 80, 255},     // Hover color  
    .textColor = WHITE,
    .roundness = 0.2f,
    .borderThickness = 2.0f
};
```

#### **Core UI Elements**
```cpp
// Button with custom font and style
bool clicked = SSO::UI::DrawButton(rect, "Click Me", font, buttonStyle);

// Panel with header
SSO::UI::DrawPanel(rect, "Panel Title", font);

// Health/status bar
SSO::UI::DrawHealthBar(rect, currentHealth, maxHealth, GREEN, RED);
```

#### **Scrollable Areas**
```cpp
float scrollPos = 0.0f;
float contentHeight = 1000.0f;

SSO::UI::BeginScrollArea(viewRect, &scrollPos, contentHeight);
// Draw your scrollable content here
for (int i = 0; i < 50; i++) {
    DrawText(TextFormat("Item %d", i), 20, i * 30 + scrollPos, 20, WHITE);
}
SSO::UI::EndScrollArea();
```

#### **Modal Popups**
```cpp
bool popupActive = true;

bool confirmed = SSO::UI::DrawPopUp(
    popupRect, 
    "Confirm", 
    "Are you sure you want to quit?", 
    font, 
    &popupActive
);
```

#### **Visual Effects**
```cpp
// Background texture
SSO::UI::DrawBackground(backgroundTexture, WHITE);

// Overlay for modals
SSO::UI::DrawOverlay(0.7f);

// Text with shadow
SSO::UI::DrawTextShadow(font, "Shadow Text", pos, 20, 1, WHITE);
```

### Example Usage
```cpp
#include "tools/sso_ui.h"
#include "tools/sso_window.h"

int main() {
    SSO::Window::Init(800, 600, "Advanced UI Demo");
    Font font = LoadFont("resources/font.png");
    
    Rectangle buttonRect = {300, 250, 200, 50};
    Rectangle panelRect = {200, 150, 400, 300};
    Rectangle healthBarRect = {300, 350, 200, 30};
    
    float health = 75.0f;
    bool popupActive = false;
    
    while (!WindowShouldClose()) {
        SSO::Window::BeginDrawingVirtual();
        ClearBackground(DARKGRAY);
        
        // Draw panel
        SSO::UI::DrawPanel(panelRect, "UI Demo", font);
        
        // Draw button
        if (SSO::UI::DrawButton(buttonRect, "Show Popup", font)) {
            popupActive = true;
        }
        
        // Draw health bar
        SSO::UI::DrawHealthBar(healthBarRect, health, 100.0f, GREEN, RED);
        
        // Draw popup if active
        if (popupActive) {
            Rectangle popupRect = {250, 200, 300, 150};
            if (SSO::UI::DrawPopUp(popupRect, "Popup", "Hello World!", font, &popupActive)) {
                // Popup confirmed
            }
        }
        
        SSO::Window::EndDrawingVirtual();
    }
    
    UnloadFont(font);
    SSO::Window::Close();
    return 0;
}
```

---

## 🔢 sso_math.h - Collision & Math

### What it ACTUALLY Does
Essential collision detection and math utilities for 2D games.

### Include
```cpp
#include "tools/sso_math.h"
```

### Available Functions

#### **Collision Detection**
```cpp
// AABB Collision (Rectangle vs Rectangle)
bool collision = CheckCollision(rect1, rect2);

// Circle collision (built into Raylib)
bool circleCollision = CheckCollisionCircles(circle1, radius1, circle2, radius2);
```

#### **Vector Utilities**
```cpp
// Clamp vector within boundaries
Vector2 clampedPos = ClampVector2(position, minX, minY, maxX, maxY);

// Distance calculation
float distance = GetDistance(pos1, pos2);
```

#### **Collision Resolution**
```cpp
// Solid collision resolution (prevents passing through walls)
Rectangle playerRect = {playerX, playerY, playerWidth, playerHeight};
Rectangle wallRect = {wallX, wallY, wallWidth, wallHeight};
Vector2 previousPlayerPos = {prevX, prevY};

ResolveCollision(&playerRect, wallRect, previousPlayerPos);
```

### Example Usage
```cpp
#include "tools/sso_math.h"
#include "tools/sso_window.h"

int main() {
    SSO::Window::Init(800, 600, "Collision Demo");
    
    Rectangle player = {100, 100, 40, 40};
    Rectangle wall = {300, 200, 100, 20};
    Vector2 previousPos = {100, 100};
    
    while (!WindowShouldClose()) {
        // Store previous position
        previousPos = {player.x, player.y};
        
        // Player movement
        if (IsKeyDown(KEY_RIGHT)) player.x += 5;
        if (IsKeyDown(KEY_LEFT)) player.x -= 5;
        if (IsKeyDown(KEY_UP)) player.y -= 5;
        if (IsKeyDown(KEY_DOWN)) player.y += 5;
        
        // Keep player in screen bounds
        player.x = ClampVector2({player.x, player.y}, 0, 0, 760, 560).x;
        player.y = ClampVector2({player.x, player.y}, 0, 0, 760, 560).y;
        
        // Check collision with wall
        if (CheckCollision(player, wall)) {
            // Resolve collision - move back to previous position
            ResolveCollision(&player, wall, previousPos);
        }
        
        SSO::Window::BeginDrawingVirtual();
        ClearBackground(RAYWHITE);
        
        DrawRectangleRec(player, BLUE);
        DrawRectangleRec(wall, RED);
        
        // Show collision status
        if (CheckCollision(player, wall)) {
            DrawText("COLLISION!", 10, 10, 20, RED);
        }
        
        SSO::Window::EndDrawingVirtual();
    }
    
    SSO::Window::Close();
    return 0;
}
```

---

## 📝 sso_logger.h - Colored Console Logger

### What it ACTUALLY Does
Console logging system with colored output and timestamps.

### Include
```cpp
#include "tools/sso_logger.h"
```

### Available Functions

#### **Basic Logging**
```cpp
SSO::Logger::Log(SSO::Logger::Level::INFO, "Game started");
SSO::Logger::Log(SSO::Logger::Level::WARNING, "Low memory");
SSO::Logger::Log(SSO::Logger::Level::ERROR, "Failed to load texture");
SSO::Logger::Log(SSO::Logger::Level::SUCCESS, "Level loaded");
```

#### **Output Colors**
- **INFO** - Cyan color
- **WARNING** - Yellow color  
- **ERROR** - Red color
- **SUCCESS** - Green color

#### **Timestamp Format**
```
[14:32:15] [INFO] Game started
[14:32:16] [WARNING] Low memory
[14:32:17] [SUCCESS] Level loaded
```

### Example Usage
```cpp
#include "tools/sso_logger.h"
#include "tools/sso_window.h"

int main() {
    SSO::Logger::Log(SSO::Logger::Level::INFO, "Initializing game...");
    
    SSO::Window::Init(800, 600, "Logger Demo");
    SSO::Logger::Log(SSO::Logger::Level::SUCCESS, "Window initialized");
    
    Texture2D texture = LoadTexture("player.png");
    if (texture.id <= 0) {
        SSO::Logger::Log(SSO::Logger::Level::ERROR, "Failed to load player.png");
    } else {
        SSO::Logger::Log(SSO::Logger::Level::SUCCESS, "Player texture loaded");
    }
    
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) {
            SSO::Logger::Log(SSO::Logger::Level::INFO, "Space key pressed");
        }
        
        SSO::Window::BeginDrawingVirtual();
        ClearBackground(RAYWHITE);
        DrawText("Check console for log messages", 200, 300, 20, BLACK);
        SSO::Window::EndDrawingVirtual();
    }
    
    SSO::Logger::Log(SSO::Logger::Level::INFO, "Game shutting down...");
    SSO::Window::Close();
    return 0;
}
```

---

## 🛠️ sso_utils.h - Currently Empty

### Status
This file exists but is currently empty (only contains a blank line).

---

## 🚀 Complete Game Example

Here's how to use the ACTUAL advanced tools together:

```cpp
#include "tools/sso_window.h"
#include "tools/sso_camera.h"
#include "tools/sso_timer.h"
#include "tools/sso_ui.h"
#include "tools/sso_math.h"
#include "tools/sso_logger.h"

int main() {
    // Initialize systems
    SSO::Logger::Log(SSO::Logger::Level::INFO, "Starting game...");
    
    // Window setup with virtual resolution
    SSO::Window::Init(1280, 720, "Advanced Game Demo");
    SSO::Window::showBorder = true;
    SSO::Logger::Log(SSO::Logger::Level::SUCCESS, "Window initialized");
    
    // Camera setup
    SSO::Camera camera(Vector2{0, 0}, 1280, 720);
    camera.SetZoom(1.0f);
    camera.SetSmoothing(0.1f);
    
    // Timer setup
    SSO::Timer engineTimer;
    SSO::Timer gameTimer;
    gameTimer.SetValue(120.0f); // 2 minute timer
    gameTimer.Start();
    
    // Game objects
    Rectangle player = {0, 0, 40, 40};
    Rectangle wall = {200, 100, 80, 20};
    Vector2 previousPos = {0, 0};
    
    // UI setup
    Font font = GetFontDefault();
    Rectangle buttonRect = {550, 20, 150, 40};
    Rectangle healthBarRect = {550, 70, 150, 20};
    float health = 100.0f;
    bool showPopup = false;
    
    SSO::Logger::Log(SSO::Logger::Level::INFO, "Game loop started");
    
    while (!WindowShouldClose()) {
        float dt = engineTimer.GetDeltaTime();
        
        // Update game timer
        gameTimer.UpdateCountdown(dt);
        
        // Player movement
        previousPos = {player.x, player.y};
        if (IsKeyDown(KEY_RIGHT)) player.x += 200 * dt;
        if (IsKeyDown(KEY_LEFT)) player.x -= 200 * dt;
        if (IsKeyDown(KEY_UP)) player.y -= 200 * dt;
        if (IsKeyDown(KEY_DOWN)) player.y += 200 * dt;
        
        // Collision resolution
        if (CheckCollision(player, wall)) {
            ResolveCollision(&player, wall, previousPos);
            SSO::Logger::Log(SSO::Logger::Level::WARNING, "Player collision with wall");
        }
        
        // Camera follow with smoothing
        camera.Follow({player.x + 20, player.y + 20}, dt);
        
        // Handle UI
        if (SSO::UI::DrawButton(buttonRect, "Shake", font)) {
            camera.Shake(20.0f, 0.5f);
            SSO::Logger::Log(SSO::Logger::Level::INFO, "Camera shake triggered");
        }
        
        if (gameTimer.IsFinished()) {
            health -= dt * 10; // Lose health over time
            if (health <= 0) {
                showPopup = true;
                health = 0;
            }
        }
        
        // Rendering
        SSO::Window::BeginDrawingVirtual();
        ClearBackground(DARKGRAY);
        
        // Game world (with camera)
        camera.Begin();
        DrawGrid(40, 100);
        DrawRectangleRec(player, BLUE);
        DrawRectangleRec(wall, RED);
        camera.End();
        
        // UI (no camera)
        DrawText(TextFormat("Time: %.1f", gameTimer.GetValue()), 10, 10, 20, WHITE);
        DrawText(TextFormat("FPS: %d", GetFPS()), 10, 40, 20, WHITE);
        SSO::UI::DrawHealthBar(healthBarRect, health, 100.0f, GREEN, RED);
        
        // Popup
        if (showPopup) {
            Rectangle popupRect = {400, 250, 400, 150};
            if (SSO::UI::DrawPopUp(popupRect, "Game Over", "Time's up! Click OK to restart.", font, &showPopup)) {
                // Restart game
                gameTimer.Reset();
                gameTimer.Start();
                health = 100.0f;
                player = {0, 0};
                SSO::Logger::Log(SSO::Logger::Level::INFO, "Game restarted");
            }
        }
        
        SSO::Window::EndDrawingVirtual();
    }
    
    SSO::Logger::Log(SSO::Logger::Level::INFO, "Game ending...");
    SSO::Window::Close();
    return 0;
}
```

---

## ⚠️ Important Notes

### What These Tools ACTUALLY Are
- ✅ **Advanced camera system** - With smoothing and shake effects
- ✅ **High-precision timer** - With countdown/stopwatch functionality
- ✅ **Virtual resolution manager** - With letterboxing and scaling
- ✅ **Complete UI system** - With panels, modals, and styling
- ✅ **Collision utilities** - Essential math functions
- ✅ **Colored logger** - With timestamps and colors

### Limitations
- **sso_utils.h is empty** - Currently contains no functions
- **Windows-focused** - Some features may not work cross-platform
- **Requires C++11 or later** - Uses chrono and modern C++ features
- **Memory management** - Manual cleanup required for some resources

### Best Practices
1. **Use SSO::Window::BeginDrawingVirtual()** - Not BeginDrawing()
2. **Always call SSO::Window::Close()** - Proper resource cleanup
3. **Use namespace SSO::UI** - For UI functions
4. **Check timer IsFinished()** - Before using timer values

### When to Use These Tools
- ✅ **2D games with advanced camera** - Platformers, top-down games
- ✅ **Games with complex UI** - RPGs, strategy games
- ✅ **Games with timing mechanics** - Puzzles, arcade games
- ✅ **Games needing collision** - Action games, platformers

---

**These tools are actually quite advanced!** They provide features you'd expect from a serious game engine, not just basic wrappers. The virtual resolution system, advanced camera with shake, and complete UI system are particularly impressive. 🎮✨
