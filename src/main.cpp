#include <raylib.h>
#include "constants/constants.h"
#include "class/food.h"
#include "class/snake.h"


class Game{

    public:
        int score=0;
        bool passThroughWalls=false;

        Sound eatSound;
        Sound gameOverSound;


        Game(bool allowPassThrough)
        {
            InitAudioDevice();
            cout<<GetWorkingDirectory()<<endl;
            gameOverSound=LoadSound("./assets/over.wav");
            eatSound=LoadSound("./assets/eat.wav");
            passThroughWalls=allowPassThrough; 
        }
        ~Game()
        {
            UnloadSound(eatSound);
            UnloadSound(gameOverSound);
            CloseAudioDevice();
        }


        bool gameStarted=false;
        bool gameOver=false;

        Snake snake=Snake();
        Food food=Food();

        
        void draw()
        {
            snake.draw();
            food.draw();
        }

        void update()
        {
            if(!gameOver && gameStarted){
                snake.update();
                checkOutsideScreen();
                score+=checkCollisionWithFood();
                if(snake.checkCollisionWithItself())
                {
                    GameOver();
                }
            }
            else
            {
                waitInput();
            }

        }

        void Reset()
        {
            if(gameOver)
            {
                score=0;
                snake.reset();
                food.respawn(snake.body);
                
            }
        }

    private:


        int checkCollisionWithFood()
        {
            if(Vector2Equals(snake.body[0],food.position))
            {
                PlaySound(eatSound);
                snake.addSegment();
                food.respawn(snake.body);
                return 1;
            }
            return 0;
        }


        void checkOutsideScreen()
        {
            bool outside=false;
            if(snake.body[0].x<0)
            {
                outside=true;
                snake.body[0].x=cellCount-1;
            }
            if(snake.body[0].x>cellCount-1)
            {
                outside=true;
                snake.body[0].x=0;
            }
            if(snake.body[0].y<0)
            {
                outside=true;
                snake.body[0].y=cellCount-1;
            }
            if(snake.body[0].y>cellCount-1)
            {
                outside=true;
                snake.body[0].y=0;
            }
            if(outside && !passThroughWalls)
            {
                GameOver();
            }
        }



        void GameOver()
        {
            PlaySound(gameOverSound);
            gameOver=true;
            WaitTime(0.8);
            Reset();
        }






        void waitInput()
        {
            if(GetKeyPressed()!=0)
            {
                gameOver=false;
                gameStarted=true;
            }
        }
};

int main()
{   
    InitWindow(cellCount*cellSize +padding*2,cellCount*cellSize+padding*2,"Snake Game");
    SetTargetFPS(60);

    Game game=Game(false);

    while(!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BACKGROUNDCOLOR);
        DrawRectangleLinesEx(Rectangle{(float)(padding-10),(float)(padding-10),(float)cellCount*cellSize+20,(float)cellCount*cellSize+20},10,BLACK);
        DrawText("Retro Snake",padding-5,20,40,BLACK);
        DrawText(TextFormat("Score: %d",game.score),cellCount*cellSize-padding,30,30,BLACK);
        game.update();
        game.draw();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
