#include "mainwindow.h"
#include<QMenuBar>
#include<QKeyEvent>
#include<QMessageBox>
#include<QApplication>
#include<QDesktopWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    controlWidget = new ControlWidget(this);
    QMenuBar *bar = menuBar();
    QMenu *game=bar->addMenu("游戏(&G)");
    QMenu *about=bar->addMenu("关于(&A)");
    map.insert(game->addAction("初级(&N)"),QSize(9,9));
    map.insert(game->addAction("中级(&M)"),QSize(16,16));
    map.insert(game->addAction("高级(&H)"),QSize(30,16));
    QAction * play = about->addAction("玩法简介(&p)");
    connect(play,&QAction::triggered,[=](){
        QMessageBox::about(this,"玩法说明","点出的数字是几，"
                                       "代表以当前数字为中心的九宫格内有几个地雷，"
                                       "这时候就需要通过其它地方的数字来判断,通过不断判断排除地雷"
                                       "获取胜利");
    });
    QAction * write = about->addAction("关于作者(&w)");
    connect(write,&QAction::triggered,[=](){
        this->king+=2;
        if(king>=8){
            mineKing->show();
            MineLabel::king=true;
        }
        QMessageBox::about(this,"感谢你的支持","by:BugMaker");
    });
    this->setMenuBar(bar);
    gameWidget = new GameWidget(this);
    QMapIterator<QAction*,QSize> it(map);
    mineKing = new QWidget(this);
    mineKing->hide();
    mineKing->move(10,30);
    mineKing->resize(3,3);
    mineKing->setStyleSheet("background:black");
    for(int i=0;i<map.size();i++){
        auto v = it.next();
        connect(v.key(),&QAction::triggered,[=](){
            gameWidget->row=v.value().width();
            gameWidget->column=v.value().height();
            switch (v.value().width()) {
            case 9:gameWidget->totalMines=10;break;
            case 16:gameWidget->totalMines=40;break;
            case 30:gameWidget->totalMines=99;break;
            }
            allWidgetUpdate();
        });
    }
    allWidgetUpdate();
    this->setWindowIcon(QIcon(":/img/mine.ico"));
    this->setWindowTitle("MineSweeper");
}
void MainWindow::keyPressEvent(QKeyEvent * event){
    if(event->key()==Qt::Key_M){
        if(king==0)
            king++;
    }
    else if(event->key()==Qt::Key_I){
        if(king==1||king==5)
            king++;
    }
    else if(event->key()==Qt::Key_N){
        if(king==2||king==6)
            king++;
    }
    else if(event->key()==Qt::Key_E){
        if(king==3)
            king++;
    }
    else if(event->key()==Qt::Key_K){
        if(king==4)
            king++;
    }
    else if(event->key()==Qt::Key_G){
        if(king==7)
            king++;
    }
    else{
        king=0;
    }
    if(king>=8){
        mineKing->show();
        MineLabel::king=true;
    }
}
MainWindow::~MainWindow()
{
}
void MainWindow::allWidgetUpdate(){
    gameWidget->gameUpdate();
    this->resize(gameWidget->getSize());
    controlWidget->init();
    this->setFixedSize(gameWidget->getSize());
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move(( desktop->width()- this->width())/2, (desktop->height() - this->height())/2);
    connect(controlWidget->game,&QPushButton::clicked,[=](){
        if(controlWidget->timer)
            controlWidget->timer->stop();
        gameWidget->gameUpdate();
        controlWidget->init();
    });
    connect(gameWidget,&GameWidget::reBind,[=](){
        controlWidget->init();
    });
    connect(gameWidget,&GameWidget::begin,[=](){
        controlWidget->time = controlWidget->time.currentTime();
        if(controlWidget->timer)
            delete controlWidget->timer;
        controlWidget->timer = new QTimer(this);
        controlWidget->timer->start(1000);
        connect(controlWidget->timer,&QTimer::timeout,[=](){
            controlWidget->ledChange(++controlWidget->gameTime,controlWidget->led2);
        });
    });
}
QPixmap MainWindow::getImage(QString src,int width,int height){
    QImage image;
    image.load(src);
    QPixmap pixmap = QPixmap::fromImage(image);
    QPixmap fitpixmap = pixmap.scaled(width,height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
    return fitpixmap;
}
QWidget* MainWindow::mineKing=nullptr;
int MainWindow::king=0;
