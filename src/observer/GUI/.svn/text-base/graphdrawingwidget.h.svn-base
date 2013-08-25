/*
 Author: Balazs Nemeth
 Description: This widget is used to create a QGroupBox around the graphdrawingview, nothing more
     */
#ifndef GRAPHDRAWINGWIDGET_H
#define GRAPHDRAWINGWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QGridLayout>
#include <QSlider>
#include <QLabel>

#include "observer/observer.h"
#include "graphdrawingview.h"

class Graph;
class NodePropertyWidget;
class QGraphicsScene;

class GraphDrawingWidget : public QWidget, public Observer
{
    Q_OBJECT
public:
    GraphDrawingWidget(QWidget* parent = NULL);
    void setToolHandler(ToolHandler* toolHandler) { _graphDrawingView->setToolHandler(toolHandler); }
    void setFillColor(const RGB& rgb) {_graphDrawingView->setFillColor(rgb);}
    QGraphicsScene* getScene() {return _graphDrawingView->getScene();}
    ~GraphDrawingWidget();
    // implement the paint function that paints the node
    void notify(Subject *subject);
private slots:
    void updateSceneZoom(int value);
private:
    GraphDrawingView* _graphDrawingView;
    QGridLayout* _mainLayout;
    // this slider is controlled to zoom in on the graph
    QSlider* _zoomSlider;
    QLabel* _zoomLabel;
    /* this graph is being observed and is set after the first notification, also if the notify
        function is called with another graph, the observing graph will be changed, this isn't so important in our case */
    Graph* _graph;
    QLabel _numNodesLabel;
    QLabel _numberOfNodesLabel;
    QLabel _numEdgesLabel;
    QLabel _numberOfEdgesLabel;
};

#endif // GRAPHDRAWINGWIDGET_H
