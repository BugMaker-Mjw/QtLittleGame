#include "minelabel.h"
#include"mainwindow.h"
#include<QMouseEvent>
int MineLabel::canClick=true;
QList<QSize> MineLabel::list;
bool MineLabel::isFirst=true;
int MineLabel::gameMines=10;
QPoint MineLabel::firstPoint;
bool MineLabel::king=false;
MineLabel::MineLabel(int x,int y,QWidget *parent) : QLabel(parent)
{
    this->x=x;
    this->y=y;
    this->setPixmap(MainWindow::getImage(QString(":/img/blank.gif")));
    this->resize(30,30);
    this->type=0;
    this->visited=false;
    this->isFlag=0;
}
void MineLabel::mousePressEvent(QMouseEvent *e){
    if(canClick&&this->visited==false){ //可以点击并且没有被访问过
        if(e->button()==Qt::LeftButton){
            if(this->type==1&&!this->isFlag){//点到了雷 并且还没有被标记
                if(isFirst){
                    firstPoint=QPoint(this->x,this->y);
                    emit first();
                }
                else{
                    canClick=false;
                    boom();
                    emit fail();
                }
            }
            else{
                if(isFirst){
                    isFirst=false;
                    emit begin();
                }
                if(!this->isFlag)
                    setBlank(this);
                if(isWin()){
                    canClick=false;
                    emit win();
                }
            }
        }
        else{
            if(this->isFlag==1)
                gameMines++;
            this->isFlag=(this->isFlag+1)%3;
            QString str[]={"blank.gif","flag.gif","ask.gif"};
            this->setPixmap(MainWindow::getImage(QString(":/img/")+str[this->isFlag]));
            if(this->isFlag==1)
                gameMines--;
            emit numberChange();
        }
    }
}
void MineLabel::enterEvent(QEvent *e){
    Q_UNUSED(e);
    if(!this->visited&&this->isFlag==0&&canClick){
        this->setPixmap(MainWindow::getImage(QString(":/img/0.gif")));
    }
    if(king){
        if(this->type==1)
            MainWindow::mineKing->setStyleSheet("background:red");
        else
            MainWindow::mineKing->setStyleSheet("background:white");
    }
}
void MineLabel::leaveEvent(QEvent *e){
    Q_UNUSED(e);
    if(!this->visited&&this->isFlag==0&&canClick)
        this->setPixmap(MainWindow::getImage(QString(":/img/blank.gif")));
    if(king)
        MainWindow::mineKing->setStyleSheet("background:white");
}
bool MineLabel::isWin(){
    int count=0;
    for(int i=1;i<GameWidget::mines.size()-1;i++){
        for(int j=1;j<GameWidget::mines[i].size()-1;j++){
            if(GameWidget::mines[i][j]->visited)
                count++;
        }
    }
    if(GameWidget::row*GameWidget::column-count==GameWidget::totalMines)
        return true;
    return false;
}
int MineLabel::searchRound(int x,int y){
    int count=0;
    if(GameWidget::mines[x-1][y]->type)
        count++;
    if(GameWidget::mines[x+1][y]->type)
        count++;
    for(int i=x-1,j=y-1;i<x+2;i++)
        if(GameWidget::mines[i][j]->type)
            count++;
    for(int i=x-1,j=y+1;i<x+2;i++)
        if(GameWidget::mines[i][j]->type)
            count++;
    return count;
}
void MineLabel::setBlank(MineLabel* current){
    int count=searchRound(current->x,current->y);
    if(current->isFlag==0){
        current->visited=true;
        QString temp = QString(":/img/%1.gif").arg(count);
        current->setPixmap(MainWindow::getImage(QString(temp)));
    }
    if(count==0){
        if(current->x>1&&list.indexOf(QSize(current->x-1,current->y))==-1){//左
            list.append(QSize(current->x-1,current->y));
            setBlank(GameWidget::mines[current->x-1][current->y]);
        }
        if(current->x<GameWidget::row&&list.indexOf(QSize(current->x+1,current->y))==-1){//右
            list.append(QSize(current->x+1,current->y));
            setBlank(GameWidget::mines[current->x+1][current->y]);
        }
        if(current->y>1&&list.indexOf(QSize(current->x,current->y-1))==-1){//上
            list.append(QSize(current->x,current->y-1));
            setBlank(GameWidget::mines[current->x][current->y-1]);
        }
        if(current->y<GameWidget::column&&list.indexOf(QSize(current->x,current->y+1))==-1){//下
            list.append(QSize(current->x,current->y+1));
            setBlank(GameWidget::mines[current->x][current->y+1]);
        }
        if(current->x>1&&current->y>1&&list.indexOf(QSize(current->x-1,current->y-1))==-1){//左上
            list.append(QSize(current->x-1,current->y-1));
            setBlank(GameWidget::mines[current->x-1][current->y-1]);
        }
        if(current->x>1&&current->y<GameWidget::column&&list.indexOf(QSize(current->x-1,current->y+1))==-1){//左下
            list.append(QSize(current->x-1,current->y+1));
            setBlank(GameWidget::mines[current->x-1][current->y+1]);
        }
        if(current->x<GameWidget::row&&current->y>1&&list.indexOf(QSize(current->x+1,current->y-1))==-1){//右上
            list.append(QSize(current->x+1,current->y-1));
            setBlank(GameWidget::mines[current->x+1][current->y-1]);
        }
        if(current->x<GameWidget::row&&current->y<GameWidget::column&&list.indexOf(QSize(current->x+1,current->y+1))==-1){//右下
            list.append(QSize(current->x+1,current->y+1));
            setBlank(GameWidget::mines[current->x+1][current->y+1]);
        }
    }
}
void MineLabel::boom(){
    for(int i=1;i<GameWidget::mines.size()-1;i++){
        for(int j=1;j<GameWidget::mines[i].size()-1;j++){
               if(GameWidget::mines[i][j]->type!=1&&GameWidget::mines[i][j]->isFlag==1)
                   GameWidget::mines[i][j]->setPixmap(MainWindow::getImage(":/img/error.gif"));
               else if(GameWidget::mines[i][j]->type==1&&GameWidget::mines[i][j]->isFlag==1)
                   continue;
               else if(GameWidget::mines[i][j]->type==1)
                   GameWidget::mines[i][j]->setPixmap(MainWindow::getImage(":/img/mine.gif"));
        }
    }
    this->setPixmap(MainWindow::getImage(":/img/blood.gif"));
}
