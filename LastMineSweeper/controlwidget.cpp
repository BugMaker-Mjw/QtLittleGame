#include "controlwidget.h"
#include "mainwindow.h"
#include<QMessageBox>
int ControlWidget::gameTime=0;
ControlWidget::ControlWidget(QWidget *parent) : QWidget(parent)
{
    timer=nullptr;
    ledLeft = new QWidget(this);
    ledRight = new QWidget(this);
    game = new QPushButton(this);
    for(int i=0;i<6;i++){
        if(i<3){
           led1.append(new QLabel(ledLeft));
        }
        else{
            led2.append(new QLabel(ledRight));
        }
    }
}
void ControlWidget::init(){
    for(int i=0;i<6;i++){
        if(i<3){
            led1[i]->setPixmap(MainWindow::getImage(":/img/d0.gif",20));
            led1[i]->resize(20,30);
            led1[i]->move(i*20,0);
        }
        else{
            led2[i-3]->setPixmap(MainWindow::getImage(":/img/d0.gif",20));
            led2[i-3]->resize(20,30);
            led2[i-3]->move((i-3)*20,0);
        }
    }
    game->resize(30,30);
    game->setStyleSheet("border-image:url(:/img/face_normal.gif)");
    this->move(0,32);
    this->resize(GameWidget::row*30,38);
    ledLeft->move(10,0);
    ledRight->move(this->width()-70,0);
    game->move(this->width()/2-15,0);
    ledChange(GameWidget::totalMines,led1);
    for(int i=0;i<GameWidget::mines.size();i++){
        for(int j=0;j<GameWidget::mines[i].size();j++){
            connect(GameWidget::mines[i][j],&MineLabel::begin,[=](){
                 time = time.currentTime();
                 if(timer)
                     delete timer;
                 timer = new QTimer(this);
                 timer->start(1000);
                 connect(timer,&QTimer::timeout,[=](){
                     ledChange(++gameTime,led2);
                 });
            });
            connect(GameWidget::mines[i][j],&MineLabel::fail,[=](){
                timer->stop();
                game->setStyleSheet("border-image:url(:/img/face_fail.gif)");
                gameTime=0;
            });
            connect(GameWidget::mines[i][j],&MineLabel::numberChange,[=](){
                 this->ledChange(MineLabel::gameMines,this->led1);
            });
            connect(GameWidget::mines[i][j],&MineLabel::win,[=](){
                timer->stop();
                gameTime=0;
                int tmMsec=time.elapsed();//计算时间差
                int ms=tmMsec%1000;//计算毫秒数
                int sec=tmMsec/1000;//计算秒数
                QString str=QString::asprintf("完成时间: %d秒.%d毫秒",sec,ms);
                game->setStyleSheet("border-image:url(:/img/face_success.gif)");
                QMessageBox::about(this,"祝贺!","你赢得了比赛胜利!\n"+str);
            });
        }
    }
}
void ControlWidget::ledChange(int number,QList<QLabel*> &list){
    if(number<0||number>999)
        return;
    for(int i=list.size()-1;i>=0;i--){
        QString temp = QString(":/img/d%1.gif").arg(number%10);
        number/=10;
        list[i]->setPixmap(MainWindow::getImage(temp,20));
    }
}
