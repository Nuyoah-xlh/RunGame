#include "gamebutton.h"
#include<QPushButton>

GameButton::GameButton(QString str,QString str2)
{
    img1.load(str);
    img2.load(str2);
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setFixedSize(QSize(img1.width(),img1.height())); //按钮尺寸
    this->setIcon(img1);            //按钮图标
    this->setIconSize(QSize(img1.width(),img1.height()));  //图标尺寸
    isRun = false;
}

GameButton::~GameButton()
{

}
void GameButton::init()
{
    this->move(600,400);
}
void GameButton::mouseReleaseEvent(QMouseEvent *e)
{
    //qDebug()<<"鼠标点击";
    isRun = true;  //进入游戏
    //this->move(this->x(),this->y()+25);
    return QPushButton::mouseReleaseEvent(e);
}

void GameButton::enterEvent(QEvent *event)
{
    //qDebug()<<"鼠标进入";
    this->setFixedSize(QSize(img2.width(),img2.height()));  //设置更大图标
    this->setIcon(img2);
    this->setIconSize(QSize(img2.width(),img2.height()));
    this->move(this->x()-50,this->y()-50);
}
void GameButton::leaveEvent(QEvent *event)
{
    //qDebug()<<"鼠标离开";
    this->setFixedSize(QSize(img1.width(),img1.height())); //按钮尺寸
    this->setIcon(img1);            //按钮图标
    this->setIconSize(QSize(img1.width(),img1.height()));  //图标尺寸
    this->move(this->x()+50,this->y()+50);
}


