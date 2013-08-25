#include "nodepropertywidget.h"
#include <QGroupBox>
#include <QDebug>
#include <QGridLayout>

NodePropertyWidget::NodePropertyWidget(QWidget *parent) : QWidget(parent)
{
    _groupBox = new QGroupBox(this);
    _groupBox->setTitle("Node Properties");
    // by setting the parent for the QGridLayout to be the groupbox, it is automatically aligned to it
    _groupBoxLayout = new QGridLayout(_groupBox);

}

NodePropertyWidget::~NodePropertyWidget()
{
    delete _groupBox;
}
