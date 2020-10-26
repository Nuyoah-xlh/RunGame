#include "barriers.h"

#include<QTimer>
#include<QDebug>

#define wall_1 ":/new/prefix1/image/wall1.png"
#define wall_2 ":/new/prefix1/image/wall2.png"
#define coin_1 ":/new/prefix1/image/coin_001.png"
#define coin_2 ":/new/prefix1/image/coin_002.png"
#define coin_3 ":/new/prefix1/image/coin_003.png"
#define coin_4 ":/new/prefix1/image/coin_004.png"
#define arrow_1 ":/new/prefix1/image/arrow.png"
#define blood ":/new/prefix1/image/blood.png"
#define magic ":/new/prefix1/image/clear.png"


/////基类////
Barriers::Barriers(int x,int y,int width,int height)
{
    //成员初始化
    this->x=x;
    this->y=y;
    this->width=width;
    this->height=height;
}
int Barriers::getX()
{
    return this->x;

}
int Barriers::getY()
{
    return this->y;

}
void Barriers::setX(int x)
{
    this->x=x;
}
void Barriers::setY(int y)
{
    this->y=y;
}
int Barriers::getWidth()
{
    return this->width;

}
int Barriers::getHeight()
{
    return this->height;

}
/////墙体类////
Wall::Wall(int x, int y, int width, int height)
    :Barriers(x,y,width,height)
{
    srand(time(NULL));
    this->img.load(QString(":/new/prefix1/image/wall%1.png").arg(rand()%2+1));  //两种墙，随机取出
}
QPixmap Wall::getImg()
{
    return this->img;
}
bool Wall::isCollision(int lx, int ly, int lwid, int lhei)
{
    QRect rect_1(this->getX(),this->getY(),this->getWidth(),this->getHeight());
    QRect rect_2(lx,ly,lwid,lhei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}
void Wall::move()
{
    this->setX(this->getX()-5);

}
bool Wall::done()
{
    if(this->getX()<=(-this->getWidth()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/////金币////
Coin::Coin(int x, int y, int width, int height)
    :Barriers(x,y,width,height)
{

    this->img[0].load(QString(":/new/prefix1/image/coin_001.png"));
    this->img[1].load(QString(":/new/prefix1/image/coin_002.png"));
    this->img[2].load(QString(":/new/prefix1/image/coin_003.png"));
    this->img[3].load(QString(":/new/prefix1/image/coin_004.png"));
    cointime=0;
    coinappear.setInterval(100);
    QObject::connect(&coinappear,&QTimer::timeout,
            [=]()
            {
                cointime=(cointime+1)%3;
            }
      );

    coinappear.start();

}


QPixmap Coin::getImg()
{
    return this->img[cointime];
}
bool Coin::isCollision(int lx, int ly, int lwid, int lhei)
{
    QRect rect_1(this->getX(),this->getY(),this->getWidth()-30,this->getHeight()+20);
    QRect rect_2(lx,ly,lwid,lhei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}
void Coin::move()
{
    this->setX(this->getX()-5);

}
bool Coin::done()
{
    if(this->getX()<-10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/////血瓶////
Bottle::Bottle(int x, int y, int width, int height)
    :Barriers(x,y,width,height)
{

    img.load(blood);

}
QPixmap Bottle::getImg()
{
    return this->img;
}
bool Bottle::isCollision(int lx, int ly, int lwid, int lhei)
{
    QRect rect_1(this->getX(),this->getY(),this->getWidth()-30,this->getHeight()+20);
    QRect rect_2(lx,ly,lwid,lhei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}
void Bottle::move()
{
    this->setX(this->getX()-5);

}
bool Bottle::done()
{
    if(this->getX()<-10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/////法杖////
Magic::Magic(int x, int y, int width, int height)
    :Barriers(x,y,width,height)
{

    img.load(magic);

}
QPixmap Magic::getImg()
{
    return this->img;
}
bool Magic::isCollision(int lx, int ly, int lwid, int lhei)
{
    QRect rect_1(this->getX(),this->getY(),this->getWidth()-30,this->getHeight()+20);
    QRect rect_2(lx,ly,lwid,lhei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}
void Magic::move()
{
    this->setX(this->getX()-5);

}
bool Magic::done()
{
    if(this->getX()<-10)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/////箭////
Arrow::Arrow(int x, int y, int width, int height)
    :Barriers(x,y,width,height)
{
    this->img.load(arrow_1);
}
QPixmap Arrow::getImg()
{
    return this->img;
}
bool Arrow::isCollision(int lx, int ly, int lwid, int lhei)
{
    QRect rect_1(this->getX(),this->getY(),this->getWidth()-300,this->getHeight()-20);
    //qDebug()<<this->getX()<<this->getY()<<this->getWidth()<<this->getHeight();
    QRect rect_2(lx,ly,lwid,lhei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}
void Arrow::move()
{
    this->setX(this->getX()-10);

}
bool Arrow::done()
{
    if(this->getX()<=(-this->getWidth()))
    {
        return true;
    }
    else
    {
        return false;
    }
}
