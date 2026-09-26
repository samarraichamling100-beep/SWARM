#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <random>
#include <string>


struct Enemy
{
    Texture Textur;
    Rectangle Source;
    Rectangle Rect;
    Rectangle Hitbox = {0,0,30,30};
    Vector2 origin;
    float Speed;
    float rotation;
    int Health;
    Vector2 Direction;

};


class ENEMIES
{
    private:

    public:
    int Score = 0;
    std::vector<Enemy>EnemyList;
    int tick = 0;
    Enemy WeakEnemy;
    //list of possibles sides in the screen
    std::vector<std::string>Sides = {"Left","Right","Top","Bottom"};
    std::string Side;
    //defining random
    std::random_device rd;
    std::mt19937 gen{rd()};
    //making the numIndex generator for the sideslist
    std::uniform_int_distribution<int> SideIndexGen{
    0, static_cast<int>(Sides.size()) - 1
    };
    //The Position Generators For All Sides

    //Top Side
    std::uniform_real_distribution<float> TopSideX{50,1230};
    std::uniform_real_distribution<float> TopSideY{50,100};
    //Bottom Side
    std::uniform_real_distribution<float> BottomSideX{50,1230};
    std::uniform_real_distribution<float> BottomSideY{620,720};
    //Right Side
    std::uniform_real_distribution<float> RightSideX{1130,1230};
    std::uniform_real_distribution<float> RightSideY{50,670};
    //Left Side
    std::uniform_real_distribution<float> LeftSideX{50,150};
    std::uniform_real_distribution<float> LeftSideY{50,670};

    std::string GetSide()
    {
        int SideIndex = SideIndexGen(gen);
        std::cout << "Side : " << Sides[SideIndex] << std::endl;
        return Sides[SideIndex];
    }
    void getWeakEnemy_Position()
    {
        WeakEnemy.Rect.width = 30.0f;
        WeakEnemy.Rect.height = 30.0f;
        if(Side == "Left")
        {
            WeakEnemy.Rect.x = LeftSideX(gen);
            WeakEnemy.Rect.y = LeftSideY(gen);
            std::cout << "WeakEnemy.Rect.x : " << WeakEnemy.Rect.x << std::endl;
            std::cout << "WeakEnemy.Rect.y : " << WeakEnemy.Rect.y << std::endl;
        }
        else if(Side == "Right")
        {
            WeakEnemy.Rect.x = RightSideX(gen);
            WeakEnemy.Rect.y = RightSideY(gen);
            std::cout << "WeakEnemy.Rect.x : " << WeakEnemy.Rect.x << std::endl;
            std::cout << "WeakEnemy.Rect.y : " << WeakEnemy.Rect.y << std::endl;
        }
        else if(Side == "Top")
        {
            WeakEnemy.Rect.x = TopSideX(gen);
            WeakEnemy.Rect.y = TopSideY(gen);
            std::cout << "WeakEnemy.Rect.x : " << WeakEnemy.Rect.x << std::endl;
            std::cout << "WeakEnemy.Rect.y : " << WeakEnemy.Rect.y << std::endl;
        }
        else if(Side == "Bottom")
        {
            WeakEnemy.Rect.x = BottomSideX(gen);
            WeakEnemy.Rect.y = BottomSideY(gen);
            std::cout << "WeakEnemy.Rect.x : " << WeakEnemy.Rect.x << std::endl;
            std::cout << "WeakEnemy.Rect.y : " << WeakEnemy.Rect.y << std::endl;
        }
    }

    void set_up_enemy_elements()
    {
        set_up_WeakEnemy();
    }

    void set_up_WeakEnemy()
    {
        Image WeakEnemyImg = LoadImage("../Assets/WeakEnemy.png");
        WeakEnemy.Textur = LoadTextureFromImage(WeakEnemyImg);
        WeakEnemy.Source = 
        {
            0,
            0,
            static_cast<float>(WeakEnemyImg.width),
            static_cast<float>(WeakEnemyImg.height)
        };
        WeakEnemy.Rect = 
        {
            0,
            0,
            static_cast<float>(WeakEnemyImg.width),
            static_cast<float>(WeakEnemyImg.height)
        };
        WeakEnemy.origin = 
        {
            .x = WeakEnemy.Rect.width/2,
            .y = WeakEnemy.Rect.height/2
        };
        WeakEnemy.rotation = 0.0f;
        WeakEnemy.Speed = 200.0f;
        WeakEnemy.Health = 50;
        UnloadImage(WeakEnemyImg);

    }
    void CreateNewEnemy()
    {
        tick ++;
        if(tick >= 180)
        {
            std::cout << "new enemy has been created" << std::endl;
            Side = GetSide();
            getWeakEnemy_Position();
            EnemyList.push_back(WeakEnemy);
            tick = 0;
        }
    }
    void Draw_WeakEnemy()
    {
        for(auto & Enemy : EnemyList)
        {
            Enemy.Hitbox.x = Enemy.Rect.x - Enemy.Rect.width/2;
            Enemy.Hitbox.y = Enemy.Rect.y - Enemy.Rect.height/2;
            Enemy.rotation += 0.5f;
            DrawTexturePro(Enemy.Textur,Enemy.Source,Enemy.Rect,Enemy.origin,Enemy.rotation,WHITE);
        }
    }
    void Move_WeakEnemy(Rectangle PlayerRect)
    {
        float dt = GetFrameTime();
        for(auto & Enemy : EnemyList)
        {
            float dx = PlayerRect.x - Enemy.Rect.x;
            float dy = PlayerRect.y - Enemy.Rect.y;
            Enemy.Direction = Vector2Normalize({dx,dy});
            Enemy.Rect.x += Enemy.Direction.x * Enemy.Speed * dt;
            Enemy.Rect.y += Enemy.Direction.y * Enemy.Speed * dt;
        }
    }
    void Delete_Killed_bullets()
    {
        std::erase_if(EnemyList,[&](auto & enemy)
        {
            bool Died = enemy.Health <= 0;
            if(Died)
            {
                Score ++;
                return true;
            }
            else
            {
                return false;
            };
        }
    );
    }
};