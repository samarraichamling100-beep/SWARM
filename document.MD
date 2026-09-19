learned to make triangles in raylib.
To move it we have to add points in order to make it.
Delta time is a timeframe which is based on fps.
For ep(if fps = 60)
{
    dt = 1/60
}



Now the rotation of spaceship
I dont know of anyway to do it for a triangle so i didnt know to rotate the triangle.
So I decided to use an image for this because i know how to make rotation work with this 
Now the math for making rotation I understood like this

    mouse.pos.x - object.pos.x =  change of object position aka dx of mosuse.pos.x
    same for the other one but with y
    mouse.pos.y - object.pos.y =  change of object position aka dy of mouse.pos.y

these are dx and dy.

    There is formula with dx and dy 
    angleInRadian = atan2(dy/dx);
    angleInDegree = (angleInRadian * PI/180);
    atan2 is a func that gets the rotation of two coardinate (x,y)

I understand math but I cannot make sense of this completely

when i implemented this into my code it worked but the angle was off
I had to add 65 degree to make it work


Learned to use TextFormat



Will do everything other in other days
