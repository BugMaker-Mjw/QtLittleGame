#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "myplane.h"
#include<QTimer>
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void setstart(QWidget *start);
    void init();
protected:
    void paintEvent(QPaintEvent *e);
    void keyPressEvent(QKeyEvent *ev);
private:
    MyPlane * myplane;
    QTimer *plane1;
    QTimer *plane2;
    QTimer *plane3;
    QWidget * start;
    int control;
signals:

public slots:
    void Gameover();
};

#endif // GAMEWIDGET_H
