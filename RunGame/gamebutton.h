#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>
#include <QDebug>
#include<QString>

class GameButton : public QPushButton
{
    Q_OBJECT
private:
    QPixmap img1;
    QPixmap img2;
public:
 //   explicit GameButton(QWidget *parent = nullptr);
    GameButton(QString str,QString str2);  //自定义构造函数
    ~GameButton(); //析构函数
    bool isRun;  //是否开始游戏
    void enterEvent(QEvent *event); //鼠标移入函数
    void leaveEvent(QEvent *event);  //鼠标移出函数
    void mouseReleaseEvent(QMouseEvent *e);  //鼠标点击
    void init();


signals:

public slots:
};

#endif // GAMEBUTTON_H
