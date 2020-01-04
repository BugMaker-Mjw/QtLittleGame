#ifndef WIDGET_H
#define WIDGET_H
#include"snake.h"
#include <QWidget>
#include"food.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void paintEvent(QPaintEvent *e);
    Food food;
    snake *snake1;
    QTimer *time;
    void keyPressEvent(QKeyEvent *ev);
    bool EatFood();
    void start();
    void stop();
};

#endif // WIDGET_H
