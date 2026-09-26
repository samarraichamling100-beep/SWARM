#include "raylib.h"
#include <vector>
#include <random>

struct Star
{
    Vector2 pos;
    float radius;
    float timer;
    Color color;
};

int main()
{
    InitWindow(1280, 720, "Twinkling Stars");
    SetTargetFPS(60);

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> xGen(0, 1280);
    std::uniform_real_distribution<float> yGen(0, 720);
    std::uniform_real_distribution<float> sizeGen(1, 3);

    std::vector<Star> stars;

    // Create 100 stars
    for (int i = 0; i < 100; i++)
    {
        stars.push_back({
            {xGen(gen), yGen(gen)},
            sizeGen(gen),
            0,
            WHITE
        });
    }

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        for (auto &star : stars)
        {
            star.timer += dt;

            // Every 1 second
            if (star.timer >= 1.0f)
            {
                star.timer = 0;

                // Random brightness
                int brightness = GetRandomValue(80, 255);

                star.color = {
                    255,
                    255,
                    255,
                    (unsigned char)brightness
                };
            }
        }

        BeginDrawing();

        ClearBackground(BLACK);

        for (auto &star : stars)
        {
            DrawCircleV(star.pos, star.radius, star.color);
        }

        EndDrawing();
    }

    CloseWindow();
}