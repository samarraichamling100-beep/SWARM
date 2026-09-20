#include "gameinfo.cpp"
#include "playerbullet.cpp"

class SWARM 
{
    private:
    public:
    SPACESHIP mainSpaceships;
    INFOMENU Menu;
    PlayerBullet PB;
    //Setup
    void setup_elements()
    {
        mainSpaceships.setup_all_spaceships_elements();
    }
    //Draw
    void draw_elements()
    {
        HideCursor();
        ClearBackground(BLACK);
        Menu.Draw_Info(mainSpaceships.PlayerShip.Rect,PB.BulletList.size());
        PB.Draw_PlayerBullet();
        mainSpaceships.mouse.Draw_AimPointer();
        mainSpaceships.DrawPlayerSpaceship();
    }
    //Move
    void move_elements()
    {
        mainSpaceships.MovePlayerSpaceship();
        PB.Move_PlayerBullet();
    }
    //Check
    void check_elements()
    {
        PB.check_shooting(mainSpaceships.PlayerShip.Hitbox);
        mainSpaceships.check_coners_collision();
        PB.delete_unnecessary_bullet();
    }
    //Unload
    void unload_elements()
    {
        mainSpaceships.mouse.Unload_pointer();
        mainSpaceships.unload_PlrSpaceshipTexture();
    }
};