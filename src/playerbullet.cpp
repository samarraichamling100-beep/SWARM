#include "raylib.h"
#include <raymath.h>
#include <iostream>
#include <vector>
#include <algorithm>

struct Bullet
{
    //The bullet structure
    float BulletRadius = 5.0f;
    Vector2 Position;
    //speed
    float Speed = 600.0f;
    //direction
    Vector2 Direction;

};


class PlayerBullet
{
    public:
    Bullet PlrBullet;
    Sound BulletSound;
    int tick = 0;
    std::vector<Bullet>BulletList = {};


    void Setup_bulletSound()
    {
        BulletSound = LoadSound("../assets/Bullet Sound.mp3");
        SetSoundVolume(BulletSound,0.4);
    }
    void Draw_PlayerBullet()
    {
        //Drawing all the bullets in bulletList
        for (auto & bullet : BulletList)
        {
            DrawCircle(bullet.Position.x,bullet.Position.y,bullet.BulletRadius,YELLOW);
        }
    }
    void check_shooting(Rectangle Hitbox)
    {
        tick ++;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && tick >= 20)
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
            newBullet.Position.x = shipPosition.x;
            newBullet.Position.y = shipPosition.y;
            //Applying the direction to new bullet
            newBullet.Direction = Direction;
            //Pushing back the new bullet to the bullet list
            BulletList.push_back(newBullet);
            PlaySound(BulletSound);
            tick = 0;
        }
    }
    void Move_PlayerBullet()
    {
        //delta time
        float dt = GetFrameTime();
        //We multiply the direction with speed * dt to get the speed to the mouse_position point when shooting
        for (auto &bullet : BulletList)
        {
            bullet.Position.x += bullet.Direction.x * bullet.Speed * dt;
            bullet.Position.y += bullet.Direction.y * bullet.Speed * dt;
        }
    }
    void delete_unnecessary_bullet()
    {
        //Deleting unnecssaray bullets (aka the bullets which are outside the screen)
        std::erase_if(BulletList,[](auto &bullet)
        {
            return 
            bullet.Position.y < 0 || 
            bullet.Position.y > 720 || 
            bullet.Position.x > 1280 || 
            bullet.Position.x < 0;
        }
    );
    }
    void Unload_bullet_sound()
    {
        UnloadSound(BulletSound);
    }
};