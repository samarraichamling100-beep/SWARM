#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include <vector>
#include <algorithm>
struct Bullet
{
    Rectangle Rect = {0,0,5,10};
    float Speed = 600.0f;
    Vector2 Direction;
};


class PlayerBullet
{
    public:
    Bullet PlrBullet;
    std::vector<Bullet>BulletList = {};
    std::vector<Vector2>PositionList{};

    void Draw_PlayerBullet()
    {
        for (auto & bullet : BulletList)
        {
            DrawRectangleRec(bullet.Rect,YELLOW);
        }
    }
    void check_shooting(Rectangle Hitbox)
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();

            // Ship center
            Vector2 shipPosition =
            {
                Hitbox.x + Hitbox.width / 4.5f,
                Hitbox.y + Hitbox.height / 4.5f
            };

            // Mouse - ship = direction from ship to mouse
            Vector2 Direction =
            {
                mousePosition.x - shipPosition.x,
                mousePosition.y - shipPosition.y
            };

            Direction = Vector2Normalize(Direction);

            Bullet newBullet;

            newBullet.Rect.x = shipPosition.x;
            newBullet.Rect.y = shipPosition.y;

            newBullet.Direction = Direction;

            BulletList.push_back(newBullet);
        }
    }
    void Move_PlayerBullet()
    {
        float dt = GetFrameTime();

        for (auto &bullet : BulletList)
        {
            bullet.Rect.x += bullet.Direction.x * bullet.Speed * dt;
            bullet.Rect.y += bullet.Direction.y * bullet.Speed * dt;
        }
    }
    void delete_unnecessary_bullet()
    {

        std::erase_if(BulletList,[](auto &bullet)
        {
            return 
            bullet.Rect.y < 0 || 
            bullet.Rect.y > 720 || 
            bullet.Rect.x > 1280 || 
            bullet.Rect.x < 0;
        }
    );
    }
};