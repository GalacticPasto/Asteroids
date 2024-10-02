#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define SCREENWIDTH  1280
#define SCREENHEIGHT 720 

#define RADIUS 20 

#define centerX SCREENWIDTH/2
#define centerY SCREENHEIGHT/2


struct player 
{
    float angle;
    Vector2 acceleration;
    Vector2 velocity;
    Vector2 pos;
    Vector2 up;
    Vector2 left;
    Vector2 right;
};

void printVector(Vector2* vec);
void apply2dRotation(struct player* ship,Vector2* vec,float* angle);

int main(void)
{

    struct player ship= 
    {
        .pos = {(float)centerX,(float)centerY},
        .up = {ship.pos.x, ship.pos.y - RADIUS},
    };
    Vector2 size = {5,5}; 

    float rad0 = 4.7123;

    float rad1 = 2.0944;
    ship.right= ship.up;
    apply2dRotation(&ship,&ship.right,&rad1);

    float rad2 = 4.1887;
    ship.left= ship.up;
    apply2dRotation(&ship,&ship.left,&rad2);

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Asteroids");

    SetTargetFPS(60);               
    int key = KEY_W;
    float mag = 0.01;
    while (!WindowShouldClose())    
    {
        if(IsKeyDown(key))
        {
            switch(key)
            {
                case KEY_W:
                    {
                        ship.acceleration.y -= mag;
                    }break;
                case KEY_S:
                    {
                        ship.acceleration.y += mag;
                    }break;
                case KEY_A:
                    {
                        ship.acceleration.x -= mag;
                    }break;
                case KEY_D:
                    {
                        ship.acceleration.x += mag;
                    }break;
            } 
        }
        else
        {
            switch(key)
            {
                case KEY_W:
                    {
                        ship.acceleration.y = 0;
                    }break;
                case KEY_S:
                    {
                        ship.acceleration.y = 0;
                    }break;
                case KEY_A:
                    {
                        ship.acceleration.x = 0;
                    }break;
                case KEY_D:
                    {
                        ship.acceleration.x = 0;
                    }break;
            } 
            key = GetKeyPressed();
        }
        
    
        ship.velocity.x += ship.acceleration.x;
        ship.velocity.y += ship.acceleration.y;

        if(ship.velocity.x > 5)
        {
            ship.velocity.x = 5;
        }
        else if(ship.velocity.x < -5)
        {
            ship.velocity.x = -5;
        }
        if(ship.velocity.y > 5)
        {
            ship.velocity.y = 5;
        }
        else if(ship.velocity.y < -5)
        {
            ship.velocity.y = -5;
        }

        ship.pos.x += ship.velocity.x;
        ship.pos.y += ship.velocity.y;
        ship.up.x += ship.velocity.x;
        ship.up.y += ship.velocity.y;
        ship.right.x += ship.velocity.x;
        ship.right.y += ship.velocity.y;
        ship.left.x += ship.velocity.x;
        ship.left.y += ship.velocity.y;

        ////ship.right= ship.up;
        //float ang1 = rad1 + ship.angle;
        //apply2dRotation(&ship,&ship.right,&ang1);

        //ship.left= ship.up;
        //float ang2 = rad2 + ship.angle;
        //apply2dRotation(&ship,&ship.left,&ang2);
        apply2dRotation(&ship,&ship.up,&ship.angle);
        apply2dRotation(&ship,&ship.left,&ship.angle);
        apply2dRotation(&ship,&ship.right,&ship.angle);


        if(ship.pos.x > SCREENWIDTH)
        {
            ship.pos.x -= SCREENWIDTH;
            ship.up.x -= SCREENWIDTH;
            ship.left.x -= SCREENWIDTH;
            ship.right.x -= SCREENWIDTH;
        }
        else if(ship.pos.x < 0)
        {
            ship.pos.x += SCREENWIDTH - RADIUS;
            ship.up.x += SCREENWIDTH - RADIUS;
            ship.left.x += SCREENWIDTH - RADIUS;
            ship.right.x += SCREENWIDTH - RADIUS;
        }
        if(ship.pos.y > SCREENHEIGHT)
        {
            ship.pos.y -= SCREENHEIGHT;
            ship.up.y -= SCREENHEIGHT;
            ship.left.y -= SCREENHEIGHT;
            ship.right.y -= SCREENHEIGHT;
        }
        else if(ship.pos.y < 0)
        {
            ship.pos.y += SCREENHEIGHT - RADIUS;
            ship.up.y += SCREENHEIGHT - RADIUS;
            ship.left.y += SCREENHEIGHT - RADIUS;
            ship.right.y += SCREENHEIGHT - RADIUS;
        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTriangle(ship.up,ship.left,ship.right,WHITE);
        //DrawPixelV(ship.pos,);
        DrawRectangleV(ship.left,size,GREEN);
        DrawRectangleV(ship.up,size,RED);
        DrawRectangleV(ship.right,size,BLUE);
        DrawRectangleV(ship.pos,size,YELLOW);
        //
        //DrawCircleLinesV(ship.pos, RADIUS, RED);
        EndDrawing();
    }
    CloseWindow();        
    return 0;
}

void apply2dRotation(struct player* ship, Vector2* vec,float* angle)
{
    float newAngle = *angle;
    if(newAngle < 0)
    {
        newAngle = (2 * PI) + newAngle;
    }

    //float newX = (vec->x - (float)centerX) * cos(newAngle) - (vec->y - (float)centerY)* sin(newAngle); 
    //float newY = (vec->x - (float)centerX) * sin(newAngle) + (vec->y - (float)centerY)* cos(newAngle); 

    float newX = (vec->x - ship->pos.x) * cos(newAngle) - (vec->y - ship->pos.y)* sin(newAngle); 
    float newY = (vec->x - ship->pos.x) * sin(newAngle) + (vec->y - ship->pos.y)* cos(newAngle); 

    vec->x = newX + ship->pos.x;
    vec->y = newY + ship->pos.y;

    return;
}

void printVector(Vector2* vec)
{
    printf("%f %f\n",vec->x , vec->y);
}
