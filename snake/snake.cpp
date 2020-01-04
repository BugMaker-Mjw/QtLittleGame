#include "snake.h"
#include<QDebug>
snake::snake(int x,int y)
{
    this->x=x;
    this->y=y;
    tailx=x;
    taily=y;
    flag=4;
    next=nullptr;
}
void snake::Up()
{
    //有的毛病是什么 所谓的走 就是让头的坐标加呗
   /* if(this->judge(this->x,this->y-1))
        return;*/
    if(flag==2)
        return;
    Update();
    this->y--;
    if(this->y<0)
        this->y+=20;
    flag=1;
}
void snake::Down()
{
    /*if(this->judge(this->x,this->y+1))
        return;*/
    if(flag==1)
        return;
    Update();
    this->y++;
    if(this->y>=20)
        this->y-=20;
    flag=2;
}
void snake::Left()
{
    /*if(this->judge(this->x-1,this->y))
        return;*/
    if(flag==4)
        return;
    Update();
    this->x--;
    if(this->x<0)
        this->x+=20;
    flag=3;
}
void snake::Right()
{
    /*if(this->judge(this->x+1,this->y))
        return;*/
    if(flag==3)
        return;
    Update();
    this->x++;
    if(this->x>=20)
        this->x-=20;
    flag=4;
}
/*bool snake::judge(int x,int y)
{
    snake *temp = this;
    if(x<0) x+=20;
    if(x>=20) x-=20;
    if(y<0) y+=20;
    if(y>=20) y-=20;
    while(temp!=NULL){
        if(x==temp->x && y==temp->y)
            return true;
        temp=temp->next;
    }
    return false;
}*/
void snake::Update()
{
    snake *temp1=this;
    while(temp1->next!=NULL)
        temp1=temp1->next;
    this->tailx=temp1->x;
    this->taily=temp1->y;
    temp1=this->next;
    int tempx,tempy;
    while(temp1!=NULL){
        if(temp1==this->next){
            tempx=temp1->x;
            tempy=temp1->y;
            temp1->x=this->x;
            temp1->y=this->y;
        }
        else{
            int k,b;
            k=tempx,b=tempy;
            tempx=temp1->x;
            tempy=temp1->y;
            temp1->x=k;
            temp1->y=b;
        }
        temp1=temp1->next;
    }
    //继续走 现在的任务就是每个下一个节点 接上上一个节点

}
bool snake::EatItself()
{
    snake *temp=this->next;
    while(temp!=NULL)
    {
        if(this->x==temp->x && this->y==temp->y)
            return true;
        temp=temp->next;
    }
    return false;
}
void snake::Addsnake(){
    snake *temp=this;
    while(temp->next!=NULL)
        temp=temp->next;
    temp->next=new snake(this->tailx,this->taily);
}
