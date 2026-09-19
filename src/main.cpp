

#include "game.cpp"

int main ()
{

    int screenwidth = 1280;
    int screenheight = 720;
    int fps = 60;
    const char * title = "SWARM";

    InitWindow(screenwidth,screenheight,title);
    SetTargetFPS(fps);
    
    SWARM game;
    game.setup_elements();
    
    while(!WindowShouldClose())
    {
        ClearBackground(BLACK);
        game.check_elements();
        game.move_elements();
        BeginDrawing();
        game.draw_elements();
        EndDrawing();
    }

    game.unload_elements();
    return 0;
}