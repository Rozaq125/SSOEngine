#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "player.h" // Accessing playerRec for AI tracking

// Enemy State Variables
inline Rectangle enemyRec = { 1100, 590, 60, 60 };
inline float enemyVelY = 0.0f;
inline bool enemyGrounded = false;
inline float enemySpeed = 220.0f;
inline Color enemyColor = RED;

/**
 * Initial configuration for the Enemy Entity
 */
inline void InitEnemy() {
    enemyRec.x = 1100.0f;
    enemyRec.y = 590.0f;
    enemyVelY = 0.0f;
}

/**
 * AI Logic: Pursues the player and jumps over obstacles
 */
inline void UpdateEnemy(float dt, Rectangle g, Rectangle w) {
    const float gravity = 2200.0f;
    const float jumpForce = -850.0f;

    // 1. Pathfinding: Move towards Player X-Position
    if (enemyRec.x < playerRec.x) enemyRec.x += enemySpeed * dt;
    else if (enemyRec.x > playerRec.x) enemyRec.x -= enemySpeed * dt;

    // 2. Obstacle Detection: Check if a wall is in front of the enemy
    // We project a small "sensor" rectangle ahead based on movement
    Rectangle sensor = { (enemyRec.x < playerRec.x ? enemyRec.x + 65 : enemyRec.x - 25), enemyRec.y, 20, 40 };
    bool wallInFront = CheckCollisionRecs(sensor, w);

    // 3. Smart Jumping: Jump if wall detected OR player is high above
    if (enemyGrounded && (wallInFront || playerRec.y < enemyRec.y - 150)) {
        enemyVelY = jumpForce;
        enemyGrounded = false;
    }

    // 4. Apply Physics
    enemyVelY += gravity * dt;
    enemyRec.y += enemyVelY * dt;

    // 5. Collision Handling
    enemyGrounded = false;
    // Ground collision
    if (CheckCollisionRecs(enemyRec, g)) {
        enemyRec.y = g.y - enemyRec.height;
        enemyVelY = 0;
        enemyGrounded = true;
    }
    // Wall/Platform collision
    if (CheckCollisionRecs(enemyRec, w)) {
        if (enemyVelY > 0) { // Only landing from above
            enemyRec.y = w.y - enemyRec.height;
            enemyVelY = 0;
            enemyGrounded = true;
        }
    }
}

/**
 * Draw the enemy to the screen
 */
inline void RenderEnemy() {
    DrawRectangleRec(enemyRec, enemyColor);
    DrawRectangleLinesEx(enemyRec, 2, MAROON);
    DrawText("STALKER AI", (int)enemyRec.x - 5, (int)enemyRec.y - 20, 15, MAROON);
}

inline void UnloadEnemy() {
    // Release assets if any (e.g., enemy textures)
}

#endif