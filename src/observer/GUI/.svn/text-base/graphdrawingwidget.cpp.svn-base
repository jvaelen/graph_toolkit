#include "graphdrawingwidget.h"
#include "graph/graph.h"
#include <QLabel>
#include <cmath>

// the graph can be zoomed with this factoc
#define MAXZOOMFACTOR 1000

GraphDrawingWidget::GraphDrawingWidget(QWidget *parent) : QWidget(parent)
{
    _numNodesLabel.setText("Number Of Nodes: ");
    _numEdgesLabel.setText("Number Of Edges: ");
    // start by initializing all the pointers, by setting the parent for layouts, the parent->setLayout() function is implicitly called
    _mainLayout = new QGridLayout(this);
    _graphDrawingView = new GraphDrawingView(this);
    _zoomLabel = new QLabel("Zoom Graph: ", this);
    _zoomSlider = new QSlider(Qt::Horizontal, this);
    _mainLayout->addWidget(_graphDrawingView, 0, 0, 1, 6);
    // add the zoomslider under the graph
    _mainLayout->addWidget(_zoomLabel, 1, 0);
    _mainLayout->addWidget(_zoomSlider, 1, 1);
    // add labels that tell the user how many edges and labels there are in the graph
    _mainLayout->addWidget(&_numNodesLabel, 1, 2);
    _mainLayout->addWidget(&_numberOfNodesLabel, 1, 3);
    _mainLayout->addWidget(&_numEdgesLabel, 1, 4);
    _mainLayout->addWidget(&_numberOfEdgesLabel, 1, 5);
    _mainLayout->setColumnMinimumWidth(2, 100);
    _mainLayout->setColumnMinimumWidth(3, 50);
    _mainLayout->setColumnMinimumWidth(4, 100);
    _mainLayout->setColumnMinimumWidth(5, 50);
    // at the beginning no graph is being observed
    _graph = NULL;
    connect(_zoomSlider, SIGNAL(sliderMoved(int)), this, SLOT(updateSceneZoom(int)));
    connect(_zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(updateSceneZoom(int)));

    _zoomSlider->setValue(1);
}

GraphDrawingWidget::~GraphDrawingWidget()
{
    // clean up everything that has been alocated in the constructor
    delete _zoomLabel;
    delete _zoomSlider;
    delete _graphDrawingView;
    delete _mainLayout;
}

void GraphDrawingWidget::updateSceneZoom(int value)
{

    _graphDrawingView->resetTransform();
    if (value != 0)
        _graphDrawingView->scale(1/(double)value,1/(double)value);
    else
        _graphDrawingView->scale(1.5,1.5);
    _graphDrawingView->scene()->update(_graphDrawingView->sceneRect());
}

void GraphDrawingWidget::notify(Subject *subject)
{
    // set the new _graph
    _graph = (Graph*)subject;
    _graphDrawingView->notify(_graph);
    _numberOfNodesLabel.setText(QString::number(_graph->getNumberOfNodes()));
    _numberOfEdgesLabel.setText(QString::number(_graph->getNumberOfEdges()));
}
