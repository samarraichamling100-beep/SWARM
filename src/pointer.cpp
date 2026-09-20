#include <raylib.h>
#include <raymath.h>



struct TexturePro
{
    Texture Text;
    Rectangle Source;
    Rectangle Rect;
    Vector2 origin;
    float rotation = 0.0f;
};



class AIMTRACKER
{
    private:
    public:
    Vector2 MousePos;
    TexturePro AimPointer;
    void get_mousePosition()
    {
        MousePos = GetMousePosition();
    }
    void setup_AimPointer()
    {
        //Defing things needed for it to draw the texture
        Image AimPointerImg = LoadImage("../Assets/Pointer.png");
        ImageResize(&AimPointerImg,100,100);
        AimPointer.Text = LoadTextureFromImage(AimPointerImg);
        AimPointer.Source = 
        {
            0,
            0,
            static_cast<float>(AimPointer.Text.width),
            static_cast<float>(AimPointer.Text.height)
        };
        AimPointer.Rect = 
        {
            MousePos.x,
            MousePos.y,
            static_cast<float>(AimPointer.Text.width) * 1.5f,
            static_cast<float>(AimPointer.Text.height) * 1.5f
        };
        AimPointer.origin = 
        {
            .x = AimPointer.Rect.width/2,
            .y = AimPointer.Rect.height/2
        };
        UnloadImage(AimPointerImg);
    }
    void Draw_AimPointer()
    {
        //Drawing the Aim Pointer
        get_mousePosition();
        AimPointer.Rect.x = MousePos.x;
        AimPointer.Rect.y = MousePos.y;
        DrawTexturePro
        (
            AimPointer.Text,
            AimPointer.Source,
            AimPointer.Rect,
            AimPointer.origin,
            AimPointer.rotation,
            WHITE
        );
    }
    void Unload_pointer()
    {
        //Unloading when not necessary
        UnloadTexture(AimPointer.Text);
    }
};