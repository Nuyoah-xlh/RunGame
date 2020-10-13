#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"gamebutton.h"
#include"gamewidget.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>

#define button1 ":/new/prefix1/image/startBtn1.png"
#define button2 ":/new/prefix1/image/startBtn2.png"
#define back_0  ":/new/prefix1/image/background.png"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口尺寸、标题
    this->setFixedSize(1280,720);
    this->setWindowTitle("RunGame");
    game_widget=new gamewidget(this,this->width(),this->height());  //建立游戏类
    gamebutton=new GameButton(button1,button2);  //建立按钮类
    gamebutton->setParent(this);
    gamebutton->move(600,400);
    connect(gamebutton,&QPushButton::clicked,this,
            [=]()
            {
                qDebug()<<"开始";
                start=new QPropertyAnimation(gamebutton,"geometry");
                start->setDuration(300);
                start->setEasingCurve(QEasingCurve::OutQuad);
                start->setStartValue(QRect(gamebutton->x(),gamebutton->y(),gamebutton->width(),gamebutton->height()));
                start->setEndValue(QRect(gamebutton->x(),750,gamebutton->width(),gamebutton->height()));
                start->start();
                game_widget->isRuning=true;
                game_widget->button=gamebutton;
                game_widget->start_game();
            }
               );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete start ;
    delete gamebutton ;
    delete game_widget ;
}





