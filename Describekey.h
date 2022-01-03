#pragma once

#include <QWidget>
#include "ui_Describekey.h"

class Describekey : public QWidget
{
	Q_OBJECT

public:
	Describekey(QWidget *parent = Q_NULLPTR);
	~Describekey();

private:
	Ui::Describekey ui;
};
//按键说明
