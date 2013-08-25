#include <QGroupBox>
#include <QGridLayout>
#include <vector>
#include <assert.h>
#include <QDebug>
#include <QPushButton>

#include "visitor/propertyvisitorpm.h"
#include "propertyobserver.h"
#include "propertyfield.h"

using namespace std;

PropertyObserver::PropertyObserver(QWidget *parent) : QWidget(parent)
{
    _inited = false;
    _widgetLayout = new QGridLayout(this);
    _groupBox = new QGroupBox("Graph Properties" , this);
    _groupBoxLayout = new QVBoxLayout(_groupBox);
    _updateALL = new QPushButton("Update All", this);
    _widgetLayout->addWidget(_groupBox);
    connect(_updateALL, SIGNAL(clicked()), this ,SLOT(updateAllProperties()));
}

PropertyObserver::~PropertyObserver()
{
    for (QList<PropertyField*>::iterator i = _propertyFields.begin(); i != _propertyFields.end(); ++i)
        delete *i;
    // don't have to clear the list because there are none left
}

void PropertyObserver::initPropertyObserver(const PropertyVisitorPM &propertyVisitorPM)
{
    // if the propertyObserver has already been inited
    if (_inited)
        return ;
    // set inited to true
    _inited = true;
    const vector<PropertyVisitor*>& visitors = propertyVisitorPM.getPropertyVisitors();
    for (unsigned i = 0; i < visitors.size(); ++i)
        createNewPropertyField(visitors[i]);
    _groupBoxLayout->addWidget(_updateALL);
    _groupBoxLayout->addStretch(0);
}

void PropertyObserver::updateAllProperties()
{
    for (QList<PropertyField*>::iterator i = _propertyFields.begin(); i != _propertyFields.end(); ++i)
        (*i)->fullUpdate();
}

void PropertyObserver::createNewPropertyField(PropertyVisitor* propertyVisitor)
{
    _propertyFields.push_back(new PropertyField(this));
    propertyVisitor->registerObserver(_propertyFields.back());
    propertyVisitor->notifyObservers();
    _groupBoxLayout->addWidget(_propertyFields.back());
}
