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
    Coinnum = 0 ;
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
                            r->reduceHp();
                            barrier.clear();
                            break ;
                        }
                        if(!barrier.empty())
                        {
                            (*i)->move();
                        }

                     }
                  }
                for(auto i=barrier2.begin();i!=barrier2.end();i++)
                {
                    if((*i)->done())
                    {
                        i=barrier2.erase(i);
                    }
                    else
                    {
                        if((*i)->isCollision(r->getX()-5,r->getY()-5,r->getWid()-5,r->getWid()-5))
                        {
                            //r->reduceHp();
                             barrier2.erase(i);
                             Coinnum++ ;
                            break ;
                        }
                        if(!barrier2.empty())
                        {
                            (*i)->move();
                        }
                    }

                }
                for(auto i=barrier3.begin();i!=barrier3.end();i++)
                {
                    if((*i)->done())
                    {
                        i=barrier3.erase(i);
                    }
                    else
                    {
                        if((*i)->isCollision(r->getX(),r->getY(),r->getWid(),r->getWid()))
                        {
                            r->reduceHp();
                            i=barrier3.erase(i);

                        }
                        if(!barrier3.empty())
                        {
                            (*i)->move();
                        }
                    }

                }
                if(isRuning)
                {
                    addBarriers();  //增加障碍物函数
                }
               // update();
            }
      );

}
gamewidget::~gamewidget()
{
    delete r;
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
        //qDebug()<<r->getX()<<r->getY();
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


       //血量绘制
       painter.drawRect(QRect(1000,50,150,10));
       painter.fillRect(QRect(1000,50,r->getCurHpPercent()*150/100,10),Qt::red);
       painter.drawLine(1050,50,1050,60);
       painter.drawLine(1100,50,1100,60);
       QPen pen1(Qt::black);
       painter.setFont(QFont("黑体",20));
       pen1.setColor(Qt::black);
       painter.setPen(pen1);
       painter.drawText(1000,100,QString("HP:%1%").arg(r->getCurHpPercent()));
       //绘制金币数量
       painter.drawText(100,100,QString("Coinnum:%1").arg(Coinnum)) ;
       //分数绘制
        painter.drawText(500,100,QString("Score:%1").arg(r->getScore()));
       //绘制障碍物
       for(auto i=barrier.begin();i!=barrier.end();i++)
       {
           painter.drawPixmap(QRect((*i)->getX(),(*i)->getY(),(*i)->getWidth(),(*i)->getHeight()),(*i)->getImg());
       }
       for(auto i=barrier2.begin();i!=barrier2.end();i++)
       {
           painter.drawPixmap(QRect((*i)->getX(),(*i)->getY(),(*i)->getWidth(),(*i)->getHeight()),(*i)->getImg());
       }
       for(auto i=barrier3.begin();i!=barrier3.end();i++)
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

        int y=this->ground_Y*0.7-(rand()%(int)(ground_Y*0.3));
        barrier.push_back(new Wall(x,y,70,ground_Y-y));
        LastWall_time=0;
    }
    LastWall_time++;

    static int LastCoin_time;
   // srand(time(NULL));
    if(LastCoin_time>=20)
    {

        int x= this->width()+5 ;
        int y = ground_Y-rand()%400;
        barrier2.push_back(new Coin(x,y,15,16));
        LastCoin_time=0;
        //qDebug()<<12333;
    }
    LastCoin_time++;

    static int LastArrow_time;
    //srand(time(NULL));
    if(LastArrow_time>=100)
    {

        int x=-800;
        int y =ground_Y-rand()%400;
        barrier3.push_back(new Arrow(x,y,400,100));
        LastArrow_time=0;

    }
    LastArrow_time++;



}
void gamewidget::start_game()
{
    r=new role(this);
    r->run_Timer.start();
    remove.start();
    r->hp_Timer.start();
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
        if(isPause==false)
        {
            gamepause();
        }
        else
        {
            gamecontinue()  ;
        }
    }
    else if(event->key()==Qt::Key_Q)
    {
         r->dashmove_() ;
    }

    else
    {
        return QWidget::keyPressEvent(event);
    }
}
void gamewidget::gamepause()
{
    isPause = true;
    remove.stop() ;
    r->pauserole();
}
void gamewidget::gamecontinue()
{
    isPause = false;
    remove.start() ;
    r->continuerole();
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
