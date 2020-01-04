#include "gamewidget.h"
#include<QPainter>
#include<QPen>
#include<QKeyEvent>
#include<QTimer>
Control  GameWidget::con;
Control  GameWidget::anotherCon;
QTimer* GameWidget::timer;
GameWidget::GameWidget(QWidget *parent) : QWidget(parent)
{
    this->resize(350,700);//设置推荐尺寸  因为使用了viewport 不用过于担心窗口问题
    for(int i=0;i<10;i++){  //注意 这里的访问 严格按照x-y坐标系访问
        Control::map.push_back(QVector<int>(20,0));
    }
    timer = new QTimer(this);
    timer->start(500);
    connect(timer,&QTimer::timeout,[=](){
        con.move(2);
        update();
    });
    con.rePaint();
    update();
}
void GameWidget::paintEvent (QPaintEvent *)
{
    QPainter p(this);
    p.setViewport(this->rect());
    p.setWindow(0,0,100,200);
    QPen pen;;
    for(int i=0;i<Control::map.size();i++){ //根据1的标志 来绘画砖块
        for(int j=0;j<Control::map[i].size();j++){
            if(Control::map[i][j]){
                p.fillRect(i*10,j*10,9,9,QColor("red"));
            }
        }
    }
    pen.setWidth(0);
    pen.setColor("white");
    p.setPen(pen);
    //这里一定要先填充砖块 再划线 不然砖块画出来会非常难看
    //画线
    for(int i=0;i<=20;i++){
        p.drawLine(0,i*10,100,i*10);
    }
    for(int i=0;i<=10;i++){
        p.drawLine(i*10,0,i*10,200);
    }
}
void GameWidget::keyPressEvent(QKeyEvent *e){
    if(e->key()==Qt::Key_Up){
        con.move(1);
    }
    else if(e->key()==Qt::Key_Down){
        con.move(2);
    }
    else if(e->key()==Qt::Key_Left){
        con.move(3);
    }
    else if(e->key()==Qt::Key_Right){
        con.move(4);
    }
    update();
}
