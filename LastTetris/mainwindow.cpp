#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QKeyEvent>
#include<QTimer>
int MainWindow::running=false;
int MainWindow::score=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(450,600);
    ui->next->hide();
    connect(ui->game,&GameWidget::GameOver,[=](){
       ui->pushButton->setText("重新开始");
       ui->pushButton->setDisabled(false);
       ui->label->setText(QString("最终得分为:%1").arg(score));
       score=0;
       GameWidget::gameOver=false;
       for(int i=0;i<10;i++){  //注意 这里的访问 严格按照x-y坐标系访问
           for(int j=0;j<20;j++){
           Control::map[i][j]=0;
           Control::colorMap[i][j]=0;
           }
       }
    });
    this->setWindowIcon(QIcon("://Tetris.ico"));
    this->setWindowTitle("Tetris");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::keyPressEvent(QKeyEvent *e){
    if(running){
        if(e->key()==Qt::Key_Up||e->key()==Qt::Key_W){
            ui->game->con.move(1);
        }
        else if(e->key()==Qt::Key_Down||e->key()==Qt::Key_S){
            ui->game->con.move(2);
        }
        else if(e->key()==Qt::Key_Left||e->key()==Qt::Key_A){
            ui->game->con.move(3);
        }
        else if(e->key()==Qt::Key_Right||e->key()==Qt::Key_D){
            ui->game->con.move(4);
        }
        update();
        ui->label_2->setText(QString("当前分数:%1").arg(score));
    }
    if(e->key()==Qt::Key_Space){
        if(ui->game->timer){
            if(running){
                running=false;
                ui->game->timer->stop();
                update();
            }
            else{
                running=true;
                ui->game->timer->start(1000);
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    running=true;
    ui->game->timer = new QTimer(this);
    ui->game->timer->start(1000);
    update();
    ui->game->con.newBlock();
    ui->game->anotherCon.newBlock();
    ui->game->con.rePaint();
    connect(ui->game->timer,&QTimer::timeout,[=](){
        ui->game->con.move(2);
        update();
    });
    ui->next->show();
    ui->pushButton->setDisabled(true);
    ui->label->setText("游戏进行中");
}
