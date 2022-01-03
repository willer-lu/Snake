#include "mainwindow.h"
#include <qpainter.h>
#include <qtimer.h>
#include <qkeyevent>
#include <qmessagebox.h>

MyWin::MyWin(QWidget *parent)
    : QWidget(parent)//继承基类
{

  QFont font("SongTi", 12);// 字体设置（宋体，12号）

  game_step1 = new QLabel(this);
  game_step1->setFont(font);//以上面的标准设定该标签字体形式，以下类似
  game_step1->setText(QString::fromUtf8("所用步数："));//设定文本内容，以下类似
  game_step1->setGeometry(610, 50, 85, 20);//坐标和大小，以下类似
  game_step1->show();//显示标签，以下类似
  game_step2 = new QLabel(this);
  game_step2->setText(QString::number(step));
  game_step2->setFont(font);
  game_step2->setGeometry(720, 50, 40, 20);
  game_step2->show();

  time1= new QLabel(this);
  time1 ->setFont(font);
  time1 ->setText(QString::fromUtf8("游戏时间："));
  time1->setGeometry(610, 75, 85, 20);
  time1->show();
  time2 = new QLabel(this);
  time2->setText(QString::number(step));
   time2->setFont(font);
   time2->setGeometry(720, 75, 100, 20);
   time2->show();


  QTimer*game_time=new QTimer(this);
  game_time->start(1000);
  connect(game_time,&QTimer::timeout,
          [=]()
  {
 static int second=0;
  second++;

  time2->setText(QString::number(second)+"s");

  }


          );//统计游戏的时间，1秒更新一次


  label_score_1 = new QLabel(this);
  label_score_1->setFont(font);
  label_score_1->setText(QString::fromUtf8("得分："));
  label_score_1->setGeometry(610, 125, 85, 20);
  label_score_1->show();
  label_score_2 = new QLabel(this);
  label_score_2->setText(QString::number(m_snake->score));
  label_score_2->setFont(font);
  label_score_2->setGeometry(720, 125, 40, 20);
  label_score_2->show();// 标签：游戏得分显示



  label_cur_speed_1 = new QLabel(this);
  label_cur_speed_1->setFont(font);
  label_cur_speed_1->setText(QString::fromUtf8("当前速度："));
  label_cur_speed_1->setGeometry(610, 150, 85, 20);
  label_cur_speed_1->show();
  label_cur_speed_2 = new QLabel(this);
  label_cur_speed_2->setFont(font);
  label_cur_speed_2->setText("x" + QString::number(game_speed));
  label_cur_speed_2->setGeometry(720, 150, 40, 20);
  label_cur_speed_2->show();// 标签：游戏当前速度显示


  label_speed = new QLabel(this);
  label_speed->setFont(font);
  label_speed->setText(QString::fromUtf8("速度调节："));
  label_speed->setGeometry(610, 250, 85, 20);
  label_speed->show();// 标签：速度调节显示


  button_speed_sub = new QPushButton(this);
  button_speed_sub->setFocusPolicy(Qt::NoFocus);//类似于居中，以下相同
  button_speed_sub->setText("-");
  button_speed_sub->setGeometry(620, 275, 50, 25);
  button_speed_sub->show(); // 按钮：速度设置，减速按钮

  button_speed_add = new QPushButton(this);
  button_speed_add->setFocusPolicy(Qt::NoFocus);
  button_speed_add->setText("+");
  button_speed_add->setGeometry(700, 275, 50, 25);
  button_speed_add->show();// 加速按钮

  QPalette pe;
  pe.setColor(QPalette::WindowText, Qt::red);
  QFont font_2("HeiTi", 9);
  label_tips = new QLabel(this);
  label_tips->setFont(font_2);
  label_tips->setText("");
  label_tips->setGeometry(620, 200, 150, 15);
  label_tips->setPalette(pe);
  label_tips->show();// 标签：速度上下限提示

  button_game_pause = new QPushButton(this);
  button_game_pause->setFocusPolicy(Qt::NoFocus);
  button_game_pause->setText(QString::fromUtf8("暂停游戏"));
  button_game_pause->setGeometry(640, 360, 80, 30);
  button_game_pause->show();
  // 按钮：游戏暂停


  button_restart = new QPushButton(this);
  button_restart->setFocusPolicy(Qt::NoFocus);
  button_restart->setText(QString::fromUtf8("重新开始"));
  button_restart->setGeometry(640, 410, 80, 30);
  button_restart->show();  // 按钮：重新开始游戏


  button_exit = new QPushButton(this);
  button_exit->setFocusPolicy(Qt::NoFocus);
  button_exit->setText(QString::fromUtf8("退出游戏"));
  button_exit->setGeometry(640, 460, 80, 30);
  button_exit->show(); // 按钮：退出游戏



  timer = new QTimer(this);
  timer->start(1000);//将每次定时器发出的超时信号作为信号函数，以此触发槽函数。
  //在槽函数中，即新的周期开始时，更新绘图事件，按照新周期当前snake_node结点坐标和食物坐标重新绘制蛇与食物，
  //这样便可以达到蛇在移动的视觉效果；同时需要更新界面上游戏得分标签子控件。


  (void)connect(button_speed_sub, &QPushButton::clicked, [=]() {// 按钮事件：减速按钮
    if (game_speed > 1)//判断是否为最低速度
    {
      label_tips->setText("");
      game_speed = game_speed / 2;//速度变成原来的一半
      label_cur_speed_2->setText("x" + QString::number(game_speed));//改变显示的速度
      timer->start(1000 / game_speed);//触发频率改变
      if (pause_flag == 1) timer->stop();
    }
    else
    {
      label_tips->setText(QString::fromUtf8("* 已达到最低速度."));
    }
    });

  (void)connect(button_speed_add, &QPushButton::clicked, [=]() {// 按钮事件：加速按钮
    if (game_speed < 8)//判断是否为最高速度
    {
      label_tips->setText("");
      game_speed = game_speed * 2;
      label_cur_speed_2->setText("x" + QString::number(game_speed));
      timer->start(1000 / game_speed);
      if (pause_flag == 1) timer->stop();
    }
    else
    {
      label_tips->setText(QString::fromUtf8("* 已达到最高速度."));
    }
    });


  (void)connect(button_game_pause, &QPushButton::clicked, [=]() {
    // 根据暂停标志得知当前游戏状态
    // 从而切换该按钮的状态
      //0为正在进行，1为暂停状态
    switch (pause_flag)
    {
    case 0:
      timer->stop();
      pause_flag = 1;
      button_game_pause->setText(QString::fromUtf8("继续游戏"));
      break;
    case 1:
      timer->start(1000 / game_speed);
      pause_flag = 0;
      button_game_pause->setText(QString::fromUtf8("暂停游戏"));
      break;
    default:
      break;
    }
    }); // 游戏暂停按钮响应事件


  (void)connect(button_restart, &QPushButton::clicked, [=]() {// 重新开始按钮响应事件
    m_snake = new Snake;
    game_speed = 1;
    pause_flag = 0;

    step_count = 1;
    step_key_input = 0;

    label_cur_speed_2->setText("x" + QString::number(game_speed));
    label_score_2->setText(QString::number(m_snake->score));
    step=0;
    game_step2->setText(QString::number(step));

    button_game_pause->setText(QString::fromUtf8("暂停游戏"));//更新各按钮状态
    update();
    timer->start(1000 / game_speed);
    });


  (void)connect(button_exit, &QPushButton::clicked, [=]() {
    this->close();
    }); // 退出游戏


  (void)connect(timer, &QTimer::timeout, [=](){ // 定时器控制周期刷新
      // 周期结束时，定时器发出超时信号，执行相应操作
    step_count++;
    if (step_count == INT_MAX - 10) step_count = 1;//防止溢出

    int flag = m_snake->moveSnake();// 每次周期结束后执行蛇移动函数

    label_score_2->setText(QString::number(m_snake->score));// 刷新得分标签

    switch (flag) // 根据移动函数返回值执行不同操作
    {
    case 0:
    {
          // 0表示吃到了自己或撞墙
          timer->stop();

           int ret=QMessageBox::question(this,"游戏结束","是否重新开始？");



           switch(ret){
           case QMessageBox::Yes:{ m_snake = new Snake;
               game_speed = 1;
               pause_flag = 0;

               step_count = 1;
               step_key_input = 0;

               label_cur_speed_2->setText("x" + QString::number(game_speed));
               label_score_2->setText(QString::number(m_snake->score));
               step=0;
               game_step2->setText(QString::number(step));
               pause_flag = 0;
               button_game_pause->setText(QString::fromUtf8("暂停游戏"));
               update();
               timer->start(1000 / game_speed);break;}
              case QMessageBox::No: this->close();break;}





          break;}


    case 1:
      // 1表示蛇头移动到空白区域
      update();//重绘，以下相同
      break;

    case 2:
      // 2表示吃到了食物
      m_snake->newFood();
      update();
      break;

    default:
      break;
    }
  });

}


void MyWin::keyPressEvent(QKeyEvent* event)// 键盘监听事件
{
  if (step_key_input != step_count)
  {
    switch (event->key())
    {
    case Qt::Key_Up://进行改变方向操作并判断输入是否有效
    case 'w':
    case 'W':
      if (m_snake->direction == 'D') break;
      m_snake->direction = 'U';
      step++;game_step2->setText(QString::number(step));
      step_key_input = step_count;
      break;
    case Qt::Key_Down:
    case 's':
    case 'S':
      if (m_snake->direction == 'U') break;
      m_snake->direction = 'D';
     step++;game_step2->setText(QString::number(step));
      step_key_input = step_count;
      break;
    case Qt::Key_Left:
    case 'a':
    case 'A':
      if (m_snake->direction == 'R') break;
      m_snake->direction = 'L';
      step++;game_step2->setText(QString::number(step));
      step_key_input = step_count;
      break;
    case Qt::Key_Right:
    case 'd':
    case 'D':
      if (m_snake->direction == 'L') break;
      m_snake->direction = 'R';
      step++;game_step2->setText(QString::number(step));
      step_key_input = step_count;
      break;

    default:
      break;
    }
  }
}

// 绘画事件
void MyWin::paintEvent(QPaintEvent*)
{

  QPainter painterMap(this);
  painterMap.setPen(Qt::lightGray);
  painterMap.setBrush(Qt::lightGray);// 绘制浅灰色背景

  int x = this->width();
  int y = this->height();
  painterMap.drawRect(QRect(x * mapLeftTopZoom, y * mapLeftTopZoom, y * mapSizeZoom, y * mapSizeZoom));//地图大小


  QPainter painterSnakeBody(this);
  painterSnakeBody.setPen(Qt::black);
  painterSnakeBody.setBrush(Qt::black);
  painterSnakeBody.setRenderHint(QPainter::Antialiasing);//使绘制时边缘平滑
  int i = 0;
  for (; i < m_snake->snake_node.size()-1; i++)
  {
    int site_x = begin_x + m_snake->snake_node[i][0] * single_size;
    int site_y = begin_y + m_snake->snake_node[i][1] * single_size;//计算出左上角的坐标
    painterSnakeBody.drawRoundedRect(site_x, site_y, single_size, single_size, 10, 10);
  }// 绘制蛇身
//前两个参数为矩形左上角坐标，中间两个参数为单格的像素长度，最后两个参数为矩形圆角的弯曲程度

  QPainter painterSnakeHead(this);
  painterSnakeHead.setPen(Qt::red);
  painterSnakeHead.setBrush(Qt::red);
  painterSnakeHead.setRenderHint(QPainter::Antialiasing);
  int site_x = begin_x + m_snake->snake_node[i][0] * single_size;
  int site_y = begin_y + m_snake->snake_node[i][1] * single_size;
  painterSnakeHead.drawRoundedRect(site_x + 2, site_y + 2, single_size - 4, single_size - 4, 10, 10); // 绘制蛇头


  QPainter painterSnakeEye(this);
  painterSnakeEye.setPen(Qt::white);
  painterSnakeEye.setBrush(Qt::white);
  painterSnakeEye.setRenderHint(QPainter::Antialiasing);// 绘制眼睛

  if (m_snake->direction == 'U') {// 根据蛇头的不同朝向，分情况绘制眼睛
    painterSnakeEye.drawEllipse(site_x + 7, site_y + 7, 6, 6);
    painterSnakeEye.drawEllipse(site_x + 17, site_y + 7, 6, 6);
  }
  else if (m_snake->direction == 'D') {
    painterSnakeEye.drawEllipse(site_x + 7, site_y + 17, 6, 6);
    painterSnakeEye.drawEllipse(site_x + 17, site_y + 17, 6, 6);
  }
  else if (m_snake->direction == 'L') {
    painterSnakeEye.drawEllipse(site_x + 7, site_y + 7, 6, 6);
    painterSnakeEye.drawEllipse(site_x + 7, site_y + 17, 6, 6);
  }
  else {
    painterSnakeEye.drawEllipse(site_x + 17, site_y + 7, 6, 6);
    painterSnakeEye.drawEllipse(site_x + 17, site_y + 17, 6, 6);
  }

  QPainter painterFood(this);
  painterFood.setPen(Qt::green);// 绘制食物
  painterFood.setBrush(Qt::green);
  painterFood.setRenderHint(QPainter::Antialiasing);
  site_x= begin_x + m_snake->food_x * single_size;
  site_y= begin_y + m_snake->food_y * single_size;
  painterFood.drawRoundedRect(site_x + 2, site_y + 2, single_size - 4, single_size - 4, 10, 10);

}


MyWin::~MyWin()//析构函数
{
}
