#include "menus.cpp"
#include "playerbullet.cpp"
#include "enemy.cpp"


class Collisions
{

    public:

    void check_bullets_collision(std::vector<Bullet> & BulletList, std::vector<Enemy> & EnemyList,Spaceship & sp,bool & gameover)
    {
        for(auto & enemy : EnemyList)
        {

            std::erase_if(EnemyList,[&](auto & enemy)
            {
                bool enemyHit = CheckCollisionRecs(enemy.Hitbox,sp.Hitbox);
                if(enemyHit)
                {
                    enemy.Health = 0;
                    sp.Health -= 1;
                    std:: cout << "SP- HEALTH : " << sp.Health << std::endl;
                    bool Dead  = sp.Health <= 0;
                    if(Dead)
                    {
                        gameover = true;
                    }
                    return true;
                }
                else
                {
                    return false;
                }
            } 
        );
            std::erase_if(BulletList,[&](auto & bullet)
            {
                bool hit = CheckCollisionCircleRec(bullet.Position,bullet.BulletRadius,enemy.Hitbox);
                if(hit)
                {
                    std::cout << "Bullet Collided" << std::endl;
                    std::cout << "Bullet is being removed" << std::endl;

                    enemy.Health -= 10;
                    return true;
                }
                else 
                {
                    return false;
                }
            }
            );
        }
    }
};