#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamebutton.h"
#include<QPropertyAnimation>
#include"gamewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GameButton *gamebutton= NULL;
    gamewidget *game_widget=NULL;
 //   void paintEvent(QPaintEvent *event);
    QPropertyAnimation *start=NULL;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
