/*
 Author: Balazs Nemeth
 Description: for each property one of these fields is used to show the name, value and an update button for the property
     */

#ifndef PROPERTYFIELD_H
#define PROPERTYFIELD_H

#include <QWidget>
#include <QString>

#include "observer/observer.h"
#include "visitor/propertyvisitor.h"

class QLabel;
class QPushButton;
class QHBoxLayout;

class PropertyField : public QWidget, public Observer
{
    Q_OBJECT
public:
    // constructor for the propertyfield
    PropertyField(QWidget* parent = 0);
    // clear the widget
    ~PropertyField();
    // notify the propertyfield observer that will update the propertyvaluelabel
    void notify(Subject *subject);

public slots:
    // is called by notify and if the user clicks update all then it is called by that from
    void fullUpdate();
private slots:
    void updateView();
private: // helpfunctions
    QString propertyResultToString(PropertyVisitor::propertyResult propertyResult) const;
private:
    QLabel* _propertyNameLabel;
    QLabel* _propertyValLabel;
    QPushButton* _updateButton;
    QHBoxLayout* _widgetLayout;
    PropertyVisitor* _property;
};

#endif // PROPERTYFIELD_H
