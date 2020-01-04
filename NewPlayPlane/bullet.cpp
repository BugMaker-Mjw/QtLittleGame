#include "bullet.h"
Bullet::Bullet(int x,int y,QWidget *parent) : QLabel(parent)
{
    resize(13,13);
    this->setPixmap(QPixmap(":/img/bullet1.png").scaled(13,13));
    this->bulletx=x+28;
    this->bullety=y-18;
    this->move(bulletx,bullety);
    this->show();
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[=](){
        static int id=0;
        this->id=id++;
        this->move(bulletx,bullety-=4);
        if(bullety<0){
             timer->stop();
             this->hide();
             for(int i=0;i<list->length();i++){
                 if(list->at(i)==this){
                     delete this;
                     list->removeAt(i);
                 }
             }
        }
    });
    timer->start(10);
}
void Bullet::setlist(QList<Bullet*> *list){
    this->list=list;
}
