#include "collision.cpp"
class SWARM 
{
    private:
    public:
    SPACESHIP mainSpaceships;
    INFOMENU Menu;
    PlayerBullet PB;
    ENEMIES enemy;
    Collisions Collision;
    //Setup
    void setup_elements()
    {
        PB.Setup_bulletSound();
        mainSpaceships.setup_all_spaceships_elements();
        enemy.set_up_enemy_elements();
    }
    //Draw
    void draw_elements()
    {
        HideCursor();
        ClearBackground(BLACK);
        PB.Draw_PlayerBullet();
        mainSpaceships.mouse.Draw_AimPointer();
        mainSpaceships.DrawPlayerSpaceship();
        enemy.Draw_WeakEnemy();
        Menu.ShowScore(enemy.Score);
        Menu.Draw_Info
        (
            mainSpaceships.PlayerShip.Rect,
            PB.BulletList.size(),
            enemy.EnemyList.size(),
            enemy.Score,
            mainSpaceships.secondSurived
        );
    }
    //Move
    void move_elements()
    {
        mainSpaceships.MovePlayerSpaceship();
        PB.Move_PlayerBullet();
        enemy.Move_WeakEnemy(mainSpaceships.PlayerShip.Rect);
    }
    //Check
    void check_elements()
    {
        mainSpaceships.GetTime(Menu.gameover);
        enemy.CreateNewEnemy();
        PB.check_shooting(mainSpaceships.PlayerShip.Hitbox);
        mainSpaceships.check_coners_collision();
        PB.delete_unnecessary_bullet();
        enemy.Delete_Killed_bullets();
        check_restart();
    }
    void check_collision()
    {

        Collision.check_bullets_collision(PB.BulletList,enemy.EnemyList,mainSpaceships.PlayerShip,Menu.gameover);
    }
    //Unload
    void unload_elements()
    {
        mainSpaceships.mouse.Unload_pointer();
        mainSpaceships.unload_PlrSpaceshipTexture();
        PB.Unload_bullet_sound();
    }
    void restart_game()
    {
    // Reset player
        mainSpaceships.PlayerShip.Rect = { 600, 300, 200, 200 };
        mainSpaceships.PlayerShip.Health = 100;
        mainSpaceships.PlayerShip.rotation = 0;

        // Remove all bullets
        PB.BulletList.clear();

        // Remove all enemies
        enemy.EnemyList.clear();

        // Reset score
        enemy.Score = 0;

        // Reset game over
        Menu.gameover = false;
    }
    void check_restart()
    {
        if (Menu.gameover && IsKeyPressed(KEY_R))
        {
            restart_game();
        }
    }
};