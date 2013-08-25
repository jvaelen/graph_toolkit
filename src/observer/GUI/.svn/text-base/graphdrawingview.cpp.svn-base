#include <QMouseEvent>
#include <assert.h>

#include "graphdrawingview.h"
#include "graph/graphComp/node.h"
#include "tools/toolparameters.h"
#include <QPainter>

GraphDrawingView::GraphDrawingView(QWidget* parent) : QGraphicsView(parent)
{
    setRenderHints(QPainter::Antialiasing);
    _graph = NULL;
    _toolHandler = NULL;
    // set this as the parent for the QGraphicsScene
    _graphDrawingScene = new GraphDrawingScene(this);
    setScene(_graphDrawingScene);
    centerOn(0,0);
}

GraphDrawingView::~GraphDrawingView()
{
    delete _graphDrawingScene;
}

void GraphDrawingView::mouseReleaseEvent(QMouseEvent *event)
{
    try
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
    catch(BaseEx& ex)
    {
        ExceptionMessageBox(ex, this);
    }
}

void GraphDrawingView::mousePressEvent(QMouseEvent *event)
{
    try
    {
        QGraphicsView::mousePressEvent(event);
    }
    catch(BaseEx& ex)
    {
        ExceptionMessageBox(ex, this);
    }
}

void GraphDrawingView::mouseMoveEvent(QMouseEvent *event)
{
    try
    {
        QGraphicsView::mouseMoveEvent(event);
    }
    catch(BaseEx& ex)
    {
        ExceptionMessageBox(ex, this);
    }
}

void GraphDrawingView::notify(Subject *subject)
{
    if (!_graph) // if this is the first time that we notify the view, we want to center on 0,0
        centerOn(0,0);
    _graph = (Graph*)subject;
    // first we wan't to all the node observers
    _graphDrawingScene->notify(subject);
    //setSceneRect(_graphDrawingScene->sceneRect());
}

void GraphDrawingView::resizeEvent(QResizeEvent *event)
{
    // if the view has resized, we want the scene to also resize
    QGraphicsView::resizeEvent(event);
    // if the sceneRectangle is to small, we set it to have the size of the view
    if (width()*height() > _graphDrawingScene->sceneRect().width() *  _graphDrawingScene->sceneRect().height())
    {
        _graphDrawingScene->setSceneRect(width()/-2 - 150, height()/-2 -150, width() + 150, height() + 150);
        setSceneRect(_graphDrawingScene->sceneRect());
    }
}
