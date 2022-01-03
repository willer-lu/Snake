#include "Describegame.h"

Describegame::Describegame(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);
	this->setWindowTitle(QString::fromUtf8("游戏说明"));
}

Describegame::~Describegame()
{
}
