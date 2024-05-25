#pragma once
#include "raylib.h"
#include "iostream"
#include <deque>
#include "raymath.h"
#include "../constants/constants.h"

using namespace std;

class Food{
    public:
        Vector2 position;
        Color color=DARKGREEN;
        Texture2D texture;

        Food()
        {
            Image image=LoadImage("./assets/apple.png");
            std::cout<<GetWorkingDirectory()<<std::endl;
            ImageResize(&image,cellSize,cellSize);
            texture=LoadTextureFromImage(image);
            position=GenerateRandomPosition();
            UnloadImage(image);
        }

        ~Food()
        {
            UnloadTexture(texture);
        }

        void draw(){
            DrawTexture(texture,padding+position.x*cellSize,padding+position.y*cellSize,WHITE);
        }

        void respawn(deque<Vector2> snakeBody)
        {
            position=GenerateValidPosition( snakeBody );
        }

    protected:
        Vector2 GenerateRandomPosition()
        {
            float x=GetRandomValue(0,cellCount-1);
            float y=GetRandomValue(0,cellCount-1);
            
            return {x,y};
        }
    
    
        Vector2 GenerateValidPosition(deque<Vector2> snakeBody)
        {
            Vector2 pos;
            pos=GenerateRandomPosition();
            
            long long unsigned int i;
            for(i=0;i<snakeBody.size();i++)
            {
                if(Vector2Equals(snakeBody[i],pos))
                {
                    pos=GenerateValidPosition(snakeBody);
                }
            }
            return pos;
        }
};