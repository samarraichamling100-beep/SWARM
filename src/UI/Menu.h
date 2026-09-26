#pragma once
#include "raylib.h"

class Menu
{
public:
    bool gameOver = false;

    void draw(Rectangle playerRect, int bulletCount, int enemyCount, int score, int secondsSurvived)
    {
        if (IsKeyPressed(KEY_TAB))
            debugPanelOpen = !debugPanelOpen;

        if (debugPanelOpen)
            drawDebugPanel(playerRect, bulletCount, enemyCount);

        drawScore(score);

        if (gameOver)
            drawGameOverScreen(score, secondsSurvived);
    }

private:
    bool debugPanelOpen = false;

    void drawDebugPanel(Rectangle playerRect, int bulletCount, int enemyCount)
    {
        DrawText(TextFormat("Fps: %02i", GetFPS()), 0, 0, 20, GREEN);
        DrawText(TextFormat("X: %03i", (int)playerRect.x), 0, 21, 20, GREEN);
        DrawText(TextFormat("Y: %03i", (int)playerRect.y), 0, 42, 20, GREEN);
        DrawText(TextFormat("Bullets: %03i", bulletCount), 0, 63, 20, GREEN);
        DrawText(TextFormat("Enemies: %04i", enemyCount), 0, 84, 20, GREEN);
    }

    void drawScore(int score)
    {
        DrawText(TextFormat("SCORE: %04i", score), 500, 30, 35, WHITE);
    }

    void drawGameOverScreen(int score, int secondsSurvived)
    {
        DrawText("GAME OVER", 400, 260, 60, RED);
        DrawText(TextFormat("SCORE: %04i", score), 400, 330, 30, GREEN);
        DrawText(TextFormat("Seconds survived: %04i", secondsSurvived), 400, 370, 25, GREEN);
        DrawText("Press R to restart", 400, 400, 20, BLUE);
    }
};
