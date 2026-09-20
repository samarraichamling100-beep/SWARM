#include "pointer.cpp"
#include <iostream>


struct Spaceship
{
    Texture Textur;
    Rectangle Source;
    Rectangle Rect;
    Rectangle Hitbox;
    Vector2 origin;
    float rotation;
    float speed;
};


class SPACESHIP 
{   
    private:
    public:
    Spaceship PlayerShip;
    AIMTRACKER mouse;

    void setup_all_spaceships_elements()
    {
        mouse.setup_AimPointer();
        SetupPlayerShip();
    }
    void SetupPlayerShip()
    {
        Image PlrSpaceshipImg = LoadImage("../Assets/PlrSpaceship.png");
        ImageResize(&PlrSpaceshipImg,200,200);
        PlayerShip.Textur = LoadTextureFromImage(PlrSpaceshipImg);
        PlayerShip.Source = 
        {
            0,
            0,
            (float)PlrSpaceshipImg.width ,
            (float)PlrSpaceshipImg.height 
        };
        PlayerShip.Rect =
        {
            400.0f,
            400.0f,
            (float)PlrSpaceshipImg.width,
            (float)PlrSpaceshipImg.height
        };
        std::cout << "Width : " << PlrSpaceshipImg.width << std::endl;
        std::cout << "Height : " << PlrSpaceshipImg.height << std::endl;
        PlayerShip.origin = 
        {
            .x = PlayerShip.Rect.width/2,
            .y = PlayerShip.Rect.height/2
        }; 
        PlayerShip.Hitbox = 
        {
            PlayerShip.Rect.x,
            PlayerShip.Rect.y,
            35.0f,
            35.0f
        };
        PlayerShip.rotation = 0.0f;
        PlayerShip.speed = 300;
    }   

    void DrawPlayerSpaceship()
    {
        float DifferenceInX = mouse.MousePos.x - PlayerShip.Rect.x;
        float DifferenceInY = mouse.MousePos.y - PlayerShip.Rect.y;

        float Angle = atan2(DifferenceInY,DifferenceInX) * RAD2DEG + 65.0f;
        DrawTexturePro
        (
            PlayerShip.Textur
            ,PlayerShip.Source
            ,PlayerShip.Rect
            ,PlayerShip.origin
            ,Angle
            ,WHITE
        );

    }

    void MovePlayerSpaceship()
    {
        float dt = GetFrameTime();
        if(IsKeyDown(KEY_W))PlayerShip.Rect.y -= PlayerShip.speed * dt;
        if(IsKeyDown(KEY_A))PlayerShip.Rect.x -= PlayerShip.speed * dt;
        if(IsKeyDown(KEY_D))PlayerShip.Rect.x += PlayerShip.speed * dt;
        if(IsKeyDown(KEY_S))PlayerShip.Rect.y += PlayerShip.speed * dt;
        PlayerShip.Hitbox.x = PlayerShip.Rect.x - PlayerShip.Rect.width/9.0f;
        PlayerShip.Hitbox.y = PlayerShip.Rect.y - PlayerShip.Rect.height/9.0f;
    }
    void check_coners_collision()
    {

        float offset = PlayerShip.Rect.width / 9.0f;

        // Left
        if (PlayerShip.Hitbox.x < 0)
        {
            PlayerShip.Rect.x = offset;
        }

        // Right
        if (PlayerShip.Hitbox.x + PlayerShip.Hitbox.width > 1280)
        {
            PlayerShip.Rect.x = 1280 - PlayerShip.Hitbox.width + offset;
        }

        // Top
        if (PlayerShip.Hitbox.y < 0)
        {
            PlayerShip.Rect.y = offset;
        }

        // Bottom
        if (PlayerShip.Hitbox.y + PlayerShip.Hitbox.height > 720)
        {
            PlayerShip.Rect.y = 720 - PlayerShip.Hitbox.height + offset;
        }
    }
    void unload_PlrSpaceshipTexture()
    {
        UnloadTexture(PlayerShip.Textur);
    }
};
