#ifndef FOOD_H
#define FOOD_H
#include"snake.h"
class Food
{
public:
    Food(int x=8,int y=12);
    int x,y;
    snake *realsnake;
    void NewFood();
    void setsnake(snake *temp);
};

#endif // FOOD_H
