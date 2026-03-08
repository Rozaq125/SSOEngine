# SSOEngine v1.0 - SuperStudioEngine

![Version](https://img.shields.io/badge/version-1.0-blue.svg)
![License](https://img.shields.io/badge/license-Donationware-orange.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen.svg)

---

## 📋 Overview

**SSOEngine** is a lightweight, high-performance **C++ game engine** built on top of **Raylib**.  
Designed for developers who prefer a **code-first workflow** over heavy editors.

Minimalist, portable, and lightning fast.

---

## 📁 Project Structure

```text
SSOEngine/
├── 01_Core/                 # Engine source code (main.cpp)
├── 02_Project_Templates/    # Starter templates for games
├── 03_Tools/                # Python scripts (asset embedder)
├── 04_Docs/                 # Documentation & Legal (EULA)
├── assets/                  # Put your game assets here (.png, .wav, etc)
├── examples/                # Example projects
├── include/                 # Header files (raylib.h, assets_data.h)
└── lib/                     # Pre-compiled libraries (.a)
```

---

# 🚀 Quick Start (Portable Build)

SSOEngine is **pre-configured for MinGW/GCC**.  
No internet connection is required to build if you already have the local libraries.

## 1️⃣ Configure the Project

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_CXX_COMPILER=g++
```

## 2️⃣ Build the Engine

```bash
cmake --build .
```

## 3️⃣ Run Your Game

Navigate to:

```
build/bin/
```

Then run:

```
SSOEngine.exe
```

---

# 🛠 Tools

## Asset Embedder

Convert your assets into a **C++ header file** for easy inclusion.

```bash
python 03_Tools/embedder.py
```

---

# 📄 License & Donation

SSOEngine is **Donationware**.

It is **free to use for both personal and commercial projects**.  
If you find this engine useful, please consider supporting **SSOGames Studio**.

💝 Support us on Saweria:  
https://saweria.co/omedonation

Legal information:  
See `04_Docs/Legal/EULA.txt` for terms and conditions.

---

# 📬 Contact

**SSOGames Studio**

📧 Email: strata.tech.dev@gmail.com

---

© 2026 SSOGames Studio  
All Rights Reserved