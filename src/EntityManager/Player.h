#pragma once
#include "raylib.h"
#include "AimPointer.h"
#include "Constants.h"
#include <cmath>

struct PlayerShip
{
    Texture2D texture{};
    Rectangle source{};
    Rectangle rect{};
    Rectangle hitbox{};
    Vector2   origin{};
    float     rotation = 0.0f;
    float     speed    = Config::PlayerSpeed;
    int       health   = Config::PlayerStartHealth;
};

class Player
{
public:
    PlayerShip ship;
    AimPointer aim;
    int survivedSeconds = 0;

    void setup()
    {
        aim.setup();
        loadShip();
    }

    void update(bool gameOver)
    {
        tickSurvivalTimer(gameOver);
        move();
        keepInsideScreen();
    }

    void draw()
    {
        aim.draw();
        float dx = aim.mousePosition.x - ship.rect.x;
        float dy = aim.mousePosition.y - ship.rect.y;
        float angle = atan2f(dy, dx) * RAD2DEG + Config::PlayerRotationOffsetDeg;
        DrawTexturePro(ship.texture, ship.source, ship.rect, ship.origin, angle, WHITE);
    }

    void reset()
    {
        ship.rect    = {Config::PlayerStartX, Config::PlayerStartY,
                         (float)Config::PlayerSpriteSize, (float)Config::PlayerSpriteSize};
        ship.health   = Config::PlayerStartHealth;
        ship.rotation = 0.0f;
    }

    void unload()
    {
        aim.unload();
        UnloadTexture(ship.texture);
    }

private:
    int tickCounter = 0;

    void loadShip()
    {
        Image img = LoadImage("../Assets/PlrSpaceship.png");
        ImageResize(&img, Config::PlayerSpriteSize, Config::PlayerSpriteSize);
        ship.texture = LoadTextureFromImage(img);
        ship.source  = {0, 0, (float)img.width, (float)img.height};
        ship.rect    = {Config::PlayerStartX, Config::PlayerStartY, (float)img.width, (float)img.height};
        ship.origin  = {ship.rect.width / 2.0f, ship.rect.height / 2.0f};
        ship.hitbox  = {ship.rect.x, ship.rect.y, Config::PlayerHitboxSize, Config::PlayerHitboxSize};
        UnloadImage(img);
    }

    void tickSurvivalTimer(bool gameOver)
    {
        if (gameOver) return;
        tickCounter++;
        if (tickCounter >= 60)
        {
            survivedSeconds++;
            tickCounter = 0;
        }
    }

    void move()
    {
        float dt = GetFrameTime();
        if (IsKeyDown(KEY_W)) ship.rect.y -= ship.speed * dt;
        if (IsKeyDown(KEY_A)) ship.rect.x -= ship.speed * dt;
        if (IsKeyDown(KEY_D)) ship.rect.x += ship.speed * dt;
        if (IsKeyDown(KEY_S)) ship.rect.y += ship.speed * dt;

        // Hitbox is smaller than the sprite, so it's re-centered every frame.
        ship.hitbox.x = ship.rect.x - ship.rect.width / 9.0f;
        ship.hitbox.y = ship.rect.y - ship.rect.height / 9.0f;
    }

    void keepInsideScreen()
    {
        float offset = ship.rect.width / 9.0f;

        if (ship.hitbox.x < 0)
            ship.rect.x = offset;
        if (ship.hitbox.x + ship.hitbox.width > Config::ScreenWidth)
            ship.rect.x = Config::ScreenWidth - ship.hitbox.width + offset;
        if (ship.hitbox.y < 0)
            ship.rect.y = offset;
        if (ship.hitbox.y + ship.hitbox.height > Config::ScreenHeight)
            ship.rect.y = Config::ScreenHeight - ship.hitbox.height + offset;
    }
    // Note: the original had an empty DrawHPBar() (a for-loop with no body,
    // leftover from an unfinished feature) -- removed as dead code.
};
