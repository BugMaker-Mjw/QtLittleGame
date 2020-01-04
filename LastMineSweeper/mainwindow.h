#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QAction>
#include"gamewidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QPixmap getImage(QString src,int width=30,int height=30);
    QMap<QAction*,QSize> map;
    GameWidget* gameWidget;
    void allWidgetUpdate();
    ControlWidget* controlWidget;
    static QWidget* mineKing;
    static int king;
    void keyPressEvent(QKeyEvent * event);
};

#endif // MAINWINDOW_H
