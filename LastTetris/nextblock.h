#ifndef NEXTBLOCK_H
#define NEXTBLOCK_H

#include <QWidget>

class NextBlock : public QWidget
{
    Q_OBJECT
public:
    explicit NextBlock(QWidget *parent = nullptr);
    void paintEvent (QPaintEvent *e);
signals:

public slots:
};

#endif // NEXTBLOCK_H
