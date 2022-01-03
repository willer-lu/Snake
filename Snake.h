#pragma once

#include <iostream>
#include <vector>
#include <conio.h>//通过控制台进行输入输出


using namespace std;

class Snake//贪吃蛇类
{
public:

  Snake();// 构造函数

  vector<vector<int>> snake_node; // 蛇身结点（类似于坐标），左上角为[0，0]，16×16的地图

  char direction;// 蛇当前朝向，'U'=up,'D'=down,'L'=left,'R'=right

  int head_x;
  int head_y; // 蛇头坐标

  int food_x;
  int food_y; // 食物坐标

  int score;// 游戏得分



  vector<int> mapFlag{ vector<int>(256,1) };//定义一个二维数组mapFlag，大小为16x16，与地图相对应。遍历数组，将Snake身体所处的结点标为 0，当蛇头移动至被标记为 0 的结点，即吃到自己身体，游戏结束。

      //同时，将食物结点标为2，当蛇头移动至标为 2 的结点时，即吃到食物。
  int snake_length = 1;//蛇的初始长度


  void newFood();// 生成新的食物

  int moveSnake();// 移动蛇

};
