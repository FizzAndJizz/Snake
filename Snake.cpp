#include "include/raylib.h" 
#include <iostream>
#include <cstdint>


static const int screenWidth = 400 % 2560;
static const int screenHeight = 400 % 1664;
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

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(fps);               // Set our game to run at 60 frames-per-second
    int tick = 0;
    int tickRate = 8; // more == faster

    int nLen = 1;

    Snake snakeLength[256] = {0};    

    
    Vector2 applePos = getRandomVec();
    Color appleColor= RED;


    int dir = 1;
    // 1 -> left 2 -> right 3-> down 4->up
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
        drawGrid();

        //game logic 
        {
            int key = GetKeyPressed();
            switch(key)
            {
                case KEY_W:
                    {
                        snakeLength[0].snakeVelocity = {0,-gridWidth + speed};
                    }break;
                case KEY_S:
                    {
                        snakeLength[0].snakeVelocity = {0,+gridWidth - speed};
                    }break;
                case KEY_D:
                    {
                        snakeLength[0].snakeVelocity = {+gridWidth - speed,0};
                    }break;
                case KEY_A:
                    {
                        snakeLength[0].snakeVelocity = {-gridWidth + speed,0};
                    }break;
                case KEY_ESCAPE:
                    {
                        break;
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
                    tick = 0;
                }
            }
            for(int i = 0 ; i < nLen ; i++)
            {
                //printf("%d %f %f\n",i,snakeLength[i].snakePos.x , snakeLength[i].snakePos.y);
                uint8_t r = GetRandomValue(0,255);
                uint8_t g = GetRandomValue(0,255);
                uint8_t b = GetRandomValue(0,255);
                uint8_t a = GetRandomValue(0,255);
                
                int random = 0;
                
                random = random 
 

                DrawRectangleV(snakeLength[i].snakePos,snakeLength[i].snakeSize,random);
            }
            if(snakeLength[0].snakePos.x == applePos.x && snakeLength[0].snakePos.y == applePos.y)
            {
                nLen++;
                applePos = getRandomVec();
            }
            DrawRectangleV(applePos,snakeLength[0].snakeSize,appleColor);
            tick++;
        }
        //game logic 


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}


