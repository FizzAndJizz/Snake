#include "include/raylib.h" 
#include <iostream>
#include <cstdint>


static const int screenWidth = 500;
static const int screenHeight = 500;
static const int gridWidth = 20;    
static const int speed = 0;    
static const int fps= 60;    

struct Snake
{
    Vector2 snakePos = {0,0};
    Vector2 snakeVelocity = {gridWidth - speed ,0}; // initial velocity
    Color snakeColor = GREEN;
    Vector2 snakeSize = {gridWidth,gridWidth};
};

Vector2 getRandomVec()
{
    float x = GetRandomValue(0,(screenWidth/gridWidth) - 1);
    float y = GetRandomValue(0,(screenHeight/gridWidth) - 1);

    x = x * gridWidth;  
    y = y * gridWidth;  

    Vector2 randomVec = {x,y};
    return randomVec; 
}

void drawGrid()
{
    ClearBackground(BLACK);
    Vector2 startPos= {0,0};
    Vector2 endPos = {0,screenHeight};
    Color lineColor = WHITE;

    for(int i = 0 ; i < screenWidth; i+= gridWidth)
    {
        startPos = {(float)i,0};
        endPos = {(float)i,screenHeight};
        DrawLineV(startPos, endPos, lineColor);                                     
    }
    for(int i = 0 ; i < screenHeight ; i+= gridWidth)
    {
        startPos = {0,(float)i};
        endPos = {screenWidth,(float)i};
        DrawLineV(startPos, endPos, lineColor);                                     
    }
}

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Snake");

    SetTargetFPS(fps);               // Set our game to run at 60 frames-per-second

    bool paused = 0; 
    bool add = 0; 
    
    int tick = 0;
    int tickRate = 10; // more == faster
    int nLen = 1;
    int eaten = 1;

    Snake snakeLength[256] = {0};    


    Vector2 applePos = getRandomVec();
    Color appleColor= RED;


    int dir = 1;
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        drawGrid();

        //game logic 
        {
            int key = GetKeyPressed();
            if(paused == false)
            {

                switch(key)
                {
                    case KEY_W:
                        {
                            if(snakeLength[0].snakeVelocity.y == 0)
                            {
                                snakeLength[0].snakeVelocity = {0,-gridWidth + speed};
                            }
                        }break;
                    case KEY_S:
                        {
                            if(snakeLength[0].snakeVelocity.y == 0)
                            {
                                snakeLength[0].snakeVelocity = {0,+gridWidth - speed};
                            }
                        }break;
                    case KEY_D:
                        {
                            if(snakeLength[0].snakeVelocity.x == 0)
                            {
                                snakeLength[0].snakeVelocity = {+gridWidth - speed,0};
                            }
                        }break;
                    case KEY_A:
                        {
                            if(snakeLength[0].snakeVelocity.x == 0)
                            {
                                snakeLength[0].snakeVelocity = {-gridWidth + speed,0};
                            }
                        }break;
                }
                if(tick == fps/tickRate)
                { 
                    Vector2 prevPos;
                    for(int i = 0 ; i < nLen ; i++)
                    {
                        if(i == 0)
                        {

                            prevPos = snakeLength[0].snakePos;
                            snakeLength[0].snakePos.x += snakeLength[0].snakeVelocity.x;
                            snakeLength[0].snakePos.y += snakeLength[0].snakeVelocity.y;

                            if(snakeLength[0].snakePos.x >= screenWidth)
                            {
                                snakeLength[0].snakePos.x = 0;
                            }
                            else if(snakeLength[0].snakePos.x < 0)
                            {
                                snakeLength[0].snakePos.x = screenWidth - gridWidth;
                            }
                            if(snakeLength[0].snakePos.y >= screenHeight)
                            {
                                snakeLength[0].snakePos.y = 0;
                            }
                            else if(snakeLength[0].snakePos.y < 0)
                            {
                                snakeLength[0].snakePos.y = screenHeight - gridWidth;
                            }
                        }
                        else
                        {
                            std::swap(snakeLength[i].snakePos,prevPos);
                        }

                        if(add)
                        {
                            nLen++;
                            add = 0;
                        }
                        tick = 0;
                    }
                }

                for(int i = 1 ; i < nLen ; i++)
                {
                    if(snakeLength[i].snakePos.x == snakeLength[0].snakePos.x && snakeLength[i].snakePos.y == snakeLength[0].snakePos.y)
                    {
                        paused = 1;
                    }
                }

                if(snakeLength[0].snakePos.x == applePos.x && snakeLength[0].snakePos.y == applePos.y)
                {
                    add = 1;
                    eaten++;
                    applePos = getRandomVec();
                    if(tickRate != fps && eaten % 5 == 0)
                    {
                        tickRate++;
                    }
                }



                for(int i = 0 ; i < nLen ; i++)
                {
                    //printf("%d %f %f\n",i,snakeLength[i].snakePos.x , snakeLength[i].snakePos.y);
                    // uint8_t r = GetRandomValue(0,255);
                    // uint8_t g = GetRandomValue(0,255);
                    // uint8_t b = GetRandomValue(0,255);
                    // uint8_t a = GetRandomValue(0,255);
                    // 
                    // int random = 0;
                    DrawRectangleV(snakeLength[i].snakePos,snakeLength[i].snakeSize,snakeLength[i].snakeColor);
                }
                DrawRectangleV(applePos,snakeLength[0].snakeSize,appleColor);
                tick++;
            }
            else
            {
                ClearBackground(BLACK);
                DrawText("GAMEOVER", 80, 80, 40, RED);
            }
        }    


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}


