#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gamewidget.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private:
    GameWidget *sonwidget;
    void paintEvent(QPaintEvent *ev);
};

#endif // WIDGET_H
