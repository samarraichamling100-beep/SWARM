#include "raylib.h"
#include <iostream>
#include <vector>
struct Bullet
{
    Rectangle Rect = {0,0,5,10};
    float Speed = 600.0f;
};


class PlayerBullet
{
    public:
    Bullet PlrBullet;
    std::vector<Bullet>BulletList = {};

    void Draw_PlayerBullet()
    {
        for (auto & bullet : BulletList)
        {
            DrawRectangleRec(bullet.Rect,YELLOW);
        }
    }
    void Move_PlayerBullet()
    {
        float dt = GetFrameTime();
        for (auto & bullet : BulletList)
        {
            bullet.Rect.y -= PlrBullet.Speed * dt;
        }
    }
    void check_shooting(Rectangle PlrShip)
    {
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {

            std::cout << "A new bullet has been created" << std::endl;
            PlrBullet.Rect.x = PlrShip.x;
            PlrBullet.Rect.y = PlrShip.y;
            BulletList.push_back(PlrBullet);
        }
    }
};