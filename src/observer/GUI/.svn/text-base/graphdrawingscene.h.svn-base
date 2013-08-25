/*
 Author: Balazs Nemeth
 Description: This is the scene where a graph is displayed to the user
     */

#ifndef GRAPHDRAWINGSCENE_H
#define GRAPHDRAWINGSCENE_H

#include <QGraphicsScene>
#include <QDebug>

#include "tools/toolhandler.h"

#include "observer/observer.h"
#include "observer/GUI/graphicsnode.h"
#include "observer/GUI/graphicsedge.h"
#include <QGraphicsItem>
#include <QMap>

class Graph;
class Point;
class NodePropertyWidget;
enum ObserverTypes {NODEOBSERVER = QGraphicsItem::UserType + 1, EDGEOBSERVER = QGraphicsItem::UserType + 2};

class GraphDrawingScene : public QGraphicsScene, public Observer
{
public:
    GraphDrawingScene(QObject* parent = 0);
    ~GraphDrawingScene();
    // overriden to implement mousepressevent
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void notify(Subject *subject);
    // exapnds the scenerectangle around the given position
    void expandSceneRect(const QPoint& position);
    // for convenience, calls the expandSceneRect with a QPoint created from the Point paramter
    void expandSceneRect(const Point& position);
    // the next 3 functions make it possible to draw one dummy edge, this is to show the user the edge while he is creating it
    void startDummyEdge(const QPoint& from);
    void drawDummyEdge(const QPoint& from, const QPoint& to);
    void stopDummyEdge();
    // saves the _toolHandler so that the scene knows if it recieves a mouse event, what to do
    void setToolHandler(ToolHandler* toolHandler) {_toolHandler = toolHandler;}
    // all the edges and nodes will be deleted at the next notify of the object
    void deleteMeAtNextUpdate(GraphicsNode* me);
    void deleteMeAtNextUpdate(GraphicsEdge* me);
    // sets a pen for a collection of edges
    void setDeleteStyleEdges(Node* node);
    void setNormalStyleEdges(Node* node);
    // calling this function will discard any cashed edges of any node
    void uncashEdges() {_cachedNode = NULL;}
    // calls updateEdges with the outgoing en incomming edges
    void updateEdgesOfNode(Node* node);
    // the following 3 functions are used to control the selected
    GraphicsNode* getSelectedNode() const { return _selectedGraphicsNode;}
    void setFillColor(const RGB& rgb);
    // can be called if a node's observer changes to keep the _nodeObservers and _edgeObservers up to date
    void removeFromMap(Node* node);
    void removeFromMap(Edge* edge);
    void addToMap(Node* node, GraphicsNode* graphicsNode);
    void addToMap(Edge* edge, GraphicsEdge* graphicsEdge);
private:
    // sends a notify to all the observers of the edges
    void updateEdges(const QList<Edge*>& edges);
    // caches, if needed, the outgoing AND incomming edges for the node given by the parameter
    void cacheEdgesForNode(Node* node);
    // helpfunctions
    void addNewNodes(const list<Node*>& newNodes);
    void addNewEdges(const list<Edge*>& newEdges);
    void deleteOldNodes();
    void deleteOldEdges();
    // returns the top most node clicked if there is one, else it returns NULL
    QGraphicsItem* getTopItemClicked(QList<QGraphicsItem*> itemList, int type);
    // filters a list of QGraphicItems to only contain nodeobservers
    QList<QGraphicsItem *> filterForType(QList<QGraphicsItem *>& itemList, int type);
    // when the user is dragging to create an edge, this is displayed
    GraphicsEdge* _dummyEdge;
    GraphicsNode* _dummyNode;
    ToolHandler* _toolHandler;
    // this is the graph that is being observed
    Graph* _graph;
    // keep track of all the observers created so far, for efficiency, we do this in a map so we can quickly convert any node/edge to it's observer
    QMap<Node*, GraphicsNode*> _nodeObservers;
    QMap<Edge*, GraphicsEdge*> _edgeObservers;
    QList<GraphicsNode*> _nodeObserversToRemove;
    QList<GraphicsEdge*> _edgeObserversToRemove;
    QList<Edge*> _cachedEdges;
    Node* _cachedNode;
    // this node is being dragged
    GraphicsNode* _draggingGraphicsNode;
    // this node was last selected
    GraphicsNode* _selectedGraphicsNode;
    // this is used to collect parameters for the tools;
    ToolParameters _toolParameters;
    RGB _fillColor;
    /* a pointer to the node property widget is
       kept here so that it can be efficiently notified about the node that needs to be displayed */
};

#endif // GRAPHDRAWINGSCENE_H
