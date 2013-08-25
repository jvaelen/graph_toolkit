#ifndef SELECTIONOBSERVERWIDGET_H
#define SELECTIONOBSERVERWIDGET_H

#include <QWidget>

#include "observer/observer.h"

class QGroupBox;
class QGridLayout;
class QLabel;
class QLineEdit;
class SelectAndMoveTool;
class GraphComp;

class SelectionObserverWidget : public QWidget, public Observer
{
    Q_OBJECT
public:
    SelectionObserverWidget(QWidget* parent = 0);
    ~SelectionObserverWidget();
    void notify(Subject *subject);
    bool hasSubject() { return !!_selectionAndMoveTool;}
private slots:
    void updateNodeText(QString newNodeLabel);
private:
    void updateLabels(GraphComp* graphComp);
    void clearLabels();

    // QWidgets that are in this observer
    QGridLayout* _widgetLayout;
    QGroupBox* _groupBox;
    QGridLayout* _groupBoxLayout;
    QLabel* _nodeLabelQLabel;
    QLabel* _positionQLabel;
    QLabel* _coordsLabel;
    QLineEdit* _componentLabelLineEdit;
    SelectAndMoveTool* _selectionAndMoveTool;
    GraphComp* _graphComp;
};

#endif // SELECTIONOBSERVERWIDGET_H
