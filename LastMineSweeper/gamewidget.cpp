#include "gamewidget.h"
#include<QTime>
#include "mainwindow.h"
#include <QRandomGenerator>
int GameWidget::row=9;
int GameWidget::column=9;
int GameWidget::totalMines=10;
QVector<QVector<MineLabel*>> GameWidget::mines;
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    gameUpdate();
}
QSize GameWidget::getSize(){
    return QSize(this->width(),this->height()+70);
}
void GameWidget::gameUpdate(){
    for(int i=0;i<mines.size();i++){
        for(int j=0;j<mines[i].size();j++)
            delete mines[i][j];
        mines[i].clear();
    }
    mines.clear();
    MineLabel::gameMines=this->totalMines;
    MineLabel::canClick=true;
    MineLabel::isFirst=true;
    MineLabel::list.clear();
    for(int i=0;i<this->row+2;i++){
        QVector<MineLabel*> temp;
        for(int j=0;j<this->column+2;j++){
            temp.append(new MineLabel(i,j,this));
            if(i==0||i==this->row+1||j==0||j==this->column+1){
                temp.last()->hide();
            }
            else {
                temp.last()->move((i-1)*30,(j-1)*30);
                temp.last()->show();
                connect(temp.last(),&MineLabel::first,[=](){
                    while(mines[MineLabel::firstPoint.x()][MineLabel::firstPoint.y()]->type==1){
                        this->gameUpdate();
                        emit reBind();
                    }
                    mines[MineLabel::firstPoint.x()][MineLabel::firstPoint.y()]->setBlank(mines[MineLabel::firstPoint.x()][MineLabel::firstPoint.y()]);
                    mines[MineLabel::firstPoint.x()][MineLabel::firstPoint.y()]->isFirst=false;
                    emit begin();
                });
            }
        }
        mines.append(temp);
    }
    this->move(0,70);
    this->resize(row*30,column*30);
    createMines();
}
void GameWidget::createMines(){
    int count=0;
    while(count++<this->totalMines){
        int x=QRandomGenerator::global()->bounded(1,mines.size()-1);  //这个是 [0,size)+1  [1,size+1)
        int y=QRandomGenerator::global()->bounded(1,mines[0].size()-1); //这是生成0-9 1-10
        while(mines[x][y]->type==1){
            x=QRandomGenerator::global()->bounded(1,mines.size()-1);  //[1,size()-1]
            y=QRandomGenerator::global()->bounded(1,mines[0].size()-1);
        }
        mines[x][y]->type=1;
        //mines[x][y]->setPixmap(MainWindow::getImage(QString(":/img/mine.gif")));
    }
}
