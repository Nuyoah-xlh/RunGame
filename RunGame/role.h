#ifndef ROLE_H
#define ROLE_H

#include <QWidget>
#include"gamewidget.h"
#include<QTimer>

//class gamewidget;
class role : public QWidget
{
    Q_OBJECT
private:
    gamewidget *game;
    QPixmap run_image[5];  //奔跑图片
    QPixmap jump_img;  //跳跃图片
    //设定定时器

    int currunImg;  //作为奔跑图片下标
    //设置人物长度、宽度
    int wid;
    int hei;
    //设置人物坐标
    int x;
    int y;

public:
   // explicit role(QWidget *parent = nullptr);
    role(gamewidget *game);
    QTimer run_Timer;  //定时器
    QTimer jump_Timer;
    bool jump_once;  //已经跳了一次
    bool jump_twice;  //已经跳了两次
    bool in_fall;  //正在下落
    bool twice_jumpready;  //可以二次跳
    double fall_speed;  //下落速度
    double fallspeed_a;  //下落加速度
    double jump_speed;  //上升速度
    int jump_h;  //一次跳跃高度
    int getX();
    int getY();
    int getWid();
    int getHei();
    void move(bool up,bool down,bool right,bool esc);  //人物坐标移动
    QPixmap getImg();

signals:

public slots:
};

#endif // ROLE_H
