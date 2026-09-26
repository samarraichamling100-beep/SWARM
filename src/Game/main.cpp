#include "raylib.h"
#include "Constants.h"
#include "Game.h"

int main()
{
    InitWindow(Config::ScreenWidth, Config::ScreenHeight, "SWARM");
    SetTargetFPS(Config::TargetFPS);
    InitAudioDevice();

    Game game;
    game.setup();

    while (!WindowShouldClose())
    {
        game.update();

        BeginDrawing();
        ClearBackground(BLACK); // was called twice in the original; this is the only one that matters
        game.draw();
        EndDrawing();
    }

    game.unload();
    CloseAudioDevice(); // was missing in the original
    CloseWindow();      // was missing in the original
    return 0;
}
