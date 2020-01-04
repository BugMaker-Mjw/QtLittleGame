#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include<QTimer>
#include<QTime>
#include<QPushButton>
#include<QLabel>
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent = nullptr);
    QTimer* timer;
    QTime time;
    QWidget* ledLeft;//左边的显示屏
    QWidget* ledRight;//右边的显示屏
    QPushButton* game;
    QList<QLabel*> led1;
    QList<QLabel*> led2;
    void init();
    void ledChange(int number,QList<QLabel*> &list);
    static int gameTime;
signals:

public slots:
};

#endif // CONTROLWIDGET_H
