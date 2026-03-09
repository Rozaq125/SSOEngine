# SSOEngine v1.0 - SuperStudioEngine

## 📋 Overview

SSOEngine is a lightweight, high-performance C++ game engine built on top of Raylib.
It is designed for developers who prefer a code-first workflow and absolute modularity. Unlike heavy engines, SSOEngine provides a "Plug & Play" toolset—use only what you need, keep the rest out of your binary.

Minimalist. Portable. Lightning Fast.

## ✨ Key Features (v1.0 Update)

-   Modular Tool System: Independent headers for Camera, Timer, and Logging. No forced dependencies.
    
-   Advanced SSO::Camera: Features smooth Lerp Interpolation, dynamic Zoom, and high-impact Screen Shake effects.
    
-   Precision SSO::Timer: A universal timing class for Countdowns, Stopwatches, and Frame-independent Delta Time.
    
-   Adaptive Stalker AI: Built-in entity logic with smart obstacle detection and predictive jumping.
    
-   Automated Build System: Integrated Metadata Wizard for .exe properties and `.sso` Asset Packing for performance.
    

## 📁 Project Structure

SSOEngine/
├── 00\_BuildTools/           # Asset Packer (sso\_packer) & Build Scripts
├── 01\_Core/                 # Main Engine Hub
│   ├── scripts/             # Entity Logic (Player, Smart AI)
│   ├── tools/               # Modular Headers (Camera, Timer, Logger)
│   └── game.h               # Global Game Controller
├── Legal
├── assets/                  # Raw Assets (.png, .wav, .sso)
├── include/                 # External Headers (Raylib)
└── lib/                     # Pre-compiled Libraries

## 🚀 Quick Start (Automated Build)

SSOEngine is pre-configured for MinGW/GCC.

1\. Build the Project
Simply run the automated build script in the root directory:
`build.bat`

2\. Metadata Wizard
The script will ask if you want to update Game Details (Name, Version, Company). This automatically generates the `resource.rc` file to embed icons and file details into your executable.

3\. Run Your Game
The final binary is generated in the `build/` folder. Navigate to `build/` and run your `.exe` manually.

## 🛠 Modular Tools Tutorial

🎥 SSO::Camera (Smooth Follow & Shake)
Enable cinematic movement with ease:

#include "tools/sso\_camera.h"
SSO::Camera mainCam({ 640.0f, 360.0f }, 1280, 720);

// In Update:
mainCam.Follow(playerCenter, dt);
if (Impact) mainCam.Shake(20.0f, 0.4f);

⏱️ SSO::Timer (Universal Timing)
Manage level time or cooldowns:

#include "tools/sso\_timer.h"
SSO::Timer levelTimer;
levelTimer.SetValue(60.0f);
levelTimer.Start();

// In Update:
levelTimer.UpdateCountdown(dt);

## 📦 Asset Packing (.sso)

SSOEngine uses a custom Asset Packer. During the build process, all files in `/assets` are bundled into `assets.sso`. This improves disk I/O performance and prevents "loose file" clutter in your distribution.

CRITICAL: Always update raw files in the `/assets` folder. The build system will handle the packing automatically.

## 📄 License & Donation

SSOEngine is Donationware.
It is free to use for both personal and commercial projects. If you find this engine useful, please consider supporting SSOGames Studio.

  

💝 Support us on Saweria:

[https://saweria.co/omedonation](https://saweria.co/omedonation)

  

Legal information:

See `02_Docs/Legal/EULA.txt` for terms and conditions.

## 📬 Contact

SSOGames Studio 📧 Email: strata.tech.dev@gmail.com

🌐 Lead Developer: Rozak

© 2026 SSOGames Studio

All Rights Reserved