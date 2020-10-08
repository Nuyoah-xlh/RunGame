#ifndef BARRIERS_H
#define BARRIERS_H

//#include <QWidget>
#include<QPixmap>
#include<QTimer>

///////障碍物基类///////
class Barriers
{
  //  Q_OBJECT
private:
    int x,y;
    int width,height;
public:
  //  explicit Barriers(QWidget *parent = nullptr);
    Barriers(int x,int y,int width,int height);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getWidth();
    int getHeight();


signals:

public slots:
};

///////派生类墙体类///////
class Wall:public Barriers
{
private:
    QPixmap img;
public:
    int speed;
    Wall(int x,int y,int width,int height);
    QPixmap getImg();
    bool isCollision(int lx,int ly,int wid,int hei);  //判断是否发生碰撞
    void move();  //障碍移动
    bool done();  //障碍是否已过去
};

///////金币///////
class Coin:public Barriers
{
private:
    QPixmap img[4];
public:
    QTimer coinappear ;
    int speed;
    Coin(int x,int y,int width,int height);
    QPixmap getImg();
    bool isCollision(int lx,int ly,int wid,int hei);  //判断是否发生碰撞
    void move();  //障碍移动
    bool done();  //障碍是否已过去
    int cointime;

};

///////箭///////
class Arrow:public Barriers
{
private:
    QPixmap img;
public:
    int speed;
    Arrow(int x,int y,int width,int height);
    QPixmap getImg();
    bool isCollision(int lx,int ly,int wid,int hei);  //判断是否发生碰撞
    void move();  //障碍移动
    bool done();  //障碍是否已过去
};



#endif // BARRIERS_H
