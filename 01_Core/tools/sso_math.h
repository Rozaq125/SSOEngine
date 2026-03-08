#ifndef SSO_MATH_H
#define SSO_MATH_H

#include "raylib.h"
#include <math.h>

// AABB Collision Detection (Rectangle vs Rectangle)
// Returns true if two rectangles are overlapping
bool CheckCollision(Rectangle rect1, Rectangle rect2) {
    return (rect1.x < rect2.x + rect2.width &&
            rect1.x + rect1.width > rect2.x &&
            rect1.y < rect2.y + rect2.height &&
            rect1.y + rect1.height > rect2.y);
}

// Clamp a Vector2 within specified boundaries
// Useful for keeping players inside the screen or a specific area
Vector2 ClampVector2(Vector2 val, float minX, float minY, float maxX, float maxY) {
    Vector2 result = val;
    
    if (result.x < minX) result.x = minX;
    if (result.x > maxX) result.x = maxX;
    if (result.y < minY) result.y = minY;
    if (result.y > maxY) result.y = maxY;
    
    return result;
}

// Calculate Euclidean distance between two points
float GetDistance(Vector2 v1, Vector2 v2) {
    return sqrtf(powf(v2.x - v1.x, 2) + powf(v2.y - v1.y, 2));
}

// Resolve Solid Collision
// Use this to prevent an object from passing through a wall
void ResolveCollision(Rectangle *player, Rectangle wall, Vector2 previousPos) {
    if (CheckCollision(*player, wall)) {
        player->x = previousPos.x;
        player->y = previousPos.y;
    }
}

#endif