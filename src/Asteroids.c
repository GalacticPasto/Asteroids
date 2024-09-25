#include <stdio.h>
#include "raylib.h"
#include "raymath.h"


#define screenWidth  1280
#define screenHeight 720 

#define radius 20 

#define centerX screenWidth/2
#define centerY screenHeight/2


struct player 
{
    float angle;
    float acceleration;
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
        .up = {ship.pos.x, ship.pos.y - radius},
    };
    Vector2 size = {5,5}; 
    float rad = 2.0944;
    ship.right= ship.up;
    apply2dRotation(&ship,&ship.right,&rad);
    
    float rad2 = 4.1887;
    ship.left= ship.up;
    apply2dRotation(&ship,&ship.left,&rad2);
    


    InitWindow(screenWidth, screenHeight, "Asteroids");

    SetTargetFPS(60);               
    int key = KEY_W;
    while (!WindowShouldClose())    
    {
        if(IsKeyDown(key))
        {
            switch(key)
            {
                case KEY_W:
                    {
                        ship.acceleration -= 0.01; 
                    }break;
                case KEY_S:
                    {
                        ship.acceleration += 0.01; 
                    }break;
                case KEY_A:
                    {
                        ship.angle -= 0.005; 
                    }break;
                case KEY_D:
                    {
                        ship.angle += 0.005; 
                    }break;
            } 
        }
        else
        {
            switch(key)
            {
                case KEY_W:
                    {
                        ship.acceleration = 0; 
                    }break;
                case KEY_S:
                    {
                        ship.acceleration = 0; 
                    }break;
                case KEY_A:
                    {
                        ship.angle = 0; 
                    }break;
                case KEY_D:
                    {
                        ship.angle = 0; 
                    }break;
            } 
            key = GetKeyPressed();
        }
        
        ship.velocity.x += ship.acceleration;
        ship.velocity.y += ship.acceleration;

        ship.pos.x += ship.velocity.x;
        ship.pos.y += ship.velocity.y;
        
        if(ship.angle > 0)
        {
            ship.up = ship.pos;
            apply2dRotation(&ship, &ship.up, &ship.angle);
        }

        ship.right= ship.up;
        float ang = rad + ship.angle;
        apply2dRotation(&ship,&ship.right,&ang);

        ship.left= ship.up;
        float ang2 = rad2 + ship.angle;
        apply2dRotation(&ship,&ship.left,&ang2);

        if(ship.angle < 0 || ship.angle > 0)
        {
            apply2dRotation(&ship,&ship.up,&ship.angle);
            apply2dRotation(&ship,&ship.left,&ship.angle);
            apply2dRotation(&ship,&ship.right,&ship.angle);

        }
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTriangle(ship.up,ship.left,ship.right,WHITE);
        //DrawPixelV(ship.pos,);
        DrawRectangleV(ship.left,size,GREEN);
        DrawRectangleV(ship.up,size,RED);
        DrawRectangleV(ship.right,size,BLUE);
        //
        //DrawCircleLinesV(ship.pos, radius, RED);
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
        newAngle = 2 * PI + newAngle;
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
