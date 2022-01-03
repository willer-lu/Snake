#include "Snake.h"
#include <stdlib.h>
#include <time.h>

Snake::Snake()
{
    srand((unsigned)time(NULL));
    int snakehead = rand() % 256;
    head_x = snakehead  % 16;
    head_y = snakehead  / 16;//随机出现蛇头
  vector<int> temp_node = { head_x,head_y };
  snake_node.push_back(temp_node);
  // 初始化蛇头结点，蛇长度为1

  srand((unsigned)time(NULL));
  int direct=rand()%4;
  switch(direct){
  case 0: direction = 'R';break;
  case 1: direction = 'D';break;
  case 2: direction = 'L';break;
  case 3: direction = 'U';break;
  default:break;

  }//随机确定蛇头的朝向




  srand((unsigned)time(NULL));
  int site_food = rand() % 255;
   int  i = 0;
  for (; i < 256; i++) {
    if (mapFlag[i] == 1) {
      site_food--;
      if (site_food == -1) break;
    }
  }
  food_x = i % 16;
  food_y = i / 16;
  mapFlag[i] = 2;//随机出现新食物

  score = 0;// 初始化游戏得分


  for (size_t i = 0; i < snake_node.size(); i++)
  {
    int body_site = 16 * snake_node[i][1] + snake_node[i][0];
    mapFlag[body_site] = 0;
  }// 初始化地图标志（墙体是0，与撞到自身情况相同）

}

int Snake::moveSnake()
{

  if (direction == 'U') head_y--;
  else if (direction == 'D') head_y++;
  else if (direction == 'L') head_x--;
  else head_x++; // 根据方向移动蛇头

  int head_site = 16 * head_y + head_x;
  if (head_x < 0 || head_x>15 || head_y < 0 || head_y>15 || mapFlag[head_site] == 0) {
    return 0;
  }// 移动不合法，吃到自己或撞墙


  if (mapFlag[head_site] == 2) {
    mapFlag[head_site] = 0;
    vector<int> temp_node = { head_x,head_y };
    snake_node.push_back(temp_node);//向数组最后添加成员，以下相同
    snake_length++;
    score++;
    return 2;
  }// 若遇见食物，则进行吃食物操作

  // 通过以上两种情况判断，即蛇头移动到空白区域

  int temp_site = snake_node[0][1] * 16 + snake_node[0][0];
  mapFlag[temp_site] = 1;
  mapFlag[head_site] = 0;// 将蛇尾对应标志地图置为1，蛇头置为0

  vector<int> temp_node = { head_x,head_y };
  snake_node.push_back(temp_node);
  snake_node.erase(snake_node.begin());
  return 1;
  // 将蛇头加入数组，并删除蛇尾
}

void Snake::newFood()
{
  // 食物随机刷新机制如下：
  // 标志地图为256大小的数组，地图中空白区域对应数组中的标志为0，蛇身区域为1，食物为2
  // 每次将数组大小256减去蛇身长度，得到余留空白区域的大小，以此大小为范围取随机数
  // 例如随机数取值为4，遍历标志地图数组，找到第4个空白区域，并刷新食物
  srand((unsigned)time(NULL));
  int site_food = rand() % (256 - snake_length);
  int i = 0;
  for (; i < 256; i++) {
    if (mapFlag[i] == 1) {//确保在空白区域刷出食物
      site_food--;
      if (site_food == -1) break;
    }
  }
  food_x = i % 16;
  food_y = i / 16;
  mapFlag[i] = 2;

}
