/*
 Author: Balazs Nemeth
 Description: This widget is inherited from QGraphicsView and sets it's own scene to abstract that for the GraphToolkitWindow
              This widget will use the toolhandler to execute the actions, doing so the graph that has changed will notify it's observers updating their view
     */
#ifndef GRAPHDRAWINGVIEW_H
#define GRAPHDRAWINGVIEW_H

#include <QGraphicsView>
#include "observer/observer.h"
// whenever exceptions are caught, they are displayed in this box
#include "observer/GUI/exceptionmessagebox.h"
// toolhandler is needed to know what to do if the user clicks on the drawing area
#include "tools/toolhandler.h"
// this is the QGraphicsScene that will be viewed
#include "graphdrawingscene.h"

class GraphDrawingView : public QGraphicsView, public Observer
{
public:
    // pass the toolHandler to the scene
    void setToolHandler(ToolHandler* toolHandler) { _toolHandler = toolHandler; _graphDrawingScene->setToolHandler(_toolHandler);}
    void setFillColor(const RGB& rgb) {_graphDrawingScene->setFillColor(rgb);}
    GraphDrawingView(QWidget* parent = 0);
    QGraphicsScene* getScene() {return _graphDrawingScene;}
    // destructor cleans up GUI elements allocated upfront
    ~GraphDrawingView();
    // resizes the sceneRect
    void resizeEvent(QResizeEvent *event);
    void notify(Subject *subject);
protected:
    // whenever the user releases the mouse, we want to update the sceneRect
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
private:
    // help function to resize the view
    void updateSceneRect(QMouseEvent *event);
    ToolHandler* _toolHandler;
    // this is the graph that will be drawn
    Graph* _graph;
    // this is the scene that will be viewed from this graphicsview
    GraphDrawingScene* _graphDrawingScene;
};

#endif // GRAPHDRAWINGVIEW_H
