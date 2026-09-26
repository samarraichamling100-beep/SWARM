#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Constants.h"
#include <vector>
#include <algorithm>

struct Bullet
{
    Vector2 position{};
    Vector2 direction{};
    float   radius = Config::BulletRadius;
    float   speed  = Config::BulletSpeed;
};

class BulletManager
{
public:
    std::vector<Bullet> bullets;

    void setup()
    {
        // Fixed casing: original mixed "../Assets/..." and "../assets/...".
        // Works by accident on Windows, breaks on a case-sensitive filesystem.
        fireSound = LoadSound("../Assets/Bullet Sound.mp3");
        SetSoundVolume(fireSound, 0.4f);
    }

    void update(Rectangle playerHitbox)
    {
        handleShooting(playerHitbox);
        moveBullets();
        removeOffscreenBullets();
    }

    void draw()
    {
        for (const auto& bullet : bullets)
            DrawCircleV(bullet.position, bullet.radius, YELLOW);
    }

    void unload()
    {
        UnloadSound(fireSound);
    }

private:
    Sound fireSound{};
    int   cooldownTicks = 0;

    void handleShooting(Rectangle playerHitbox)
    {
        cooldownTicks++;
        if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT) || cooldownTicks < Config::BulletFireCooldownTicks)
            return;

        Vector2 shipCenter = {
            playerHitbox.x + playerHitbox.width / 4.5f,
            playerHitbox.y + playerHitbox.height / 4.5f
        };

        Bullet bullet;
        bullet.position  = shipCenter;
        bullet.direction = Vector2Normalize(Vector2Subtract(GetMousePosition(), shipCenter));
        bullets.push_back(bullet);

        PlaySound(fireSound);
        cooldownTicks = 0;
    }

    void moveBullets()
    {
        float dt = GetFrameTime();
        for (auto& bullet : bullets)
            bullet.position = Vector2Add(bullet.position, Vector2Scale(bullet.direction, bullet.speed * dt));
    }

    void removeOffscreenBullets()
    {
        std::erase_if(bullets, [](const Bullet& bullet)
        {
            return bullet.position.x < 0 || bullet.position.x > Config::ScreenWidth ||
                   bullet.position.y < 0 || bullet.position.y > Config::ScreenHeight;
        });
    }
};
