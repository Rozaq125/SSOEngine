#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "tools/sso_math.h"

// Changed 'floor' to 'ground' to avoid conflict with math.h floor() function
Rectangle player = { 0, 0, 50, 50 };
Rectangle ground = { 0, 650, 1280, 70 }; 
Rectangle wall = { 600, 500, 200, 40 };  

float velocityY = 0.0f;
const float gravity = 1500.0f; 
const float jumpForce = -700.0f; 
bool isGrounded = false;
Color playerColor = BLUE;

void Start() {
    player.x = 100.0f;
    player.y = 100.0f;
}

void Update(float dt) {
    float speed = 400.0f;
    Vector2 oldPos = { player.x, player.y };

    if (IsKeyDown(KEY_D)) player.x += speed * dt;
    if (IsKeyDown(KEY_A)) player.x -= speed * dt;

    velocityY += gravity * dt;
    player.y += velocityY * dt;

    isGrounded = false; 
    
    // Check collision with ground (Fixed name)
    if (CheckCollision(player, ground)) {
        player.y = ground.y - player.height;
        velocityY = 0;
        isGrounded = true;
    }
    
    if (CheckCollision(player, wall)) {
        if (velocityY > 0 && oldPos.y + player.height <= wall.y) {
            player.y = wall.y - player.height;
            velocityY = 0;
            isGrounded = true;
            playerColor = RED;
        }
    } else {
        playerColor = BLUE;
    }

    if (IsKeyPressed(KEY_SPACE) && isGrounded) {
        velocityY = jumpForce;
        isGrounded = false;
    }
    
    Vector2 clampedPos = ClampVector2((Vector2){player.x, player.y}, 0, 0, 1280 - player.width, 720);
    player.x = clampedPos.x;
}

void Render() {
    DrawText("SSOEngine Platformer: A/D to Move, SPACE to Jump", 10, 10, 20, RAYWHITE);
    
    DrawRectangleRec(ground, DARKGREEN); // Fixed name
    DrawRectangleRec(wall, GRAY);
    DrawRectangleRec(player, playerColor);
}

#endif