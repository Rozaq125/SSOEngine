#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "../tools/sso_provider.h"

// Player Variables
inline Rectangle playerRec = { 100, 100, 64, 64 };
inline Texture2D playerTex;
inline float velY = 0.0f;
inline bool grounded = false;
inline float facingDir = 1.0f; // 1.0 for Right, -1.0 for Left

/**
 * Loads the player texture from the .sso bundle
 */
inline void InitPlayer() {
    playerTex = SSO::Provider::LoadTextureFromBundle("assets.sso", "player.png");
    
    if (playerTex.id == 0) {
        TraceLog(LOG_WARNING, "PLAYER_H: Could not load player.png from bundle!");
    }
}

/**
 * Handles Input, Gravity, and Collisions
 */
inline void UpdatePlayer(float dt, Rectangle g, Rectangle w) {
    const float speed = 450.0f;
    const float gravity = 2000.0f;
    const float jumpForce = -850.0f;
    Vector2 oldPos = { playerRec.x, playerRec.y };

    // Horizontal Movement
    if (IsKeyDown(KEY_D)) {
        playerRec.x += speed * dt;
        facingDir = 1.0f;
    }
    if (IsKeyDown(KEY_A)) {
        playerRec.x -= speed * dt;
        facingDir = -1.0f;
    }

    // Vertical Physics (Gravity)
    velY += gravity * dt;
    playerRec.y += velY * dt;

    grounded = false;

    // --- Collision Handling ---
    // Ground Collision
    if (CheckCollisionRecs(playerRec, g)) {
        playerRec.y = g.y - playerRec.height;
        velY = 0;
        grounded = true;
    }

    // Wall/Platform Collision
    if (CheckCollisionRecs(playerRec, w)) {
        // Only collide if falling from above
        if (velY > 0 && (oldPos.y + playerRec.height <= w.y)) {
            playerRec.y = w.y - playerRec.height;
            velY = 0;
            grounded = true;
        }
    }

    // Jumping Input
    if (IsKeyPressed(KEY_SPACE) && grounded) {
        velY = jumpForce;
        grounded = false;
    }
}

/**
 * Renders the player sprite with flip support
 */
inline void RenderPlayer() {
    if (playerTex.id > 0) {
        // Define source and destination for sprite flipping
        Rectangle source = { 0, 0, (float)playerTex.width * facingDir, (float)playerTex.height };
        Rectangle dest = { playerRec.x, playerRec.y, playerRec.width, playerRec.height };
        
        DrawTexturePro(playerTex, source, dest, {0,0}, 0, WHITE);
    } else {
        // Fallback placeholder
        DrawRectangleRec(playerRec, MAGENTA);
    }
}

/**
 * Releases texture memory
 */
inline void UnloadPlayer() {
    if (playerTex.id > 0) UnloadTexture(playerTex);
}

#endif