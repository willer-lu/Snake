#pragma once

#include <QWidget>
#include "ui_Describegame.h"

class Describegame : public QWidget
{
	Q_OBJECT

public:
	Describegame(QWidget *parent = Q_NULLPTR);
	~Describegame();

private:
	Ui::Describegame ui;
};
//游戏说明
