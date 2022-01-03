#include "begin.h"

Begin::Begin(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromUtf8("贪吃蛇"));
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(begingame()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(descgame()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(desckey()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(close()));
}

Begin::~Begin()
{
}
void Begin::begingame()
{
	this->close();//关闭欢迎界面
    MyWin *w = new MyWin();//打开程序界面
    w->resize(800,600);
    w->show();

}
//游戏说明
void Begin::descgame()
{
	Describegame* w = new Describegame();//打开程序界面
	w->show();

}
//按键说明
void Begin::desckey()
{
	Describekey* w = new Describekey();//打开程序界面
	w->show();
}
