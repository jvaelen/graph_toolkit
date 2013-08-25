#ifndef NODEPROPERTYWIDGET_H
#define NODEPROPERTYWIDGET_H

#include <QWidget>

class QGroupBox;
class QGridLayout;

class NodePropertyWidget : public QWidget
{
public:
    NodePropertyWidget(QWidget* parent = 0);
    ~NodePropertyWidget();
private:

    QGroupBox* _groupBox;
    QGridLayout* _groupBoxLayout;

};

#endif // NODEPROPERTYWIDGET_H
