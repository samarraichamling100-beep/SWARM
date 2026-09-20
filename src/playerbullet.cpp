#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct Bullet
{
    //The bullet structure
    Rectangle Rect = {0,0,5,10};
    //speed
    float Speed = 600.0f;
    //direction
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
        //Drawing all the bullets in bulletList
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
            //Using the hitbox since the shipRect is too big
            Vector2 shipPosition =
            {
                Hitbox.x + Hitbox.width / 4.5f,
                Hitbox.y + Hitbox.height / 4.5f
            };

            // Mouse - ship = direction from ship to mouse
            //directly did this because it is eaiser and creating other variable was unclean
            Vector2 Direction =
            {
                mousePosition.x - shipPosition.x,
                mousePosition.y - shipPosition.y
            };
            //Normalizing
            Direction = Vector2Normalize(Direction);
            //Creating new bullet to push
            Bullet newBullet;
            //StartingPos of new bullet
            newBullet.Rect.x = shipPosition.x;
            newBullet.Rect.y = shipPosition.y;
            //Applying the direction to new bullet
            newBullet.Direction = Direction;
            //Pushing back the new bullet to the bullet list
            BulletList.push_back(newBullet);
        }
    }
    void Move_PlayerBullet()
    {
        //delta time
        float dt = GetFrameTime();
        //We multiply the direction with speed * dt to get the speed to the mouse_position point when shooting
        for (auto &bullet : BulletList)
        {
            bullet.Rect.x += bullet.Direction.x * bullet.Speed * dt;
            bullet.Rect.y += bullet.Direction.y * bullet.Speed * dt;
        }
    }
    void delete_unnecessary_bullet()
    {
        //Deleting unnecssaray bullets (aka the bullets which are outside the screen)
        //A cool lambda funtion 
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