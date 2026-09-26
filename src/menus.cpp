#include <string>
#include "spaceship.cpp"


//Just some info to show
class INFOMENU
{
    public:
    int fps;
    bool open{};
    bool gameover{};

    Vector2 coardinates;

    void DrawDatabase(int ListSize,int EnemyListSize)
    {
        DrawText(TextFormat("Fps : %02i",fps),0,0,20,GREEN);
        DrawText(TextFormat("X-Coardinate : %03i",static_cast<int>(coardinates.x)),0,21,20,GREEN);
        DrawText(TextFormat("Y-Coardinate : %03i",static_cast<int>(coardinates.y)),0,21 * 2 ,20,GREEN);
        DrawText(TextFormat("Alive-bullets : %03i",ListSize),0,21 * 3,20,GREEN);
        DrawText(TextFormat("Alive-Enemies : %04i",EnemyListSize),0,21 * 4,20,GREEN);
    }



    void Draw_Info(Rectangle PlayerRect,int ListSize,int EnemyListSize,int & score,int secondSurived)
    {
    fps = GetFPS();
    coardinates = 
    {
        (PlayerRect.x),
        (PlayerRect.y)
    };

    if(open)
    {
        DrawDatabase( ListSize, EnemyListSize);
        if(IsKeyPressed(KEY_TAB))
        {
            open = false;
        }
    }
    if(IsKeyPressed(KEY_TAB))
    {
        open = true;
    }
    if (gameover)
    {
        DrawText("GAME OVER",400,260,60,RED);
        DrawText(TextFormat("SCORE : %04i",score),400,330,30,GREEN);
        DrawText(TextFormat("Seconds Surived : %04i",secondSurived),400,370,25,GREEN);
        DrawText("press R to Restart",400,400,20,BLUE);
    }
    }
    void ShowScore(int score)
    {
        DrawText(TextFormat("SCORE : %04i",score),500,30,35,WHITE);
    }
    private:

};