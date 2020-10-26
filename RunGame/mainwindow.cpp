#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"gamebutton.h"
#include"gamewidget.h"
#include"ui_mainwindow.h"
#include<QPaintEvent>
#include<QPainter>
#include<QPushButton>
#include<QMessageBox>
#include<QMenu>
#include<QMenuBar>

#define button1 ":/new/prefix1/image/startBtn1.png"
#define button2 ":/new/prefix1/image/startBtn2.png"
#define button3 ":/new/prefix1/image/instruction1.png"
#define button4 ":/new/prefix1/image/instruction2.png"
#define button5 ":/new/prefix1/image/keyboard1.png"
#define button6 ":/new/prefix1/image/keyboard2.png"
#define button7 ":/new/prefix1/image/archive1.png"
#define button8 ":/new/prefix1/image/archive2.png"
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
    gamebutton->move(900,400);

    gamebutton2=new GameButton(button3,button4);  //建立按钮类
    gamebutton2->setParent(this);
    gamebutton2->move(700,425);
    QString str_0=  "玩 法 :\n"
                    "   1.点击开始以进入游戏。\n"
                    "   2.游戏以避开障碍物，吃到尽可能多的金币为目标。\n"
                    "   3.不碰到障碍物人物会自动回血，血条为空时死亡，游戏结束。\n"
                    "   4.游戏结束后可通过'R'键来复活；通过'B'键来回到首页。";
    connect(gamebutton2,&QPushButton::clicked,this,
            [=]()
            {
                 QMessageBox::about(this,"玩法",str_0);
            }
               );
    gamebutton3=new GameButton(button5,button6);  //建立按钮类
    gamebutton3->setParent(this);
    gamebutton3->move(500,425);
    QString str_1=  "操 作 :\n"
                    "   1.左右方向键控制人物前进后退\n"
                    "   2.上方向键控制人物跳跃\n"
                    "   3.下方向键控制人物快速下落\n"
                    "   4.'Q'键控制人物冲刺";
    connect(gamebutton3,&QPushButton::clicked,this,
            [=]()
            {
                 QMessageBox::about(this,"操作",str_1);
            }
               );
    gamebutton4=new GameButton(button7,button8);  //建立按钮类
    gamebutton4->setParent(this);
    gamebutton4->move(300,425);

    connect(gamebutton4,&QPushButton::clicked,this,
            [=]()
            {

            }
               );
    connect(gamebutton,&QPushButton::clicked,this,
            [=]()
            {
                //qDebug()<<"开始";
                start=new QPropertyAnimation(gamebutton,"geometry");
                start->setDuration(300);
                start->setEasingCurve(QEasingCurve::OutQuad);
                start->setStartValue(QRect(gamebutton->x(),gamebutton->y(),gamebutton->width(),gamebutton->height()));
                start->setEndValue(QRect(gamebutton->x(),750,gamebutton->width(),gamebutton->height()));
                start->start();
                game_widget->isRuning=true;
                game_widget->button=gamebutton;
                game_widget->button_2=gamebutton2;
                game_widget->button_3=gamebutton3;
                game_widget->button_4=gamebutton4;
                game_widget->start_game();
                gamebutton2->hide();
                gamebutton3->hide();
                gamebutton4->hide();
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

