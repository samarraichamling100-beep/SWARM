#pragma once

// All the "magic numbers" from the original code, named and in one place.
// If you want to retune the game, this is the only file you should need to touch.
namespace Config
{
    constexpr int ScreenWidth  = 1280;
    constexpr int ScreenHeight = 720;
    constexpr int TargetFPS    = 60;

    // --- Enemy ---
    constexpr int   EnemySpawnIntervalTicks = 180; // ~3 seconds at 60 fps
    constexpr float EnemyHitboxSize         = 30.0f;
    constexpr float EnemyDefaultSpeed       = 200.0f;
    constexpr int   EnemyDefaultHealth      = 50;

    // --- Player ---
    constexpr float PlayerStartX      = 400.0f;
    constexpr float PlayerStartY      = 400.0f;
    constexpr int   PlayerSpriteSize  = 200;
    constexpr float PlayerHitboxSize  = 35.0f;
    constexpr float PlayerSpeed       = 300.0f;
    constexpr int   PlayerStartHealth = 5;
    // The ship sprite's "forward" direction isn't aligned with local +X,
    // so this offset is added to atan2() to make the nose track the mouse.
    // (This was the "+65 degrees to make it work" number from your notes;
    // it's +87 in the actual code you pasted, kept as-is here.)
    constexpr float PlayerRotationOffsetDeg = 87.0f;

    // --- Bullets ---
    constexpr float BulletRadius            = 5.0f;
    constexpr float BulletSpeed             = 600.0f;
    constexpr int   BulletFireCooldownTicks = 20;
    constexpr int   BulletDamage            = 10;

    // --- Aim pointer ---
    constexpr int   AimPointerSpriteSize = 100;
    constexpr float AimPointerScale      = 1.5f;
}
