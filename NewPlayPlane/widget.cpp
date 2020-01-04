#include "widget.h"
#include "gamewidget.h"
#include<QPushButton>
#include<QPainter>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *button=new QPushButton(this);
    button->setText("开始游戏");
    button->setStyleSheet("background:#C3C8C9;color:gray");
    resize(500,700);
    button->move(width()*0.40,height()*0.7);
    connect(button,&QPushButton::clicked,[=](){
        sonwidget=new GameWidget();
        sonwidget->resize(500,700);
        sonwidget->init();
        sonwidget->setstart(this);
        sonwidget->show();
        this->hide();
    });

}
void Widget::paintEvent(QPaintEvent *ev){
    QPainter paint(this);
    //paint.drawPixmap(0,0,500,700,QPixmap(":/img/bk1.png"));
    paint.drawPixmap(rect(),QPixmap(":/img/start.png"));
}
Widget::~Widget()
{

}
