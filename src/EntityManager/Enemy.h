#pragma once
#include "raylib.h"
#include "raymath.h"
#include "Constants.h"
#include <vector>
#include <random>
#include <algorithm>

struct Enemy
{
    Texture2D texture{};
    Rectangle source{};
    Rectangle rect{};
    Rectangle hitbox{0, 0, Config::EnemyHitboxSize, Config::EnemyHitboxSize};
    Vector2   origin{};
    Vector2   direction{};
    float     speed    = Config::EnemyDefaultSpeed;
    float     rotation = 0.0f;
    int       health   = Config::EnemyDefaultHealth;
};

// Owns every enemy on screen: spawning, chasing the player, drawing,
// and cleaning up the dead. (Only one enemy "type" today, the loadWeakEnemyTemplate
// name below is written so adding a second type doesn't require a rewrite.)
class EnemyManager
{
public:
    int score = 0;
    std::vector<Enemy> enemies;

    void setup()
    {
        loadWeakEnemyTemplate();
    }

    void update(Rectangle playerRect)
    {
        spawnTick();
        moveTowardsPlayer(playerRect);
        removeDeadEnemies();
    }

    void draw()
    {
        for (auto& enemy : enemies)
        {
            enemy.hitbox.x = enemy.rect.x - enemy.rect.width / 2.0f;
            enemy.hitbox.y = enemy.rect.y - enemy.rect.height / 2.0f;
            enemy.rotation += 0.5f;
            DrawTexturePro(enemy.texture, enemy.source, enemy.rect, enemy.origin, enemy.rotation, WHITE);
        }
    }

private:
    enum class Side { Left, Right, Top, Bottom };

    Enemy weakEnemyTemplate;
    int   spawnTimerTicks = 0;

    std::random_device rd;
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution<int> sideIndexGen{0, 3};

    std::uniform_real_distribution<float> topX{50, Config::ScreenWidth - 50};
    std::uniform_real_distribution<float> topY{50, 100};
    std::uniform_real_distribution<float> bottomX{50, Config::ScreenWidth - 50};
    std::uniform_real_distribution<float> bottomY{Config::ScreenHeight - 100, Config::ScreenHeight};
    std::uniform_real_distribution<float> rightX{Config::ScreenWidth - 150, Config::ScreenWidth - 50};
    std::uniform_real_distribution<float> rightY{50, Config::ScreenHeight - 50};
    std::uniform_real_distribution<float> leftX{50, 150};
    std::uniform_real_distribution<float> leftY{50, Config::ScreenHeight - 50};

    void loadWeakEnemyTemplate()
    {
        Image img = LoadImage("../Assets/WeakEnemy.png");
        weakEnemyTemplate.texture = LoadTextureFromImage(img);
        weakEnemyTemplate.source  = {0, 0, (float)img.width, (float)img.height};
        weakEnemyTemplate.rect    = {0, 0, (float)img.width, (float)img.height};
        weakEnemyTemplate.origin  = {weakEnemyTemplate.rect.width / 2.0f, weakEnemyTemplate.rect.height / 2.0f};
        UnloadImage(img);
    }

    Vector2 randomSpawnPosition()
    {
        switch (static_cast<Side>(sideIndexGen(gen)))
        {
            case Side::Left:  return { leftX(gen),   leftY(gen) };
            case Side::Right: return { rightX(gen),  rightY(gen) };
            case Side::Top:   return { topX(gen),    topY(gen) };
            default:          return { bottomX(gen), bottomY(gen) };
        }
    }

    void spawnTick()
    {
        spawnTimerTicks++;
        if (spawnTimerTicks < Config::EnemySpawnIntervalTicks) return;

        Enemy newEnemy = weakEnemyTemplate;
        // Original code force-sets a small draw size regardless of the
        // source image's actual dimensions -- preserved here on purpose.
        newEnemy.rect.width  = Config::EnemyHitboxSize;
        newEnemy.rect.height = Config::EnemyHitboxSize;

        Vector2 pos = randomSpawnPosition();
        newEnemy.rect.x = pos.x;
        newEnemy.rect.y = pos.y;

        enemies.push_back(newEnemy);
        spawnTimerTicks = 0;
    }

    void moveTowardsPlayer(Rectangle playerRect)
    {
        float dt = GetFrameTime();
        for (auto& enemy : enemies)
        {
            float dx = playerRect.x - enemy.rect.x;
            float dy = playerRect.y - enemy.rect.y;
            enemy.direction = Vector2Normalize({dx, dy});
            enemy.rect.x += enemy.direction.x * enemy.speed * dt;
            enemy.rect.y += enemy.direction.y * enemy.speed * dt;
        }
    }

    void removeDeadEnemies()
    {
        // (Renamed from "Delete_Killed_bullets" in the original -- that
        // function actually deleted enemies, not bullets.)
        std::erase_if(enemies, [this](const Enemy& enemy)
        {
            if (enemy.health <= 0)
            {
                score++;
                return true;
            }
            return false;
        });
    }
};
