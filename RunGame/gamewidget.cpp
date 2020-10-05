#include "gamewidget.h"
#include"gamebutton.h"
#include"role.h"
#include<QPainter>
#include<QPaintEvent>
#include<QDebug>
#include<QVector>
#include<vector>
#include<time.h>
#include<QTime>
#include<ctime>

//class role;

#define back_up ":/new/prefix1/image/startBkg.png"
#define back_mid ":/new/prefix1/image/startBkg2.png"
#define back_down ":/new/prefix1/image/foggy.png"
#define before ":/new/prefix1/image/background.png"
#define ground_img ":/new/prefix1/image/ground.png"

gamewidget::gamewidget(QWidget *parent,int wid,int heig) : QWidget(parent)
{
    this->resize(wid,heig);  //固定尺寸
    ground_Y=heig-70;
    //R=nullptr;
    //加载背景图
    background[0].load(back_up);
    background[1].load(back_mid);
    background[2].load(back_down);
    before_start.load(before);
    ground.load(ground_img);
    //按键初始化
    up=false;
    down=false;
    right=false;
    esc=false;
    isRuning=false;
    isPause=false;
    ground_speed=1;
    ground_X=0;
    //setAttribute(Qt::WA_OpaquePaintEvent);
    remove.setInterval(17);
    this->grabKeyboard(); //激活键盘事件捕获
    connect(&remove,&QTimer::timeout,
            [=]()
            {
                r->move(up,down,right,esc);
                for(auto i=barrier.begin();i!=barrier.end();i++)
                {
                    if((*i)->done())
                    {
                        i=barrier.erase(i);
                    }
                    else
                    {
                        if((*i)->isCollision(r->getX()-5,r->getY()-5,r->getWid()-5,r->getWid()-5))
                        {
                            barrier.clear();
                        }
                        (*i)->move();
                    }

                }
                if(isRuning)
                {
                    addBarriers();  //增加障碍物函数
                }
                update();
            }
      );

}
void gamewidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    if(isRuning==false)
    {
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(before_start));
       // qDebug()<<"2222";
    }
    else
    {
       // painter.drawPixmap(QRect(0,0,this->width(),this->height())
                 //    ,background_up
          //           ,QRect(backImgX[0],0,this->width(),this->height()));
       // painter.drawPixmap(QRect(0,0,this->width(),this->height())
                //     ,background_mid
       //              ,QRect(backImgX[1],0,this->width(),this->height()));
       // painter.drawPixmap(QRect(0,0,this->width(),this->height())
        //             ,background_down
      //               ,QRect(backImgX[2],0,this->width(),this->height()));
        // painter.drawPixmap(QRect(r->getX(),r->getY(),r->getWid(),r->getHei()),r->getImg());
        for(int i=0;i<3;i++)   //叠加背景图片
        {
            painter.drawPixmap(QRect(0,0,this->width(),this->height())
                         ,background[i]
                         ,QRect(backImgX[i],0,this->width(),this->height()));  //在指定区域绘制指定尺寸的图片
            if(backImgX[i]>0)
            {
                painter.drawPixmap(QRect(background[i].width()-backImgX[i],0,this->width()-(background[i].width()-backImgX[i]),this->height())
                             ,background[i]
                             ,QRect(0,0,this->width()-(background[i].width()-backImgX[i]),this->height()));   //补充右边的空白区域
            }
            if(backImgX[i]>=background[i].width())
            {
                  backImgX[i]-=background[i].width();
            }
            if(isRuning&&isPause==false)
            {
                backImgX[i]+=imgSpeed[i]; //图片剪切区域x起点
            }
        }
        //绘制地面
        painter.drawPixmap(QRect(0,ground_Y,this->width(),this->height()-ground_Y)
                     ,ground
                     ,QRect(ground_X,0,this->width(),this->height()- ground_Y));
        if(ground_X>ground.width()-this->width())   //补充空白
        {
            painter.drawPixmap(QRect(ground.width()-ground_X,this->ground_Y,this->width()-(ground.width()-ground_X),this->height()-this->ground_Y)
                         ,ground
                         ,QRect(0,0,this->width()-(ground.width()-ground_X),this->height()-this->ground_Y));
        }
        if(ground_X>=ground.width())
        {
             ground_X-=ground.width();
        }
        if(isRuning&&isPause==false)
        {
            ground_X+=ground_speed;
        }
        //绘制人物
       painter.drawPixmap(QRect(r->getX(),r->getY(),r->getWid(),r->getHei()),r->getImg());
       //绘制障碍物
       for(auto i=barrier.begin();i!=barrier.end();i++)
       {
           painter.drawPixmap(QRect((*i)->getX(),(*i)->getY(),(*i)->getWidth(),(*i)->getHeight()),(*i)->getImg());
       }
       update();
    }

}
void gamewidget::addBarriers()   //，添加障碍物，可添加更多类型
{
    static int LastWall_time;
    srand(time(NULL));
    if(LastWall_time>=200)
    {

        int x=this->width()+10;

        int y=(rand()%(int)(ground_Y*0.4))+this->ground_Y*0.6;
        barrier.push_back(new Wall(x,y,70,ground_Y-y));
        LastWall_time=0;
    }
    LastWall_time++;
}
void gamewidget::start_game()
{
    r=new role(this);
    r->run_Timer.start();
    remove.start();
    update();

}
void gamewidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        up=true;
        //qDebug()<<up;
    }
    else if(event->key()==Qt::Key_S)
    {
        down=true;
    }
    else if(event->key()==Qt::Key_D)
    {
        right=true;
    }
    else if(event->key()==Qt::Key_Escape)
    {
        esc=true;
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }
}
void gamewidget::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_W)
    {
        up=false;
        //qDebug()<<up;
    }
    else if(event->key()==Qt::Key_S)
    {
        down=false;
    }
    else if(event->key()==Qt::Key_D)
    {
        right=false;
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }
}
