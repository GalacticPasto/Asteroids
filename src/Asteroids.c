#include <stdio.h>
#include <raylib.h>
#include <raymath.h>

#define DEBUG 
#undef DEBUG
#define SCREENWIDTH  1280
#define SCREENHEIGHT 720 

#define RADIUS 20 

#define CENTERX SCREENWIDTH/2
#define CENTERY SCREENHEIGHT/2

#define ASTEROIDCOUNT 10

struct asteroid 
{
    float angle;
    float radius;
    Vector2 velocity;
    Vector2 pos;
};


struct ship 
{
    float angle;
    float acceleration;
    Vector2 velocity;
    Vector2 pos;
};

void printVector(Vector2* vec);
void apply2dRotation(Vector2* shipPos,Vector2* vec,float angle);

int main(void)
{

    InitWindow(SCREENWIDTH, SCREENHEIGHT, "Asteroids");

    struct asteroid asteroids[ASTEROIDCOUNT] = {};

    for(int i = 0 ; i < ASTEROIDCOUNT; i++)
    {
        asteroids[i].angle = GetRandomValue(0, 360);
        asteroids[i].radius = GetRandomValue(10,30);
        asteroids[i].velocity.x = cos(asteroids[i].angle * DEG2RAD) * 2; 
        asteroids[i].velocity.y = sin(asteroids[i].angle * DEG2RAD) * 2; 
    }


    struct ship ship= 
    {
        .pos = {(float)CENTERX,(float)CENTERY},
    };

    Vector2 size = {5,5}; 
    SetTargetFPS(60);               

    while (!WindowShouldClose())    
    {

        //ship angle 
        if(IsKeyDown(KEY_D))
        {
            ship.angle += 5;
        } 
        if(IsKeyDown(KEY_A))
        {
            ship.angle -= 5;
        } 

        // acceleration  

        if(IsKeyDown(KEY_W))
        {
            if(ship.acceleration < 1) ship.acceleration += 0.05;
        }
        else
        {
            if(ship.acceleration > 0) ship.acceleration -= 0.005;
            else if(ship.acceleration < 0) ship.acceleration = 0;
        }

        if(IsKeyDown(KEY_S))
        {
            if(ship.acceleration > 0)ship.acceleration -= 0.005;
            else if(ship.acceleration < 0)ship.acceleration = 0;
        }

        //velocity
        ship.velocity.x = cos(ship.angle * DEG2RAD) * 6;
        ship.velocity.y = sin(ship.angle * DEG2RAD) * 6;

        //pos
        ship.pos.x += (ship.velocity.x * ship.acceleration);
        ship.pos.y += (ship.velocity.y * ship.acceleration);

        if(ship.pos.x > SCREENWIDTH)
        {
            ship.pos.x -= SCREENWIDTH;
        }
        else if(ship.pos.x < 0)
        {
            ship.pos.x += SCREENWIDTH - RADIUS;
        }
        if(ship.pos.y > SCREENHEIGHT)
        {
            ship.pos.y -= SCREENHEIGHT;
        } else if(ship.pos.y < 0) 
        { 
            ship.pos.y += SCREENHEIGHT - RADIUS;
        }

        Vector2 shipHead = Vector2Normalize(ship.velocity);
        shipHead = Vector2Scale(shipHead,RADIUS);
        shipHead = Vector2Add(ship.pos,shipHead);

        Vector2 shipLeft = shipHead; 
        apply2dRotation(&ship.pos, &shipLeft, 240); 

        Vector2 shipRight = shipHead; 
        apply2dRotation(&ship.pos, &shipRight, 120); 

        for(int i = 0 ; i < ASTEROIDCOUNT; i++)
        {
            asteroids[i].pos.x += asteroids[i].velocity.x;
            asteroids[i].pos.y += asteroids[i].velocity.y;

            if(asteroids[i].pos.x > SCREENWIDTH)
            {
                asteroids[i].pos.x -= SCREENWIDTH;
            }
            else if(asteroids[i].pos.x < 0)
            {
                asteroids[i].pos.x += SCREENWIDTH - asteroids[i].radius;
            }
            if(asteroids[i].pos.y > SCREENHEIGHT)
            {
                asteroids[i].pos.y -= SCREENHEIGHT;
            }
            else if(asteroids[i].pos.y < 0)
            {
                asteroids[i].pos.y += SCREENHEIGHT - asteroids[i].radius;
            }

        }


        BeginDrawing();
        ClearBackground(BLACK);

        //DrawAsteroids 
        for(int i = 0 ; i < ASTEROIDCOUNT ; i++)
        {
            DrawCircleV(asteroids[i].pos,asteroids[i].radius,GRAY);
        }

        //DrawShip
        DrawLineV(shipHead,shipLeft,WHITE);
        DrawLineV(shipHead,shipRight,WHITE);
        DrawLineV(shipRight,ship.pos,WHITE);
        DrawLineV(shipLeft,ship.pos,WHITE);
        // 




#ifdef DEBUG  
        char posx[16];
        sprintf(posx,"%f",ship.pos.x);


        char posy[16];
        sprintf(posy,"%f",ship.pos.y);

        DrawText(posx,0,0,10,GREEN);
        DrawText(posy,10,10,10,GREEN);

        DrawRectangleV(ship.pos,size,GREEN);
        DrawRectangleV(shipHead,size,RED);
        DrawRectangleV(shipLeft,size,BLUE);
        DrawRectangleV(shipRight,size,WHITE);


        //DrawLineV(ship.pos,shipHead,RED);
        //
        //DrawRectangleV(v1,size,GREEN);
        //DrawRectangleV(v2,size,RED);
        //DrawRectangleV(v3,size,BLUE);
        //DrawRectangleV(ship.pos,size,YELLOW);
        //DrawCircleLinesV(ship.pos, RADIUS, RED);
#endif

        EndDrawing();
    }
    CloseWindow();        
    return 0;
}

//rotaion around a arbiratary point 
void apply2dRotation(Vector2* shipPos, Vector2* vec,float angle)
{
    float newAngle = angle * DEG2RAD;

    float newX = (vec->x - shipPos->x) * cos(newAngle) - (vec->y - shipPos->y)* sin(newAngle); 
    float newY = (vec->x - shipPos->x) * sin(newAngle) + (vec->y - shipPos->y)* cos(newAngle); 

    vec->x = newX + shipPos->x;
    vec->y = newY + shipPos->y;

    return;
}

void printVector(Vector2* vec)
{
    printf("%f %f\n",vec->x , vec->y);
}
