#ifndef CONTROL_H
#define CONTROL_H
#include<QVector>
#include<QPoint>
class Control
{
public:
    Control();
    int x; //当前处于的x坐标
    int y; //当前处于的y坐标
    int type; //方块的类型
    int process;//方块类型变成了那种了
    static QVector<QVector<int>> map; //map类  地图信息
    static QVector<QVector<QVector<QPoint>>> block; //留存砖块形状 配合control类生成方块
    void newBlock();//生成新的砖块
    bool indexCheck(int moveX,int moveY,int newProcess); //砖块发生移动的时候 检查下标
    void move(int type);
    void gc();
    void rePaint();
    void clearRow();
    void operator=(Control&);
};

#endif // CONTROL_H
