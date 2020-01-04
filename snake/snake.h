#ifndef SNAKE_H
#define SNAKE_H
#include<QKeyEvent>
#include<QLabel>
class snake
{
public:
    snake(int x,int y);
    int x,y,flag;
    int tailx,taily;
    snake *next;
    void Up();
    void Down();
    void Left();
    void Right();
    bool EatItself();
    void Addsnake();
    bool judge(int x,int y);
    void Update();
};

#endif // SNAKE_H
