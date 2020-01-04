#include "food.h"
#include<QTime>
#include<QRandomGenerator>
Food::Food(int x,int y)
{
    this->x=x;
    this->y=y;
}
void Food::setsnake(snake *temp)
{
    this->realsnake=temp;
}
void Food::NewFood()
{
    bool flag=1;
    while(flag){
        this->x=QRandomGenerator::global()->bounded(0,19);//生成一个0和19之间的整数
        this->y=QRandomGenerator::global()->bounded(0,19);//生成一个0和19之间的整数
        snake *temp=realsnake;
        while(temp!=nullptr){
            if(temp->x==this->x && temp->y ==this->y){
                flag=1;
                break;
            }
            else
                flag=0;
            temp=temp->next;
        }
    }
}
