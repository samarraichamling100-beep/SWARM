#pragma once
#include "raylib.h"
#include ".gitignore"
#include "EntityManager\Bullet.h"
#include "EntityManager\Enemy.h"
#include "UI\Menu.h"
#include "System\Collision.h"

class Game
{
public:
    void setup()
    {
        player.setup();
        bullets.setup();
        enemies.setup();
    }

    // Simulation step: input, movement, spawning, collisions, cleanup.
    void update()
    {
        player.update(menu.gameOver);
        bullets.update(player.ship.hitbox);
        enemies.update(player.ship.rect);
        collisions.update(bullets, enemies, player, menu);
        handleRestartInput();
    }

    // Render step. Caller is responsible for Begin/EndDrawing + ClearBackground.
    void draw()
    {
        HideCursor();
        bullets.draw();
        player.draw();
        enemies.draw();
        menu.draw(player.ship.rect, (int)bullets.bullets.size(), (int)enemies.enemies.size(),
                  enemies.score, player.survivedSeconds);
    }

    void unload()
    {
        player.unload();
        bullets.unload();
    }

private:
    Player            player;
    BulletManager     bullets;
    EnemyManager      enemies;
    Menu              menu;
    CollisionManager  collisions;

    void restart()
    {
        player.reset();
        bullets.bullets.clear();
        enemies.enemies.clear();
        enemies.score = 0;
        menu.gameOver = false;
    }

    void handleRestartInput()
    {
        if (menu.gameOver && IsKeyPressed(KEY_R))
            restart();
    }
};
