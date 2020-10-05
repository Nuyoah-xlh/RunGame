#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
//#include"role.h"
#include<QTimer>
//#include<QVector>
#include<vector>
#include"barriers.h"

class role;
class gamewidget : public QWidget
{
    Q_OBJECT
private:

    QPixmap background[3];  //游戏地图
    QPixmap before_start;   //开始前页面
    QPixmap ground;       //地面
    role *r=NULL;
public:
    explicit gamewidget(QWidget *parent = nullptr,int wid=1280,int heig=720);
    std::vector<Wall *> barrier;  //放障碍物的容器
    double backImgX[3]={0,200,0}; //图片水平移动参数
    double imgSpeed[3]={0.15,1,0.5};  //移动速度参数
    double ground_X;  //X点
    double ground_speed;   //地面移动参数
    int ground_Y;  //地面起点y值
    bool isRuning;  //是否游戏中
    bool isPause;  //是否暂停
    bool up;  //向上
    bool down;   //向下
    bool right;   //向右
    bool esc;    //暂停
    QTimer remove;
    void paintEvent(QPaintEvent *event);  //绘图
    void start_game(); //开始游戏
    void keyPressEvent(QKeyEvent *event);  //键盘按下事件
    void keyReleaseEvent(QKeyEvent *event);  //键盘释放事件
    void addBarriers();   //增加障碍物



signals:

public slots:
};

#endif // GAMEWIDGET_H
