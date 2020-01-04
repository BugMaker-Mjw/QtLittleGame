#include "myplane.h"
#include<QMovie>
#include<QLabel>
#include<QTimer>
#include"bullet.h"
#include<QList>
#include<QDebug>
MyPlane::MyPlane(QWidget *parent) : QLabel(parent)
{
    list=new QList<Bullet*>;
    QMovie *movie = new QMovie(":/img/myplane.gif");
    this->setMovie(movie);
    movie->start();
  //  this->setPixmap(QPixmap(":/img/myplane.gif"));
    resize(66,80);
    this->parent=parent;
}
void MyPlane::init(int x,int y){
    nowx=x*0.5-30;
    nowy=y*0.8;
    this->move(nowx,nowy);
    fatherx=x,fathery=y;
    //emit where(this->nowx,this->nowy);
    //这里就要开启定时器 发起子弹
    bullet = new QTimer(this);
    connect(bullet,&QTimer::timeout,[=](){
         Bullet* temp=new Bullet(nowx,nowy,parent);
         temp->setlist(list);
         list->push_back(temp);
    });
    bullet->start(100);
}
void MyPlane::Goto(int flag){
    if(flag==1){
        if(nowx>0)
            this->move(nowx-=20,nowy);
     }
    else if(flag==2){
        if(nowx<(fatherx-70))
            this->move(nowx+=20,nowy);
    }
    else if(flag==3){
        if(nowy>5)
            this->move(nowx,nowy-=20);
    }
    else{
        if(nowy<(fathery-80))
            this->move(nowx,nowy+=20);
    }
    emit move(nowx,nowy);
}
void MyPlane::gameover(){
    QMovie *movie = new QMovie(":/img/myboom.gif");
    this->setMovie(movie);
    movie->start();
    this->bullet->stop();
    for(int i=0;i<list->length();i++)
        list->removeLast();
}
