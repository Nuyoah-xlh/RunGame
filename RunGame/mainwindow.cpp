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
#include<QSound>

#define button1 ":/new/prefix1/image/startBtn1.png"
#define button2 ":/new/prefix1/image/startBtn2.png"
#define button3 ":/new/prefix1/image/instruction1.png"
#define button4 ":/new/prefix1/image/instruction2.png"
#define button5 ":/new/prefix1/image/keyboard1.png"
#define button6 ":/new/prefix1/image/keyboard2.png"
#define button7 ":/new/prefix1/image/archive1.png"
#define button8 ":/new/prefix1/image/archive2.png"
#define back_0  ":/new/prefix1/image/background.png"
#define title ":/new/prefix1/image/title.png"
#define back_sound ":/new/prefix1/sound/Theme.wav"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置窗口尺寸、标题
    this->setFixedSize(1280,720);
    this->setWindowIcon(QPixmap(title)); //设置应用图标
    this->setWindowTitle("RunGame");
    QSound *startsound=new QSound(back_sound,this);
    startsound->play();//播放背景音乐
    startsound->setLoops(-1); //设置单曲循环
    game_widget=new gamewidget(this,this->width(),this->height());  //建立游戏类
    gamebutton=new GameButton(button1,button2);  //建立按钮类
    gamebutton->setParent(this);
    gamebutton->move(900,400);

    gamebutton2=new GameButton(button3,button4);  //建立按钮类
    gamebutton2->setParent(this);
    gamebutton2->move(700,425);
    QString str_0=  "游 戏 玩 法 :\n"
                    "   1.点击开始以进入游戏。\n"
                    "   2.游戏以控制火柴人避开障碍物，吃到尽可能多的金币为主要目标。\n"
                    "   3.控制火柴人跑得越远得分越高，吃到金币会有加分并增加金币数，碰到障碍物会有扣分。\n"
                    "   4.吃到红心会加速回血，吃到法杖会暂时消除所有障碍物。\n"
                    "   5.不碰到障碍物人物会自动缓慢回血，血条为空时死亡，游戏结束。\n"
                    "   6.游戏会自动记录你的最高记录，试着打破它！";

    connect(gamebutton2,&QPushButton::clicked,this,
            [=]()
            {
                 QMessageBox::about(this,"游 戏 玩 法",str_0);

            }
               );
    gamebutton3=new GameButton(button5,button6);  //建立按钮类
    gamebutton3->setParent(this);
    gamebutton3->move(500,425);
    QString str_1=  "按 键 操 作 :\n"
                    "   1.按下W键控制火柴人向上跳跃，在空中可进行二次跳跃。\n"
                    "   2.按下S键控制火柴人加速下落。\n"
                    "   3.按下A键控制火柴人向左加速移动。\n"
                    "   4.按下D键控制火柴人向右加速。\n"
                    "   5.游戏中按下esc键暂停游戏，再次按下esc键继续游戏。\n"
                    "   6.游戏结束后按下R键重新开始游戏，按下B键返回游戏主菜单。";
    connect(gamebutton3,&QPushButton::clicked,this,
            [=]()
            {
                 QMessageBox::about(this,"操作方法",str_1);

            }
               );
    gamebutton4=new GameButton(button7,button8);  //建立按钮类
    gamebutton4->setParent(this);
    gamebutton4->move(300,425);

    connect(gamebutton4,&QPushButton::clicked,this,
            [=]()
            {
               QString str = "你的最高分数为：" + QString("%1分").arg(game_widget->maxscore);
                QMessageBox::about(this,"最高记录",str) ;

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

