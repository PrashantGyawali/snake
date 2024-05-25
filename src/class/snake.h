#include <deque>
#include "raylib.h"
#include "../constants/constants.h"
#include "raymath.h"
using namespace std;

class Snake{
    public:
        deque<Vector2> body ={Vector2{14,11},Vector2{14,12},Vector2{14,13}};
        Vector2 direction={0,-1};

        void addSegment()
        {
            body.push_back(body[body.size()-1]);
        }

        void reset()
        {
            body={Vector2{12,5},Vector2{12,6},Vector2{12,7}};
            float xDirection=GetRandomValue(-1,1)*1.0;
            float yDirection=xDirection==0?-1:0*1.0;
            direction={xDirection,yDirection};
        }

        void draw(){
            long long unsigned int i;
            for(i=0 ; i<body.size();i++){
                float x=body[i].x * cellSize;
                float y=body[i].y * cellSize;
                Rectangle segment=Rectangle{x+padding,y+padding,(float)cellSize,(float)cellSize};
                DrawRectangleRounded(segment,0.5,6,DARKGREEN);
            }
        }

        void update()
        {
            if(eventTriggered(0.2))
            {
                body.pop_back();
                body.push_front(Vector2Add(body[0],direction));
            }
            if(IsKeyPressed(KEY_UP) && direction.y!=1)
            {
                direction={0,-1};
            }
            if(IsKeyPressed(KEY_DOWN)&& direction.y!=-1)
            {
                direction={0,1};
            }
            if(IsKeyPressed(KEY_LEFT) && direction.x!=1)
            {
                direction={-1,0};
            }
            if(IsKeyPressed(KEY_RIGHT) && direction.x!=-1)
            {
                direction={1,0};
            } 
        }

    bool checkCollisionWithItself()
    {
        deque<Vector2> headlessBody=body;
        headlessBody.pop_front();
        long long unsigned int i;

        for(i=0;i<headlessBody.size();i++)
        {
            if(Vector2Equals(body[0],headlessBody[i]))
            {
                return true;
            }
        }
            return false;
    }
    
protected:
    double lastUpdateTime=0;

    bool eventTriggered(double interval)
    {
        double currentTime=GetTime();
        if(currentTime-lastUpdateTime>=interval)
        {
            lastUpdateTime=currentTime;
            return true;
        }
        return false;
    }


};