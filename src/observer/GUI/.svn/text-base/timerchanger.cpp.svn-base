#include "timerchanger.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

TimerChanger::TimerChanger(QWidget *parent) :
    QWidget(parent)
{
    // default value
    _timerVal = 1000/50;
    _widgetLayout = new QGridLayout(this);
    _groupBox = new QGroupBox("Timer Interval" , this);
    _groupBoxLayout = new QGridLayout(_groupBox);
    _updateTimer = new QPushButton("Update", this);
    _intervalField = new QLineEdit(this);
    _intervalField->setFixedWidth(60);
    _widgetLayout->addWidget(_groupBox);
    _groupBoxLayout->addWidget(new QLabel("Interval (msec):"), 0, 0);
    _groupBoxLayout->addWidget(_intervalField,0,1);
    _groupBoxLayout->addWidget(_updateTimer,1,0,2,0);
    connect(this->_updateTimer, SIGNAL(clicked()), this, SLOT(changeTimerVal()));
    this->setLayout(_widgetLayout);

}

void TimerChanger::changeTimerVal()
{
   this->_timerVal = _intervalField->text().toInt();
    if (_intervalField->text().toInt() == 0)
        _intervalField->setText("0");
}
