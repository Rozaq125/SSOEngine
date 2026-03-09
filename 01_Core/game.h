#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "scripts/player.h"
#include "scripts/enemy.h"
#include "tools/sso_timer.h"
#include "tools/sso_camera.h"

// --- Global World Geometry ---
// Extreme width to allow long-distance exploration with the camera tool
inline Rectangle ground = { -5000, 650, 10000, 70 }; 
inline Rectangle wall   = { 700, 500, 300, 50 };

// --- Engine Core Systems ---
SSO::Timer countdownTimer;
SSO::Camera mainCam({ 640.0f, 360.0f }, 1280, 720);
inline bool gameFinished = false;
inline bool playerWon    = false;

/**
 * @brief Global Startup sequence.
 * Configures the environment and the game state.
 */
inline void Start() {
    InitPlayer();
    InitEnemy();

    // Mission: Survive for 30 seconds
    countdownTimer.Reset();
    countdownTimer.SetValue(30.0f);
    countdownTimer.Start();
    
    gameFinished = false;
    playerWon = false;
}

/**
 * @brief Main Logic Loop.
 * Handles Physics, AI Behavior, and Camera Smoothing.
 */
inline void Update(float dt) {
    if (!gameFinished) {
        // 1. Process Object Updates
        UpdatePlayer(dt, ground, wall);
        UpdateEnemy(dt, ground, wall);
        
        // 2. Process Timer Logic
        countdownTimer.UpdateCountdown(dt);

        // 3. Process Camera Tracking
        // Tracking the center point of the player's rectangle
        Vector2 playerCenter = { 
            playerRec.x + playerRec.width / 2.0f, 
            playerRec.y + playerRec.height / 2.0f 
        };
        mainCam.Follow(playerCenter, dt);

        // 4. Combat & Collision Logic
        if (CheckCollisionRecs(playerRec, enemyRec)) {
            // Impact! Shake the camera and trigger game over
            mainCam.Shake(15.0f, 0.3f);
            gameFinished = true;
            playerWon = false;
        }

        // 5. Objective Check
        if (countdownTimer.IsFinished()) {
            gameFinished = true;
            playerWon = true;
        }
    }
}

/**
 * @brief Main Render Loop.
 * Renders World Space objects (Camera-aware) and Screen Space (UI).
 */
inline void Render() {
    // --- Phase 1: World Space (Rendering objects affected by the Camera) ---
    mainCam.Begin();
        // Environment
        DrawRectangleRec(ground, DARKGREEN);
        DrawRectangleRec(wall, DARKGRAY);
        DrawRectangleLinesEx(wall, 2, LIGHTGRAY); // Visual detail
        
        // Entities
        RenderEnemy();
        RenderPlayer();
    mainCam.End();

    // --- Phase 2: Screen Space (Fixed HUD Elements) ---
    // Top Bar HUD
    DrawRectangle(0, 0, 1280, 55, Fade(BLACK, 0.6f)); 
    DrawRectangleLinesEx({0, 0, 1280, 55}, 1, Fade(RAYWHITE, 0.2f));

    // Live Timer Display
    float timeVal = countdownTimer.GetValue();
    Color timerColor = (timeVal < 10.0f) ? RED : YELLOW;
    DrawText(TextFormat("SURVIVAL CLOCK: %.1f s", timeVal), 520, 15, 25, timerColor);
    
    // Engine Brand / Info
    DrawText("SSOEngine Platformer: [A/D] Walk | [SPACE] Jump", 25, 18, 18, RAYWHITE);

    // --- Phase 3: Post-Game Overlays ---
    if (gameFinished) {
        // Darken the background for the menu
        DrawRectangle(0, 0, 1280, 720, Fade(BLACK, 0.85f));
        
        if (playerWon) {
            DrawText("MISSION: SUCCESS", 400, 300, 50, GREEN);
            DrawText("Target successfully survived the encounter.", 420, 370, 20, LIGHTGRAY);
        } else {
            DrawText("MISSION: TERMINATED", 380, 300, 50, RED);
            DrawText("Elimination confirmed by Stalker AI.", 460, 370, 20, LIGHTGRAY);
        }
        
        DrawText("Press [ESC] to Quit Engine", 520, 480, 20, GRAY);
    }
}

/**
 * @brief Resource Disposal.
 */
inline void Shutdown() {
    UnloadPlayer();
    UnloadEnemy();
}

#endif