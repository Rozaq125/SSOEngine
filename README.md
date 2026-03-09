# SSOEngine V1.0

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE) [![Build Status](https://img.shields.io/github/actions/workflow/status/SSOGames/SSOEngine/build.yml?branch=main)](https://github.com/SSOGames/SSOEngine/actions) [![Version](https://img.shields.io/badge/Version-1.0-brightgreen.svg)](https://github.com/SSOGames/SSOEngine/releases/tag/v1.0) [![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://github.com/SSOGames/SSOEngine) [![Language](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)

## 📖 Overview

**SSOEngine** is a lightweight, modular C++ game engine SDK built on Raylib. It provides ready‑to‑use subsystems (camera, timer, AI, asset packing) and an automated build pipeline, enabling indie developers to prototype and ship games faster.

### 🎯 Perfect For
- **Indie Game Developers** who want to focus on gameplay, not boilerplate
- **Game Jams** and rapid prototyping
- **Educational Projects** for learning C++ game development
- **2D Games** of any genre (platformers, shooters, puzzles, etc.)

---

## 🚀 Quick Start

### Prerequisites
- **Windows** operating system
- **MinGW-w64** (GCC) compiler installed and added to PATH
- Basic knowledge of C++

### One-Click Build & Run
```bash
cd SSOEngine/01_Core
./build.bat
```
That's it! Your game will be compiled and ready in `build/` folder.

> *"Build games, not configurations."*

---

## 📁 Complete Project Structure

```
SSOEngine/
├── 📄 README.md                    # This file - Complete documentation
├── 📄 LICENSE                      # MIT License
├── 📄 INSTALL (MUST READ).txt      # Detailed installation guide
├── 📄 .gitignore                   # Git ignore rules
│
├── 📁 00_BuildTools/               # Build system utilities
│   └── Asset packer & Metadata Wizard
│
├── 📁 01_Core/                     # MAIN WORKSPACE ⭐
│   ├── 🦇 build.bat                # Automated build script
│   ├── 🎮 main.cpp                 # Game entry point
│   ├── 🎯 game.h                   # Game logic & configuration
│   ├── 🖼️ app_icon.ico             # Application icon
│   ├── 📦 resource.rc               # Windows resource file
│   │
│   ├── 📁 tools/                   # Engine subsystems
│   │   ├── 📹 sso_camera.h         # 2D Camera system
│   │   ├── ⏱️ sso_timer.h          # Delta-time based timers
│   │   ├── 🖥️ sso_window.h         # Window management
│   │   ├── 🎨 sso_ui.h             # UI components
│   │   ├── 📊 sso_provider.h       # Data providers
│   │   ├── 🧮 sso_math.h           # Math utilities
│   │   ├── 📝 sso_logger.h         # Logging system
│   │   └── 🛠️ sso_utils.h          # General utilities
│   │
│   ├── 📁 scripts/                 # Game-specific scripts
│   │   ├── 👤 player.h             # Player character logic
│   │   └── 👾 enemy.h              # Enemy AI logic
│   │
│   ├── 📁 assets/                  # Game assets (images, sounds, etc.)
│   └── 📁 build/                   # Compiled output directory
│
├── 📁 02_Docs/                     # Documentation
│   └── 📁 Legal/
│       └── 📄 EULA.txt             # End User License Agreement
│
├── 📁 include/                     # External headers (Raylib)
├── 📁 lib/                         # Static libraries (.a files)
└── 📁 examples/                    # Code examples and tutorials
    └── 📄 example.cpp              # Asset embedding example
```

---

## 🔧 Installation Guide

### 1. System Requirements
- **Windows 10/11** (64-bit recommended)
- **MinGW-w64** GCC compiler (version 7.0 or higher)
- **2GB+ RAM** for development
- **100MB+ disk space**

### 2. Installing MinGW-w64

#### Option A: MSYS2 (Recommended)
```bash
# Install MSYS2 from https://www.msys2.org/
# Then in MSYS2 terminal:
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-make
```

#### Option B: Standalone MinGW-w64
1. Download from [https://winlibs.com/](https://winlibs.com/)
2. Extract to `C:\mingw64`
3. Add `C:\mingw64\bin` to your PATH environment variable

### 3. Verify Installation
Open Command Prompt and run:
```bash
g++ --version
```
If you see version information, you're ready to go!

---

## 🎮 How to Build & Run

### Method 1: Automated Build (Recommended)
```bash
cd SSOEngine/01_Core
build.bat
```

### Method 2: Manual Build
```bash
cd SSOEngine/01_Core
g++ -o build/game.exe main.cpp -I../include -L../lib -lraylib -lopengl32 -lgdi32 -lwinmm
```

### Build Process Overview
1. **Metadata Wizard** - Configure game details (name, icon, version)
2. **Asset Packing** - Bundle `assets/` folder into `assets.sso`
3. **Resource Compilation** - Process icons and metadata
4. **Code Compilation** - Build your game executable
5. **Output** - Final game in `build/` folder

---

## ✨ Engine Features

### 🎥 Camera System (`tools/sso_camera.h`)
```cpp
SSO::Camera mainCam({ 640.0f, 360.0f }, 1280, 720);

// Features:
- Smooth Lerp interpolation
- Dynamic zoom control
- Screen shake effects
- Follow target tracking
- Boundary constraints
```

### ⏱️ Timer System (`tools/sso_timer.h`)
```cpp
SSO::Timer countdownTimer;
countdownTimer.SetDuration(30.0f); // 30 seconds

// Features:
- Delta-time based precision
- Countdown & Stopwatch modes
- Pause/Resume functionality
- Event callbacks
```

### 🖥️ Window Management (`tools/sso_window.h`)
```cpp
SSO::Window window("My Game", 1280, 720);

// Features:
- Resolution management
- Fullscreen toggle
- V-Sync control
- Window positioning
```

### 🎨 UI System (`tools/sso_ui.h`)
```cpp
SSO::Button button({100, 100, 200, 50}, "Click Me!");

// Features:
- Button, Text, Input components
- Mouse interaction
- Visual feedback
- Layout management
```

### 🧮 Math Utilities (`tools/sso_math.h`)
```cpp
Vector2 normalized = SSO::Math::Normalize(vector);
float distance = SSO::Math::Distance(point1, point2);

// Features:
- Vector operations
- Collision detection
- Interpolation functions
- Trigonometry helpers
```

### 📊 Data Providers (`tools/sso_provider.h`)
```cpp
SSO::AssetProvider assets;
Texture2D texture = assets.LoadTexture("player.png");

// Features:
- Asset loading/management
- Data streaming
- Caching system
- Resource pooling
```

---

## 🎯 Game Development Workflow

### 1. Setup Your Game
```cpp
// In game.h
inline void Start() {
    // Initialize game objects
    InitPlayer();
    InitEnemy();
    
    // Configure timers
    countdownTimer.Reset();
    countdownTimer.SetDuration(30.0f);
}

inline void Update(float deltaTime) {
    // Update game logic
    UpdatePlayer(deltaTime);
    UpdateEnemy(deltaTime);
    
    // Update camera
    mainCam.Follow(player.position);
    mainCam.Update(deltaTime);
}

inline void Render() {
    // Render everything
    DrawPlayer();
    DrawEnemy();
    DrawUI();
}
```

### 2. Add Assets
Place your game assets in `01_Core/assets/`:
- Images (PNG, JPG, BMP)
- Sounds (WAV, OGG)
- Fonts (TTF, FNT)
- Data files (JSON, XML)

### 3. Build & Test
```bash
build.bat
# Your game is now in build/game.exe
```

---

## � API Reference

### Core Classes

#### SSO::Camera
```cpp
class Camera {
public:
    Camera(Vector2 target, int screenWidth, int screenHeight);
    
    void Follow(Vector2 target);           // Follow a target
    void SetZoom(float zoom);              // Set zoom level
    void Shake(float intensity, float duration); // Screen shake
    void SetBounds(Rectangle bounds);      // Set movement bounds
    void Update(float deltaTime);          // Update camera
    
    Camera2D GetCamera2D();                // Get Raylib camera
};
```

#### SSO::Timer
```cpp
class Timer {
public:
    void Reset();                          // Reset timer
    void SetDuration(float seconds);       // Set duration
    void Pause();                           // Pause timer
    void Resume();                          // Resume timer
    
    bool IsFinished();                      // Check if finished
    float GetProgress();                    // Get progress (0-1)
    float GetRemaining();                   // Get remaining time
};
```

#### SSO::Window
```cpp
class Window {
public:
    Window(const char* title, int width, int height);
    
    void SetSize(int width, int height);   // Set window size
    void SetFullscreen(bool fullscreen);    // Toggle fullscreen
    void SetVSync(bool vsync);             // Toggle V-Sync
    void Center();                          // Center window
    
    bool ShouldClose();                     // Check if should close
};
```

---

## 🎨 Asset System

### Supported Formats
- **Images**: PNG, JPG, BMP, TGA, PSD, GIF
- **Sounds**: WAV, OGG, MP3, FLAC
- **Fonts**: TTF, OTF, FNT
- **Data**: JSON, XML, TXT, CFG

### Asset Packing
Assets are automatically packed into `assets.sso` during build:
```cpp
// Access embedded assets
#include "assets_data.h"

// Assets are available as:
// asset_filename[]     // Binary data
// asset_filename_size  // Data size
```

### Asset Loading
```cpp
// Load from packed assets
Texture2D texture = LoadTextureFromMemory(asset_player_png, asset_player_png_size);
Sound sound = LoadSoundFromMemory(asset_explosion_wav, asset_explosion_wav_size);
```

---

## 🛠️ Advanced Configuration

### Build Script Customization
Edit `01_Core/build.bat` to customize:
- Compiler flags
- Library linking
- Asset packing options
- Output directory

### Game Configuration
Edit `01_Core/game.h` to customize:
- Screen resolution
- Game constants
- Object initialization
- Update/render logic

### Resource Configuration
Edit `01_Core/resource.rc` to customize:
- Game name and version
- Application icon
- File metadata

---

## 🐛 Troubleshooting

### Common Issues

#### "'g++' is not recognized"
**Solution**: Install MinGW-w64 and add to PATH
1. Install MinGW-w64 (see Installation Guide)
2. Add compiler's `bin` folder to Windows PATH
3. Restart Command Prompt

#### "Build Failed"
**Possible Causes**:
- Missing Raylib libraries in `lib/` folder
- Syntax errors in your code
- Missing asset files

**Solutions**:
1. Check `lib/` folder contains `libraylib.a`
2. Review your code for syntax errors
3. Ensure all assets are in `assets/` folder

#### "Asset Not Found"
**Solution**: 
1. Place assets in `01_Core/assets/` folder
2. Use correct file names (case-sensitive)
3. Rebuild with `build.bat`

#### "Window Won't Open"
**Solutions**:
1. Check graphics drivers are updated
2. Ensure OpenGL is supported
3. Try running as administrator

### Debug Mode
Enable debug output by adding to `build.bat`:
```bash
set DEBUG=1
```

---

## 📖 Examples & Tutorials

### Basic Game Loop
```cpp
#include "raylib.h"
#include "game.h"

int main(void) {
    // Initialize window
    InitWindow(1280, 720, "My Game");
    SetTargetFPS(60);
    
    // Start game
    Start();
    
    // Main loop
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        
        Update(deltaTime);
        
        BeginDrawing();
        ClearBackground(BLACK);
        Render();
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
```

### Player Movement
```cpp
void UpdatePlayer(float deltaTime) {
    // Input
    if (IsKeyDown(KEY_RIGHT)) player.x += speed * deltaTime;
    if (IsKeyDown(KEY_LEFT))  player.x -= speed * deltaTime;
    if (IsKeyDown(KEY_UP))    player.y -= speed * deltaTime;
    if (IsKeyDown(KEY_DOWN))  player.y += speed * deltaTime;
    
    // Boundaries
    player.x = Clamp(player.x, 0, screenWidth);
    player.y = Clamp(player.y, 0, screenHeight);
}
```

### Camera Follow
```cpp
void UpdateCamera(float deltaTime) {
    // Follow player with smooth lerp
    mainCam.Follow(player.position);
    mainCam.Update(deltaTime);
    
    // Apply camera to rendering
    BeginMode2D(mainCam.GetCamera2D());
    // Render game objects
    EndMode2D();
}
```

---

## 🤝 Contributing

### How to Contribute
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly
5. Submit a pull request

### Coding Standards
- Use C++17 features
- Follow existing code style
- Add comments for complex logic
- Include examples for new features

### Bug Reports
- Use GitHub Issues
- Provide detailed steps
- Include error messages
- Attach screenshots if applicable

---

## 📄 License & Support

### License
SSOEngine is **Donationware** - Free for personal & commercial use!

### 🎁 Support the Project
💝 **Donate on Saweria:** [https://saweria.co/omedonation](https://saweria.co/omedonation)

Your support helps us:
- ✅ Maintain and improve the engine
- ✅ Add new features and tools
- ✅ Provide better documentation
- ✅ Create more examples and tutorials

### Community
- **GitHub**: [SSOGames/SSOEngine](https://github.com/SSOGames/SSOEngine)
- **Discord**: Coming soon!
- **YouTube**: Tutorials and devlogs

---

## 🏆 Showcase

### Games Made with SSOEngine
*Have you made a game with SSOEngine? Let us know and we'll feature it here!*

### Features in Development
- 🎵 Audio system improvements
- 🌐 Networking support
- 🎨 Particle system
- 📱 Mobile export options
- 🎮 Input system enhancements

---

## 📞 Contact

### Lead Developer
**Rozak** - Game Engine Architect
- GitHub: [@rozakdev](https://github.com/rozakdev)
- Email: rozak@ssogames.com

### SSOGames Studio
- Website: [ssogames.com](https://ssogames.com)
- Twitter: [@SSOGamesStudio](https://twitter.com/SSOGamesStudio)

---

## 🗺️ Roadmap

### Version 1.1 (Planned)
- [ ] Advanced audio system
- [ ] Particle effects
- [ ] Input mapping system
- [ ] More UI components

### Version 1.2 (Future)
- [ ] Networking multiplayer
- [ ] Mobile platform support
- [ ] Visual editor
- [ ] Asset marketplace

### Version 2.0 (Long-term)
- [ ] 3D support
- [ ] Scripting system (Lua)
- [ ] Physics engine integration
- [ ] Cross-platform builds

---

## 📚 Additional Resources

### Learning Resources
- [Raylib Documentation](https://www.raylib.com/)
- [C++ Game Development Tutorials](https://github.com/topics/cpp-game-dev)
- [Game Programming Patterns](https://gameprogrammingpatterns.com/)

### Tools & Software
- **IDE**: Visual Studio Code, CLion
- **Graphics**: Aseprite, Photoshop
- **Audio**: Audacity, FMOD
- **Version Control**: Git, GitHub Desktop

---

---

**© 2026 SSOGames Studio | Lead Developer: Rozak**

*Built with passion for indie game developers everywhere.* 🎮✨
