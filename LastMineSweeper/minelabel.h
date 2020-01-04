#ifndef MINELABEL_H
#define MINELABEL_H

#include <QWidget>
#include<QLabel>
class MineLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MineLabel(int x,int y,QWidget *parent = nullptr);
    int x;//x坐标
    int y;//y坐标
    int type;//类型  砖块为0 地雷为1
    int isFlag;//控制是否被旗子标记
    bool visited;//标记是否被访问
    void setBlank(MineLabel* current);//处理空白砖
    int searchRound(int x,int y); //查找砖块周围 返回这个砖块四周的雷量
    bool isWin();
    static int canClick;//控制游戏能否被点击
    static QList<QSize> list;
    static bool isFirst;
    static int gameMines;
    static QPoint firstPoint;
    static bool king;
    void boom();
signals:
    void first();
    void win();
    void fail();
    void begin();
    void numberChange();
public slots:
protected:
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void enterEvent(QEvent *e);
    virtual void leaveEvent(QEvent *e);
};


#endif // MINELABEL_H
