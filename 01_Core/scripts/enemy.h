#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "../tools/sso_provider.h"
#include "../tools/sso_logger.h"
#include "player.h"
#include <vector>
#include <algorithm>

// Forward declaration
class Player;

// External global player reference
extern Player* player;

enum class EnemyType { MERVIN, CAR };

class Enemy {
public:
    Vector2 position;
    float speed;
    Texture2D texture;
    float scale;
    Rectangle collisionRect;
    bool isActive;
    int health;
    EnemyType type;

    // Animasi Variables
    int frameCount;
    int currentFrame;
    float frameTimer;
    float frameSpeed;
    float direction;

    Enemy(EnemyType t, float x, float y) {
        type = t;
        position = { x, y };
        scale = (type == EnemyType::MERVIN) ? 2.5f : 1.5f; // Semua lebih kecil
        isActive = true;
        health = (type == EnemyType::MERVIN) ? 5 : 1;
        direction = (type == EnemyType::MERVIN) ? 1.0f : 1.0f; // Mervin ngadep kanan (ngejar), Mobil ngadep bawah
        
        if (type == EnemyType::MERVIN) {
            texture = SSO::Provider::LoadTextureFromBundle("assets.sso", "killer/mervin.png");
            frameCount = 8;
            speed = 180.0f; // Lebih cepat biar ngejar
            frameSpeed = 0.15f; // Animasi lebih cepat
        } else {
            texture = SSO::Provider::LoadTextureFromBundle("assets.sso", "cars/cars1.png");
            frameCount = 5; // 5 jenis mobil
            speed = 250.0f; // Mobil jatuh lebih cepat
            // Pilih satu mobil random dari 5 pilihan
            currentFrame = GetRandomValue(0, 4); 
            frameSpeed = 0; // Mobil nggak animasi ganti bentuk
        }
        
        frameTimer = 0;
        if (type == EnemyType::MERVIN) currentFrame = 0;

        UpdateCollisionRect();
    }
    
    void UpdateCollisionRect() {
        float frameWidth = (float)texture.width / frameCount;
        collisionRect = { position.x, position.y, frameWidth * scale, (float)texture.height * scale };
    }
    
    void Update(float deltaTime) {
        if (!isActive) return;
        
        if (type == EnemyType::MERVIN) {
            // Mervin AI: Ngejar player dari belakang
            if (player && player->position.x > position.x + 50) {
                // Player di depan, Mervin ngadep kanan dan ngejar
                direction = 1.0f;
                position.x += speed * direction * deltaTime;
            } else {
                // Player di belakang, Mervin ngadep kiri dan mundur
                direction = -1.0f;
                position.x += speed * direction * deltaTime;
            }
            
            // Animasi lari
            frameTimer += deltaTime;
            if (frameTimer >= frameSpeed) {
                frameTimer = 0;
                currentFrame = (currentFrame + 1) % frameCount;
            }
        } else {
            // Mobil jatoh dari atas ke bawah
            position.y += speed * deltaTime; // Gerak vertikal ke bawah
            // Mobil nggak perlu animasi frame (cuma 1 mobil per spawn)
        }
        
        UpdateCollisionRect();
    }
    
    void Draw() {
        if (!isActive) return;
        
        float frameWidth = (float)texture.width / frameCount;
        Rectangle source = { (float)currentFrame * frameWidth, 0, frameWidth, (float)texture.height };
        
        // Flip logic: Hanya flip jika arahnya ke kiri
        if (direction < 0) {
            source.width *= -1;
        }

        Rectangle dest = { position.x, position.y, frameWidth * scale, (float)texture.height * scale };
        
        // Warna tint: Mervin putih, Mobil warna-warni random
        Color carColors[] = { RED, BLUE, GREEN, YELLOW, PURPLE };
        Color tint = (type == EnemyType::MERVIN) ? WHITE : carColors[currentFrame % 5];
        
        DrawTexturePro(texture, source, dest, {0,0}, 0.0f, tint);
        
        // Health bar cuma buat Mervin
        if (type == EnemyType::MERVIN) {
            DrawRectangle(position.x, position.y - 15, (frameWidth * scale) * (health / 5.0f), 5, RED);
        }
    }
    
    void TakeDamage() {
        health--;
        if (health <= 0) isActive = false;
    }
    
    ~Enemy() { UnloadTexture(texture); }
};

class EnemyManager {
public:
    std::vector<Enemy*> enemies;
    float spawnTimer = 0;
    
    EnemyManager() {
        // Mervin muncul dari kiri layar (ngejar player)
        enemies.push_back(new Enemy(EnemyType::MERVIN, -100, 450));
        spawnTimer = 0;
    }
    
    void Update(float dt) {
        // Auto spawn mobil dari atas tiap 2.5 detik
        spawnTimer += dt;
        if (spawnTimer > 2.5f) {
            // Mobil muncul dari atas layar dengan posisi X random
            float randomX = GetRandomValue(100, 1100);
            enemies.push_back(new Enemy(EnemyType::CAR, randomX, -100)); // Muncul dari atas
            spawnTimer = 0;
        }

        for (auto enemy : enemies) enemy->Update(dt);
        
        // Hapus enemy yang inactive
        enemies.erase(std::remove_if(enemies.begin(), enemies.end(), 
            [](Enemy* e) { if(!e->isActive){ delete e; return true; } return false; }), enemies.end());
    }
    
    void Draw() { for (auto e : enemies) e->Draw(); }
    
    ~EnemyManager() { for (auto e : enemies) delete e; enemies.clear(); }
};

#endif