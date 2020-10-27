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
#include<QMessageBox>
#include<QFile>
#include<QSound>
#include<QDesktopServices>
//class role;

#define back_up ":/new/prefix1/image/startBkg.png"
#define back_mid ":/new/prefix1/image/startBkg2.png"
#define back_down ":/new/prefix1/image/foggy.png"
#define before ":/new/prefix1/image/background.png"
#define ground_img ":/new/prefix1/image/ground.png"
#define hurtimg ":/new/prefix1/image/hurt.png"
#define gameover ":/new/prefix1/image/gameover.jpg"
#define pause ":/new/prefix1/image/pause.jpg"
#define jump ":/new/prefix1/sound/jump.wav"
#define coin ":/new/prefix1/sound/coin.wav"
#define over ":/new/prefix1/sound/over.wav"
#define collision ":/new/prefix1/sound/collision.wav"


gamewidget::gamewidget(QWidget *parent,int wid,int heig) : QWidget(parent)
{
    QFile file("save.txt");
    QTextStream txtInput(&file);
    QString lineStr;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
       // qDebug()<<"Open failed." << endl;
        return ;
    }
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readAll();
        //if (count==0)
        maxscore=lineStr.toInt();

        //count ++ ;
        //qDebug()<<"12345   " << maxscore ;
    }
    file.close();


    this->resize(wid,heig);  //固定尺寸
    ground_Y=heig-70;

    //加载背景图
    background[0].load(back_up);
    background[1].load(back_mid);
    background[2].load(back_down);
    before_start.load(before);
    ground.load(ground_img);
    hurtImg.load(hurtimg);
    pauseImg.load(pause);
    gameOverImg.load(gameover);
    //按键初始化
    up=false;
    down=false;
    left=false;
    difficult=0;
    right=false;
    //esc=false;
    isRuning=false;
    isPause=false;
    ground_speed=1;
    ground_X=0;
    Score=0;
    beforegame=true;
    Coinnum = 0 ;
   // difficult=0;
    //setAttribute(Qt::WA_OpaquePaintEvent);
    remove.setInterval(17);
    this->grabKeyboard(); //激活键盘事件捕获
   // static n;
    connect(&remove,&QTimer::timeout,
            [=]()
            {
                r->move(up,down,right,left);
                if(difficult<=80)   //随时间提高难度
                {
                    difficult+=0.0015;

               }
                else
                {
                    difficult=80;
                }
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
                            QSound::play(collision);
                            r->reduceHp();
                            if(r->getScore()>=100)  //撞击到障碍物扣分
                            {
                                r->setScore(-100);
                            }
                            else
                            {
                                r->setScore(0);
                            }
                            hurtImgAlpha=255;
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
                           // QSound::play(collision);
                            //r->reduceHp();
                            QSound::play(coin);
                             r->setScore(30); //吃到金币加分
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
                            QSound::play(collision);
                            if(r->getScore()>=100)  //撞击到障碍物扣分
                            {
                                r->setScore(-100);
                            }
                            else
                            {
                                r->setScore(0);
                            }
                            r->reduceHp();
                            hurtImgAlpha=255;
                            barrier3.clear();
                            break;

                        }
                        if(!barrier3.empty())
                        {
                            (*i)->move();
                        }
                    }

                }
                for(auto i=barrier4.begin();i!=barrier4.end();i++)
                {
                    if((*i)->done())
                    {
                        i=barrier4.erase(i);
                    }
                    else
                    {
                        if((*i)->isCollision(r->getX()-5,r->getY()-5,r->getWid()-5,r->getWid()-5))
                        {

                            r->increaseHp(700);
                             i=barrier4.erase(i);
                             //Coinnum++ ;
                            break ;
                        }
                        if(!barrier4.empty())
                        {
                            (*i)->move();
                        }
                    }

                }
                for(auto i=barrier5.begin();i!=barrier5.end();i++)
                {
                    if((*i)->done())
                    {
                        i=barrier5.erase(i);
                    }
                    else
                    {
                        if((*i)->isCollision(r->getX()-5,r->getY()-5,r->getWid()-5,r->getWid()-5))
                        {

                            // QSound::play(fazhang);
                             barrier5.clear();
                             barrier.clear();
                             barrier3.clear();
                             barrier6.clear();
                             //Coinnum++ ;
                            break ;
                        }
                        if(!barrier5.empty())
                        {
                            (*i)->move();
                        }
                    }


                }
                for(auto i=barrier6.begin();i!=barrier6.end();i++)
                {
                    if((*i)->done())
                    {
                        i=barrier6.erase(i);
                    }
                    else
                    {
                        if((*i)->isCollision(r->getX(),r->getY(),r->getWid(),r->getWid()))
                        {
                            QSound::play(collision);
                            if(r->getScore()>=100)  //撞击到障碍物扣分
                            {
                                r->setScore(-100);
                            }
                            else
                            {
                                r->setScore(0);
                            }
                            r->reduceHp();
                            hurtImgAlpha=255;
                            barrier6.clear();
                            break;

                        }
                        if(!barrier6.empty())
                        {
                            (*i)->move();
                        }
                    }

                }
                if(isRuning)
                {
                    if(r->getCurHp()<=0)
                    {
                        gameIsOver();   //血量为0则游戏结束
                         //存档
                        QFile file("save.txt");
                                                QTextStream txtInput(&file);
                                                QString lineStr;
                                                if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                                                {
                                                    qDebug()<<"Open failed." << endl;
                                                    return ;
                                                }
                                                while(!txtInput.atEnd())
                                                {
                                                    lineStr = txtInput.readAll();
                                                    //if (count==0)
                                                    maxscore=lineStr.toInt();

                                                    //count ++ ;
                                                    //qDebug()<<"12345   " << maxscore ;
                                                }
                                                file.close();

                                                //QFile file("save.txt");
                                                if(Score>maxscore)
                                                {
                                                    if ( file.exists())
                                                    {
                                                        file.remove();
                                                    }
                                                    file.open( QIODevice::WriteOnly );
                                                    file.close();
                                                    if (file.open(QFile::WriteOnly | QIODevice::Append|QIODevice::Text)) {
                                                    QTextStream out(&file);
                                                    out  << Score ;
                                                    //qDebug()<<"2222";
                                                    }
                                                    file.close();
                                                }







                }
                    addBarriers();  //增加障碍物函数
               // update();
            }
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
    if(isRuning==false&&beforegame==true)   //游戏首页
    {
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(before_start));


       // qDebug()<<"2222";
    }
    else if(GameOver==true)  //结束游戏
    {
        //GameIsOver绘制


        if(GameOver)
        {
            painter.drawPixmap(QRect(240,60,800,600),gameOverImg);
        }
    }
    else  //游戏中绘制
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



       //受伤绘制
       if(hurtImgAlpha!=0) {
           QPixmap temp(hurtImg.size());

           temp.fill(Qt::transparent);
           QPainter p2(&temp);
           p2.setCompositionMode(QPainter::CompositionMode_Source);
           p2.drawPixmap(0,0,hurtImg);
           p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
           p2.fillRect(temp.rect(),QColor(0,0,0,hurtImgAlpha));
           painter.drawPixmap(QRect(0,0,this->width(),this->height()),temp);
           hurtImgAlpha-=3;
       }

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
       for(auto i=barrier4.begin();i!=barrier4.end();i++)
       {
           painter.drawPixmap(QRect((*i)->getX(),(*i)->getY(),(*i)->getWidth(),(*i)->getHeight()),(*i)->getImg());
       }
       for(auto i=barrier5.begin();i!=barrier5.end();i++)
       {
           painter.drawPixmap(QRect((*i)->getX(),(*i)->getY(),(*i)->getWidth(),(*i)->getHeight()),(*i)->getImg());
       }
       for(auto i=barrier6.begin();i!=barrier6.end();i++)
       {
           painter.drawPixmap(QRect((*i)->getX(),(*i)->getY(),(*i)->getWidth(),(*i)->getHeight()),(*i)->getImg());
       }

       //暂停绘制
       if(isPause&&!GameOver)
       {
           painter.drawPixmap((this->width()-pauseImg.width())/2,(this->height()-pauseImg.height())/2,pauseImg);
       }
       update();
    }

}
void gamewidget::addBarriers()   //，添加障碍物，可添加更多类型
{
    static int LastWall_time;
    srand(time(NULL));
    if(LastWall_time>=200-difficult)
    {

        int x=this->width()+10;

        int y=this->ground_Y-100-(rand()%(int)(ground_Y*0.3));
        barrier.push_back(new Wall(x,y,70,ground_Y-y));
        LastWall_time=0;
    }
    LastWall_time++;

    static int LastCoin_time;
   // srand(time(NULL));
    if(LastCoin_time>=30-difficult)
    {

        int x= this->width()+5 ;
        int y = ground_Y-18-rand()%300;
        barrier2.push_back(new Coin(x,y,15,16));
        LastCoin_time=0;
        //qDebug()<<12333;
    }
    LastCoin_time++;

    static int LastArrow_time;
    //srand(time(NULL));
    if(LastArrow_time>=100-difficult)
    {

        int x=this->width()+100;
        int y =ground_Y-90-rand()%400;
        barrier3.push_back(new Arrow(x,y,400,100));
        LastArrow_time=0;

    }
    LastArrow_time++;

    static int LastBlood_time;
    //srand(time(NULL));
    if(LastBlood_time>=250)
    {

        int x= this->width()+10 ;
        int y = ground_Y-45-rand()%300;
        barrier4.push_back(new Bottle(x,y,40,40));
        LastBlood_time=0;

    }
    LastBlood_time++;

    static int LastMagic_time;
    //srand(time(NULL));
    if(LastMagic_time>=250)
    {

        int x= this->width()+10 ;
        int y = ground_Y-55-rand()%300;
        barrier5.push_back(new Magic(x,y,40,70));
        LastMagic_time=0;

    }
    LastMagic_time++;
    static int LastCircle_time;
    if(LastCircle_time>=190-difficult)
    {

        int x=this->width()+100;
        int y =ground_Y-90-rand()%400;
        barrier6.push_back(new Circle(x,y,90,100));
        LastCircle_time=0;

    }
    LastCircle_time++;



}
void gamewidget::start_game()
{
    r=new role(this);
    r->run_Timer.start();
    remove.start();
    r->hp_Timer.start();
    GameOver=false;
    beforegame=false;
    isRuning=true;
    Coinnum=0;
    isPause=false;
    update();

}
void gamewidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        up=true;
        QSound::play(jump);
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
    else if(event->key()==Qt::Key_A)
    {
        left=true;
    }

    else if(!GameOver&&event->key()==Qt::Key_Escape)
    {
        if(isPause==false)
        {
            r->hp_Timer.stop();
            gamepause();

        }
        else
        {
            r->hp_Timer.start();
            gamecontinue()  ;
        }
    }
    else if(!GameOver && isRuning&&!isPause&&event->key()==Qt::Key_Q)
    {
         r->dashmove_() ;
    }
    else if(GameOver && event->key()==Qt::Key_R)
    {
        start_game();
    }
    else if(GameOver&&event->key()==Qt::Key_B)
    {
        back();
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }
}
void gamewidget::back()
{
    QFile file("save.txt");
                            QTextStream txtInput(&file);
                            QString lineStr;
                            if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
                            {
                                qDebug()<<"Open failed." << endl;
                                return ;
                            }
                            while(!txtInput.atEnd())
                            {
                                lineStr = txtInput.readAll();
                                //if (count==0)
                                maxscore=lineStr.toInt();

                                //count ++ ;
                               // qDebug()<<"12345   " << maxscore ;
                            }
                            file.close();

    beforegame=true;
    //button->init();
    button->move(900,400);//按钮重新回归原位
    button_2->show();
    button_3->show();
    button_4->show();
    update();

}
/**void gamewidget::restart()
{
    GameOver=true;
    isRuning=false;
    delete r;

}
**/
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
    else if(event->key()==Qt::Key_A)
    {
        left=false;
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }
}

void gamewidget::gameIsOver()
{
    QSound::play(over);
    //弹出游戏结算框
    Score=r->getScore();
    //maxscore=0;
    if(Score>maxscore)
    {
        maxscore=Score;
    }
    r->hp_Timer.stop();
    QString str="你的分数："+QString("%1").arg(r->getScore())+'\n'+"你的金币："+QString("%1").arg(Coinnum);

    QMessageBox::about(this,"游戏结束",str);
    QFile file("save.txt");
    QTextStream txtInput(&file);
    QString lineStr;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Open failed." << endl;
        return ;
    }
    while(!txtInput.atEnd())
    {
        lineStr = txtInput.readAll();
        //if (count==0)
        maxscore=lineStr.toInt();

        //count ++ ;
      //  qDebug()<<"12345   " << maxscore ;
    }
    file.close();





    isRuning=false;
    GameOver=true;

    remove.stop();
    barrier.clear();
    barrier2.clear();
    barrier3.clear();
    barrier4.clear();

    r->run_Timer.stop();
    //r->hp_Timer.stop();
    delete r;
    update();
}
