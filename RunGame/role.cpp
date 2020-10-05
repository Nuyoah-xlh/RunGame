#include "role.h"
#include<QTimer>
#include"gamewidget.h"
#include<QDebug>

//role::role(QWidget *parent) : QWidget(parent)
//{
//
//}
#define run_1 ":/new/prefix1/image/run_1.png"
#define run_2 ":/new/prefix1/image/run_2.png"
#define run_3 ":/new/prefix1/image/run_3.png"
#define run_4 ":/new/prefix1/image/run_4.png"
#define run_5 ":/new/prefix1/image/run_5.png"
#define jump ":/new/prefix1/image/jump.png"

role::role(gamewidget *game)
{
    game=game;
    this->wid=30;
    this->hei=40;
    this->x=100;
    this->y=610;
    jump_once=false;
    jump_twice=false;
    twice_jumpready=false;
    in_fall=false;
    jump_h=100;
    fall_speed=0;
    jump_speed=20;
    fallspeed_a=0.5;
    jump_Timer.setInterval(400);
    jump_Timer.setSingleShot(true);
    //加载图片
    for(int i=0;i<=4;i++)
    {
        run_image[i].load(QString(":/new/prefix1/image/run_%1.png").arg(i+1));
    }
    jump_img.load(jump);
    currunImg=0;
    run_Timer.setInterval(100);  //设定每帧时长
    connect(&run_Timer,&QTimer::timeout,
            [=]()
            {
               currunImg=(currunImg+1)%3;
              // qDebug()<<currunImg;

            }
      );

}
void role::move(bool up,bool down,bool right,bool esc)
{
    if(this->y==610)
    {
        twice_jumpready=true;
        fall_speed=0;
    }
    //向上跳
    if(up)
    {
        //在地上可以进行一段跳
        if(this->y==610)
        {
            jump_Timer.start();
            jump_once=false;
            //jump_twice=false;
        }
        //在空中，且一段跳结束，则可以进行二段跳
        if(this->y<610&& twice_jumpready && jump_once)
        {
            jump_Timer.start();
            //twice_jumpready=false;
            fall_speed=0;
            twice_jumpready=false;
        }
        if(jump_Timer.isActive())
        {
            this->y-=jump_speed*jump_Timer.remainingTime()/400;
        }
    }
    else
    {
        jump_Timer.stop();
        jump_once=true;
        //jump_twice=true;
        //jump_speed=20;
    }
    //自由下落
    this->y+=fall_speed;
    //范围限制，保证人物在画面内
    if(this->y>610)
    {
        this->y=610;
    }
    if(this->y<150)
    {
        this->y=150;
    }
    if(this->x<100)
    {
        this->x=100;
    }
    if(this->x>1000)
    {
        this->x=1000;
    }
    //不再向上跳了，就开始下落
    if(!jump_Timer.isActive())
    {
        fall_speed+=fallspeed_a;
        //qDebug()<<1;
    }
    else
    {
        fall_speed=0;
    }
    //加速下落
    if(down)
    {
        if(this->y<610&&!jump_Timer.isActive())
        {
            fall_speed+=2*fallspeed_a;
        }
    }
    //向右加速
    if(right)
    {
        this->x+=10;
    }
    else
    {
         this->x-=1;  //停止加速后，缓慢归位
    }
    //qDebug()<<y;
}
int role::getX()
{
    return this->x;
}
int role::getY()
{
    return this->y;
}
int role::getWid()
{
    return this->wid;
}
int role::getHei()
{
    return this->hei;
}
QPixmap role::getImg()
{
    QPixmap img;
    if(this->y<610)
    {
        img=jump_img;    //跳跃姿态
    }
    else if(this->y==610)
    {
        img=run_image[currunImg];  //奔跑姿态
    }
    else if(this->y>610)
    {
        img=jump_img;   //跳跃姿态
    }

    return img;
}

