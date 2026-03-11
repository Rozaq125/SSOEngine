#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "../tools/sso_provider.h"
#include "../tools/sso_logger.h"

class Player {
public:
    Vector2 position;
    float speed;
    Texture2D texture;
    bool isFacingRight;
    float scale;
    Rectangle collisionRect;
    
    // Animasi Variables
    int frameCount;
    int currentFrame;
    float frameTimer;
    float frameSpeed;

    Player() {
        isFacingRight = true;
        scale = 2.0f; // Lebih kecil biar proporsional
        speed = 300.0f;

        // Init Animasi
        frameCount = 8; // Sesuai info lu (512/64 = 8)
        currentFrame = 0;
        frameTimer = 0.0f;
        frameSpeed = 0.12f; // Animasi smooth
        
        // Load Gargant dari bundle
        texture = SSO::Provider::LoadTextureFromBundle("assets.sso", "player/gargant.png");
        
        if (texture.id <= 0) {
            SSO::Logger::Log(SSO::Logger::Level::ERROR, "Texture not found at player/gargant.png");
        }
        
        // Posisi awal di tengah layar, di atas tanah
        position = { 400, 600 - (64 * scale) }; // 600 adalah ground.y
        UpdateCollisionRect();
    }

    void UpdateCollisionRect() {
        // Lebar per frame adalah 64px
        float frameWidth = 64.0f; 
        collisionRect = { position.x, position.y, frameWidth * scale, 64 * scale };
    }

    void Update() {
        float dt = GetFrameTime();
        bool isMoving = false;

        if (IsKeyDown(KEY_A)) { position.x -= speed * dt; isFacingRight = false; isMoving = true; }
        if (IsKeyDown(KEY_D)) { position.x += speed * dt; isFacingRight = true; isMoving = true; }

        // Update Frame Animasi
        if (isMoving) {
            frameTimer += dt;
            if (frameTimer >= frameSpeed) {
                frameTimer = 0;
                currentFrame = (currentFrame + 1) % frameCount;
            }
        } else {
            currentFrame = 0; // Balik ke pose diem kalau gak jalan
        }

        UpdateCollisionRect();
    }

    void Draw() {
        float frameWidth = (float)texture.width / frameCount; // 64px
        
        // Potong spritesheet berdasarkan currentFrame
        Rectangle source = { (float)currentFrame * frameWidth, 0, frameWidth, (float)texture.height };
        if (!isFacingRight) source.width *= -1;
        
        Rectangle dest = { position.x, position.y, frameWidth * scale, (float)texture.height * scale };
        
        DrawTexturePro(texture, source, dest, {0,0}, 0.0f, WHITE);
    }

    ~Player() { UnloadTexture(texture); }
};

#endif