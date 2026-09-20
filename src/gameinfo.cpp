#include <string>
#include "spaceship.cpp"


//Just some info to show
class INFOMENU
{
    public:
    int fps;
    Vector2 coardinates;
    void Draw_Info(Rectangle PlayerRect,int ListSize)
    {
    fps = GetFPS();
    coardinates = 
    {
        (PlayerRect.x),
        (PlayerRect.y)
    };
    DrawText(TextFormat("Fps : %02i",fps),0,0,25,GREEN);
    DrawText(TextFormat("X-Coardinate : %03i",static_cast<int>(coardinates.x)),0,25,25,GREEN);
    DrawText(TextFormat("Y-Coardinate : %03i",static_cast<int>(coardinates.y)),0,50,25,GREEN);
    DrawText(TextFormat("Alive-bullets : %03i",ListSize),0,75,25,GREEN);
    }
    private:

};