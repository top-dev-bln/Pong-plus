#include <cmath>
#include <raylib.h>

using namespace std;


const int screenWidth = 1280;
const int screenHeight = 800;
const int segmentHeight = 30;
const int gapHeight = 20;

class Ball {
        public:
        float x,y;
        int speed_x,speed_y;
        int radius;

       void DrawBall() {
            DrawCircle(x, y, radius, WHITE);
        }

        void updateBall() {
            x+=speed_x;
            y+=speed_y;

            if (y + radius >= screenHeight || y - radius <= 0) {
                speed_y = -speed_y;
            }

            if (x + radius >= screenWidth || x - radius <= 0) {
                speed_x = -speed_x;
            }

            

            

            if (IsKeyDown(KEY_SPACE)) {
                speed_y = -speed_y;
            }

        }
};

class Paddle{
protected:
void limit(){
    if(y<0){
        y=0;
    }
    if(y>screenHeight-height){
        y=screenHeight-height;
}
}
public:
float x,y;
float width,height;
int speed;

void DrawPaddle() {
    DrawRectangle(x, y, width, height, WHITE);}

void updatePaddle() {
    if (IsKeyDown(KEY_W) && y > 0) {
        y -= speed;
    }
    if (IsKeyDown(KEY_S) && y < screenHeight - height) {
        y += speed;
    }
    limit();



}
};


class CPU:public Paddle{
public:

void updatePaddle(int ball_y) {
    if (y + height/2 > ball_y) {
        y -= speed;
    }
     if (y + height/2 < ball_y) {
        y += speed; 
    }
    limit();
  

}

};


class PacMan:public Paddle{
public:
void updatePaddle(int ball_y) {
    if (y + height/2 > ball_y) {
        y -= speed;
    }
     if (y + height/2 < ball_y) {
        y += speed; 
    }
    limit();
}

};


Ball ball ;
Paddle vacabon;
CPU ex_machina;

int main () {



    ball.radius=20;
    ball.x=screenWidth/2;
    ball.y=screenHeight/2;
    ball.speed_x=7;
    ball.speed_y=7;

    vacabon.width=25;
    vacabon.height=125;
    vacabon.x=20;   
    vacabon.y=screenHeight/2 - vacabon.height/2;
    vacabon.speed=10;

    ex_machina.width=25;
    ex_machina.height=125;
    ex_machina.x=screenWidth - ex_machina.width - 20;
    ex_machina.y=screenHeight/2 - ex_machina.height/2;
    ex_machina.speed=10;



    InitWindow(screenWidth, screenHeight, "Pong Plus");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();

        //update
        ball.updateBall();
        vacabon.updatePaddle();
        ex_machina.updatePaddle(ball.y);

        //colision
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{vacabon.x,vacabon.y,vacabon.width,vacabon.height})){
            ball.speed_x=-ball.speed_x;
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{ex_machina.x,ex_machina.y,ex_machina.width,ex_machina.height})){
            ball.speed_x=-ball.speed_x;
        }


        //draw
        ClearBackground(BLACK);
        for (int y = 0; y < screenHeight; y += segmentHeight + gapHeight) {
             DrawLineEx(Vector2{screenWidth / 2, (float)y}, Vector2{screenWidth / 2, (float)(y + segmentHeight)}, 5, WHITE);
        }

        ball.DrawBall();
        vacabon.DrawPaddle();
        ex_machina.DrawPaddle();
       

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
