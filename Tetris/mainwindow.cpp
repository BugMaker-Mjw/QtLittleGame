#include "mainwindow.h"
#include "gamewidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    GameWidget *widget = new GameWidget();

    widget->show();
    //this->resize(900,900);
}

MainWindow::~MainWindow()
{

}
