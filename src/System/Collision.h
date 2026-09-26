#pragma once
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "Menu.h"
#include "Constants.h"
#include <algorithm>

class CollisionManager
{
public:
    void update(BulletManager& bulletMgr, EnemyManager& enemyMgr, Player& player, Menu& menu)
    {
        resolveEnemyVsPlayer(enemyMgr.enemies, player, menu);
        resolveBulletsVsEnemies(bulletMgr.bullets, enemyMgr.enemies);
    }

private:
    void resolveEnemyVsPlayer(std::vector<Enemy>& enemies, Player& player, Menu& menu)
    {
        std::erase_if(enemies, [&](const Enemy& enemy)
        {
            bool hit = CheckCollisionRecs(enemy.hitbox, player.ship.hitbox);
            if (!hit) return false;

            player.ship.health -= 1;
            if (player.ship.health <= 0)
                menu.gameOver = true;
            return true;
        });
    }

    void resolveBulletsVsEnemies(std::vector<Bullet>& bullets, std::vector<Enemy>& enemies)
    {
        // Original bug: this used to call std::erase_if(enemies, ...) from
        // *inside* a range-for loop over that same enemies vector -- erasing
        // from a container while iterating it is undefined behavior. Here we
        // erase_if over `bullets` (the outer container) and only read/modify
        // individual enemy health inside, never resize `enemies`, in the inner loop.
        std::erase_if(bullets, [&](const Bullet& bullet)
        {
            for (auto& enemy : enemies)
            {
                if (CheckCollisionCircleRec(bullet.position, bullet.radius, enemy.hitbox))
                {
                    enemy.health -= Config::BulletDamage;
                    return true; // bullet consumed, stop checking further enemies
                }
            }
            return false;
        });
    }
};
