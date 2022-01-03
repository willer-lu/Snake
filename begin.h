#pragma once

#include <QWidget>
#include "ui_begin.h"
#include "mainwindow.h"
#include"Describegame.h"
#include"Describekey.h"
class Begin : public QWidget
{
	Q_OBJECT

public:
	Begin(QWidget *parent = Q_NULLPTR);
	~Begin();
private slots:
	void begingame();
	void descgame();
	void desckey();
private:
	Ui::begin ui;
};
//开始界面
