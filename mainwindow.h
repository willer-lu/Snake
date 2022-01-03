#pragma once

#include "Snake.h"
#include <QWidget>//窗口
#include <qpainter.h>//绘图
#include <iostream>
#include <qpushbutton.h>//按钮
#include <qlabel.h>//标签
#include <qdebug.h>//打印
#include <QTimer>//计时


class MyWin : public QWidget//继承基类
{
  Q_OBJECT//宏 信号和槽机制

public:
  MyWin(QWidget* parent = Q_NULLPTR);//构造函数
  ~MyWin();//析构函数

  Snake* m_snake = new Snake;//开辟动态空间，类的指针
  void paintEvent(QPaintEvent*);//绘图
  void keyPressEvent(QKeyEvent* event);//获取键盘操作
  QTimer* timer;//定时器

private:

  double mapLeftTopZoom = 0.1;
  double mapSizeZoom = 0.8;// 地图按整体窗口缩小比例

  int begin_x = 80;
  int begin_y = 60;// 窗口中地图左上角坐标（起点）

  int single_size = 30; // 单格尺寸，一个格子的像素
  int step=0;//游戏步数
  int game_speed = 1;// 游戏速度

  QLabel* label_score_1;
  QLabel* label_score_2;//显示分数的标签
  QLabel* label_cur_speed_1;
  QLabel* label_cur_speed_2;//显示速度的标签
  QLabel* label_speed;//标签 显示速度限制

  QPushButton* button_speed_add;
  QPushButton* button_speed_sub; // 按钮：调节速度

  QLabel* label_tips;// 标签：速度上下限提示

  QLabel*game_step1;
  QLabel*game_step2;//标签：所用步数

  QLabel*time1;
  QLabel*time2;//显示游戏进行时间



  QPushButton* button_game_pause;// 按钮：暂停游戏/继续游戏

  int pause_flag = 0; // 暂停按钮标志(0：表示游戏正在运行 1: 表示游戏正在暂停)


  QPushButton* button_restart;// 按钮：重新开始游戏

  QPushButton* button_exit;// 按钮：退出游戏

QTimer*game_time;//计量游戏时间

  int step_count = 1;
  int step_key_input = 0;//每个周期加个标志，即定义int step_count = 1；
  //比如定时器第一次循环的时候，step_count的值为 1，可以认为当前周期叫做 ’ 1 ’ 周期，
  //第二次循环的时候，step_count的值加 1，所以第二周期可以叫做 ’ 2 ’ 周期，以此类推，每周期开始时将step_count的值加 1，表示为该周期的标识；

  //标志位step_key_input，当键盘输入时，将当前周期的标识赋值给step_key_input，下次键盘输入时，判断step_key_input是否等于step_count，
  //如果等于说明在这个周期内，已经有过一个合法输入了，本次操作不执行。


};
