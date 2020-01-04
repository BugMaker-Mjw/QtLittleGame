#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "control.h"
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    //这个是游戏主窗口
    //这里主要绘制图像和捕捉按键事件 而具体的逻辑 交给control类实现
    explicit GameWidget(QWidget *parent = nullptr);
    static Control con;
    static Control anotherCon;
    static QTimer *timer;
signals:

public slots:
protected:
    virtual void keyPressEvent (QKeyEvent *);
    virtual void paintEvent (QPaintEvent *);
};

#endif // GAMEWIDGET_H
