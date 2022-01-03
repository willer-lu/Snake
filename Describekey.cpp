#include "Describekey.h"

Describekey::Describekey(QWidget *parent)
	: QWidget(parent)
{

	ui.setupUi(this);
	this->setWindowTitle(QString::fromUtf8("按键说明"));
}

Describekey::~Describekey()
{
}
