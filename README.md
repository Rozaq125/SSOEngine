# SSOEngine

**Simple 2D Game Engine Built with Raylib**

> ⚠️ **REALISTIC VERSION**: This is a basic 2D game engine wrapper around Raylib, not a full commercial engine.

---

## 🎯 What SSOEngine Actually Is

SSOEngine is a **simplified C++ game development framework** that:

- ✅ **Wraps Raylib** - Uses Raylib as the graphics backend
- ✅ **Provides basic tools** - Asset packer, build automation
- ✅ **Simple structure** - Organized folder system for small games
- ✅ **Build automation** - One-click build with `build.bat`

## 🛠️ What's Actually Included

### Core Components
- **Raylib Integration** - Graphics, input, audio (via Raylib)
- **Asset Packer** - Custom `.sso` format for assets
- **Build System** - Automated MinGW compilation
- **Basic Tools** - Camera, timer, window management

### Tools Folder (`01_Core/tools/`)
```cpp
// Available tools (basic wrappers):
- sso_camera.h    // Camera management
- sso_timer.h     // Game timer
- sso_window.h    // Window setup
- sso_ui.h        // Basic UI elements
- sso_math.h      // Math utilities
- sso_logger.h    // Simple logging
- sso_utils.h     // General utilities
```

### Build System
```batch
# What build.bat actually does:
1. Check/Install Raylib libraries
2. Compile asset packer (if needed)
3. Pack assets into .sso format
4. Compile resources (.rc files)
5. Build game executable
```

## 🚀 Quick Start (Realistic)

### Prerequisites
- **MinGW-w64** - Required for compilation
- **Windows** - Currently Windows-only
- **Basic C++ knowledge** - This is not a no-code tool

### Installation
```bash
# Clone and build
git clone https://github.com/Rozaq125/SSOEngine
cd SSOEngine/01_Core
build.bat

# This will:
# 1. Download Raylib automatically
# 2. Build your game
# 3. Create .exe in build/ folder
```

### Basic Game Structure
```cpp
#include "tools/sso_window.h"
#include "tools/sso_camera.h"

int main() {
    // Initialize window
    InitWindow(800, 600, "My Game");
    
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // Your game code here
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
```

## 📁 Project Structure

```
SSOEngine/
├── 00_BuildTools/     # Asset packer source
├── 01_Core/          # Your game code
│   ├── tools/        # Engine tools (C++ headers)
│   ├── scripts/      # Game scripts
│   ├── assets/       # Game assets
│   ├── build.bat     # Build script
│   └── main.cpp      # Game entry point
├── 02_Docs/          # Documentation
├── include/          # Raylib headers
└── lib/             # Raylib libraries
```

## 🎮 What You Can Actually Build

### ✅ Supported Features
- **2D Graphics** - Sprites, shapes, text
- **Basic Audio** - Sound effects, music
- **Input Handling** - Keyboard, mouse
- **Asset Management** - Custom .sso format
- **Window Management** - Resizable windows
- **Basic UI** - Simple buttons and text

### ❌ NOT Supported (Yet)
- **3D Graphics** - 2D only currently
- **Advanced Physics** - Basic collision only
- **Networking** - Single player only
- **Mobile Platforms** - Windows only
- **Visual Editor** - Code-based development
- **Advanced AI** - Basic game logic only

## 🔧 Development Tools

### Asset Packer
```bash
# Converts assets to .sso format
sso_packer.exe

# Input: assets/ folder
# Output: build/assets.sso
```

### Build System
```bash
build.bat

# Features:
- Auto Raylib installation
- Asset packing
- Resource compilation
- Executable generation
```

## 📚 Learning Resources

### For Beginners
1. **Learn C++ first** - This requires programming knowledge
2. **Raylib documentation** - SSOEngine uses Raylib functions
3. **Basic game dev concepts** - Game loops, update/draw patterns

### Recommended Tutorials
- [Raylib Cheatsheet](https://www.raylib.com/cheatsheet/cheatsheet.html)
- [C++ Game Development](https://www.learncpp.com/)
- [Basic Game Programming](https://github.com/raysan5/raylibgames)

## 🤝 Contributing

### What We Need
- **Bug fixes** - Report and fix issues
- **Documentation** - Improve tutorials
- **Examples** - Simple game examples
- **Tools** - Better utility functions

### How to Contribute
1. Fork the repository
2. Make your changes
3. Test thoroughly
4. Submit a pull request

## ⚠️ Limitations & Reality Check

### This is NOT:
- ❌ Unity/Unreal competitor
- ❌ Commercial-grade engine
- ❌ No-code game maker
- ❌ Cross-platform solution
- ❌ Visual development tool

### This IS:
- ✅ Learning project
- ✅ Raylib wrapper
- ✅ Small game framework
- ✅ Educational tool
- ✅ Simple game starter

## 🐛 Known Issues

- **Windows only** - No cross-platform support yet
- **Basic documentation** - Still being improved
- **Limited examples** - Need more sample games
- **No debugger** - Use external debugging tools

## 📄 License

MIT License - Free to use, modify, and distribute.

## 👥 Credits

### Author
- **Rozak** - Lead Developer
  - GitHub: [@Rozaq125](https://github.com/Rozaq125)
  - Email: spctacularstudio@gmail.com

### Special Thanks
- **Raylib Team** - For the amazing graphics library
- **MinGW-w64 Project** - For the compiler tools
- **Game Dev Community** - For feedback and support

### Development Tools Used
- **Raylib** - Graphics and input
- **MinGW-w64** - C++ compilation
- **Batch Scripting** - Build automation
- **AI Assistance** - Documentation help

---

## 🎯 Real Use Cases

### ✅ Good For:
- **Learning game development**
- **Small 2D projects**
- **Game jam prototypes**
- **Educational purposes**
- **Raylib experimentation**

### ❌ Not Good For:
- **Large commercial games**
- **Complex 3D projects**
- **Multiplayer games**
- **Mobile development**
- **Beginners without coding experience**

---

## 📞 Support

### Get Help
- **GitHub Issues** - Report bugs and request features
- **Code Examples** - Check the tools folder
- **Raylib Docs** - For graphics functions
- **Community** - Game development forums

### Before Asking for Help:
1. ✅ Check if MinGW-w64 is installed
2. ✅ Try the build.bat script
3. ✅ Read the error messages
4. ✅ Check your C++ syntax

---

**⚠️ HONEST ASSESSMENT**: SSOEngine is a **basic framework** for learning game development with Raylib. It's **not** a replacement for professional game engines like Unity or Unreal. Use it for **learning, experimentation, and small projects**.

**Built with passion for indie game developers who want to learn C++ and Raylib.** 🎮✨
