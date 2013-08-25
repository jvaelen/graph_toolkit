#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <assert.h>
#include <QDebug>
#include "propertyfield.h"

PropertyField::PropertyField(QWidget* parent) : QWidget(parent), Observer()
{
    _widgetLayout = new QHBoxLayout(this);
    _propertyNameLabel = new QLabel("not set", this);
    _propertyValLabel = new QLabel(this);
    _updateButton = new QPushButton("update", this);
    _updateButton->setFixedWidth(60);
    _widgetLayout->addWidget(_propertyNameLabel);
    _widgetLayout->addWidget(_propertyValLabel);
    _widgetLayout->addWidget(_updateButton);
    _property = NULL;
    connect(_updateButton, SIGNAL(clicked()), this, SLOT(fullUpdate()));
}

void PropertyField::notify(Subject *subject)
{
    _property = dynamic_cast<PropertyVisitor*>(subject);
    assert (_property);
    updateView();
}

PropertyField::~PropertyField()
{
    delete _propertyNameLabel;
    delete _propertyValLabel;
    delete _updateButton;
    delete _widgetLayout;
}

void PropertyField::updateView()
{
    assert(_property);
    _propertyNameLabel->setText(QString::fromStdString(_property->getName()) + ":" ) ;
    _propertyValLabel->setText(propertyResultToString(_property->getPropertyResult()));
}

QString PropertyField::propertyResultToString(PropertyVisitor::propertyResult propertyResult) const
{
    switch (propertyResult)
    {
    case PropertyVisitor::FALSEVAL:
        return "false";
    case PropertyVisitor::TRUEVAL:
        return "true";
    case PropertyVisitor::UNDEFINED:
    default:
        return "N/A";
    }
}

void PropertyField::fullUpdate()
{
    // this will call notifyObservers and this will be notified
    _property->visitFocusGraph();
}
