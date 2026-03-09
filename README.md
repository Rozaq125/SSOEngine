# SSOEngine V1.0

[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE) [![Build Status](https://img.shields.io/github/actions/workflow/status/SSOGames/SSOEngine/build.yml?branch=main)](https://github.com/SSOGames/SSOEngine/actions) [![Version](https://img.shields.io/badge/Version-1.0-brightgreen.svg)](https://github.com/SSOGames/SSOEngine/releases/tag/v1.0)

## 📖 Overview
SSOEngine is a lightweight, modular C++ game engine SDK built on Raylib. It provides ready‑to‑use subsystems (camera, timer, AI, asset packing) and an automated build pipeline, enabling indie developers to prototype and ship games faster.

## 📁 Project Structure
```
01_Core/
│   build.bat
│   assets/                # asset sources used by the packer
│   tools/
│       sso_camera.h
│       sso_timer.h
│   scripts/
│       sso_stalker.h
include/                    # external Raylib headers
00_BuildTools/
02_Docs/
```

## Quick Install
1.  Ensure **MinGW-w64** is installed and added to your system **PATH**.
2.  Open the `01_Core` folder.
3.  Run `build.bat`.
4.  Check the `build/` folder for your compiled `.exe`.
> *"Build games, not configurations."* ```

*For detailed setup, see [INSTALL (MUST READ).txt](INSTALL (MUST READ).txt).*

## 🚀 Quick Start
```bash
cd SSOEngine/01_Core
./build.bat
```
The script compiles the engine, generates `SSOEngine.dll`, and creates `resources.rc` using the Metadata Wizard.

## ✨ Key Features
* **SSO::Camera:** Smooth Lerp, dynamic Zoom, dan Screen Shake (di `tools/sso_camera.h`).
* **SSO::Timer:** Precision Delta-time based timing untuk Countdown & Stopwatch (`tools/sso_timer.h`).
* **Stalker AI:** Smart obstacle detection & predictive jumping (`scripts/sso_stalker.h`).
* **Asset Packing:** Otomatis bundle folder `assets/` jadi `assets.sso` pas proses build.

## 📄 License & Donation
SSOEngine is **Donationware**. Free for personal & commercial use.
💝 **Support us on Saweria:** [https://saweria.co/omedonation](https://saweria.co/omedonation)

---
© 2026 **SSOGames Studio** | Lead Developer: **Rozak**