#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include"minelabel.h"
#include"controlwidget.h"
class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    static QVector<QVector<MineLabel*>> mines;
    static int row;
    static int column;
    static int totalMines;
    void updateGame();
    void gameUpdate();
    QSize getSize();
    void createMines();
signals:
    void reBind();
    void begin();
public slots:
};

#endif // GAMEWIDGET_H
