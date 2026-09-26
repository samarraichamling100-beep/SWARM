#pragma once
#include "raylib.h"
#include "Constants.h"

class AimPointer
{
public:
    Vector2 mousePosition{};

    void setup()
    {
        Image img = LoadImage("../Assets/Pointer.png");
        ImageResize(&img, Config::AimPointerSpriteSize, Config::AimPointerSpriteSize);
        texture = LoadTextureFromImage(img);
        source  = {0, 0, (float)texture.width, (float)texture.height};
        rect    = {0, 0, (float)texture.width * Config::AimPointerScale, (float)texture.height * Config::AimPointerScale};
        origin  = {rect.width / 2.0f, rect.height / 2.0f};
        UnloadImage(img);
    }

    void draw()
    {
        mousePosition = GetMousePosition();
        rect.x = mousePosition.x;
        rect.y = mousePosition.y;
        DrawTexturePro(texture, source, rect, origin, 0.0f, WHITE);
    }

    void unload()
    {
        UnloadTexture(texture);
    }

private:
    Texture2D texture{};
    Rectangle source{};
    Rectangle rect{};
    Vector2   origin{};
};
