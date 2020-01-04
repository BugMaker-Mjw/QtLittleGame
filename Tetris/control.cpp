#include "control.h"
#include<QRandomGenerator>
#include"gamewidget.h"
#include<QTimer>
QVector<QVector<QVector<QPoint>>> Control::block=
{ //方块类型现在整理好了
  {
      {{0, 0}, {1, 0}, {1, 1}, {1, 2}},  // *
      {{2, 0}, {0, 1}, {1, 1}, {2, 1}},  // *
      {{1, 0}, {1, 1}, {1, 2}, {2, 2}},  // ** L类型方块
      {{0, 1}, {1, 1}, {2, 1}, {0, 2}}
  },//这个是L
  {
      {{1, 0}, {1, 1}, {1, 2}, {1, 3}}, // *
      {{0, 1}, {1, 1}, {2, 1}, {3, 1}}, // *
      {{1, 0}, {1, 1}, {1, 2}, {1, 3}}, // *
      {{0, 1}, {1, 1}, {2, 1}, {3, 1}}  // *  直方块
  },//这个是直线
  {
      {{1, 0}, {2, 0}, {1, 1}, {1, 2}}, //  *
      {{0, 1}, {1, 1}, {2, 1}, {2, 2}}, //  *
      {{1, 0}, {1, 1}, {0, 2}, {1, 2}}, // **  反L
      {{0, 0}, {0, 1}, {1, 1}, {2, 1}}
  },//这个是反L
  {
      {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
      {{0, 0}, {0, 1}, {0, 2}, {1, 1}}, //  *
      {{0, 2}, {1, 2}, {2, 2}, {1, 1}},//  ***  就这个类似三角形的方块
      {{2, 0}, {2, 1}, {2, 2}, {1, 1}}
  },//这个是 土
  {
      {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
      {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, // **
      {{0, 0}, {1, 0}, {0, 1}, {1, 1}}, // **  正方形方块
      {{0, 0}, {1, 0}, {0, 1}, {1, 1}}
  },//这个是田
  {
      {{1, 1}, {2, 1}, {2, 0}, {1, 2}},
      {{1, 1}, {0, 1}, {1, 2}, {2, 2}},  //   *
      {{1, 1}, {2, 1}, {2, 0}, {1, 2}}, //   **
      {{1, 1}, {0, 1}, {1, 2}, {2, 2}}  //   *   旋转是Z的方块
  },//这个是Z
  {
      {{0, 0}, {0, 1}, {1, 1}, {1, 2}},//   *
      {{0, 1}, {1, 1}, {1, 0}, {2, 0}},//   **
      {{0, 0}, {0, 1}, {1, 1}, {1, 2}},//    * 旋转式反Z的方块
      {{0, 1}, {1, 1}, {1, 0}, {2, 0}}
  },//这个是反Z
};
QVector<QVector<int>> Control::map;
#include<QDebug>
Control::Control()
{
    //首先初始化地图  俄罗斯方块标准版 宽10 长20
    newBlock();
}
void Control::newBlock(){
        x=3;
        y=0;//默认都是在 这个地方进行生成砖块
        type=QRandomGenerator::global()->bounded(0,6); //Qt5新随机数方法 返回[0,6]
        process=QRandomGenerator::global()->bounded(0,3);
}
bool Control::indexCheck(int moveX,int moveY,int newProcess){
    // moveX 代表x坐标位移大小 moveY代表moveY坐标大小 newProcess代表用户想要进行砖块转换
    for(int i=0;i<4;i++){ //i<4 因为每种砖块都是由4个构成
        int tempx=this->x+block[this->type][newProcess][i].x()+moveX;
        int tempy=this->y+block[this->type][newProcess][i].y()+moveY;
        //条件说明 x超过边界 y超过边界 想要移动的地方已经具有砖块 都返回false 不允许当前移动操作
        if(tempx<0||tempx>9||tempy<0||tempy>19||map[tempx][tempy])
            return false;
    }
    return true;
}
void Control::move(int type){
    bool stopFlag=false; //标志是否停止
    gc();//移除刚才的痕迹 进行下一步绘制
    if(type==1){ //1代表想上 即方块进行变化
        int newProcess=(this->process+1)%4;
        if(indexCheck(0,0,newProcess)){
            this->process=newProcess;
        }
    }
    else if(type==2){//2代表向下移动  //这里比较特殊 这里需要判断方块是否落地
        stopFlag=indexCheck(0,1,this->process);  // 如果落地 新建状况 并且检测是否有行可以消除
        if(stopFlag){
            y++;
        }
        else{
            rePaint(); //回溯一次 下面的paint准备绘制新方块
            clearRow(); //有方块落地 检测是否可以消行
            *this=GameWidget::anotherCon; //不太记得默认拷贝好不好使了 我就自己重载了一个 可以的话 不需要这个的
        }
    }
    else if(type==3){ //3代表向左移动
        if(indexCheck(-1,0,this->process)){
            x--;
        }
    }
    else if(type==4){//4代表向右移动
        if(indexCheck(1,0,this->process)){
            x++;
        }
    }
    rePaint(); //如果说没有发生任何移动 重绘回来 起重画和回溯作用 也需要检测是否死亡
}
void Control::gc(){ //垃圾回收 即发生移动过后 清楚上一步的痕迹
    for(int i=0;i<4;i++){
        map[this->x+block[this->type][this->process][i].x()][this->y+block[this->type][this->process][i].y()]=0;
    }
}
void Control::rePaint(){
    for(int i=0;i<4;i++){
        int tempx=this->x+block[this->type][this->process][i].x();
        int tempy=this->y+block[this->type][this->process][i].y();
        if(map[tempx][tempy]){//新砖块刷新 可地图已经有了内容 即死亡
            GameWidget::timer->stop();
            qDebug()<<"you are lose!";
        }
        else{
            map[tempx][tempy]=1;
        }
    }
}
void Control::clearRow(){
    int i,j;
    for(j=0;j<map[0].size();j++){ //因为是按x y格式进行标记的 所以删除方式比较特殊
        int flag1=true;
        for(i=0;i<map.size();i++){
            if(map[i][j]==0)
                flag1=false;
        }
        if(flag1){
            for(int k=0;k<map.size();k++){
                map[k].remove(j);
                map[k].insert(0,0); //插入到最前！！达到自动更新坐标
            }
        }
    }
}
void Control::operator=(Control &another){
   this->x=another.x;
    this->y=another.y;
   this->type=another.type;
    this->process=another.process;
    another.newBlock();
}
