#include "graphdrawingscene.h"
#include "graph/graph.h"
#include "graphicsnode.h"
#include "graph/graphComp/node.h"
#include "observer/GUI/graphdrawingview.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsBlurEffect>
#include <QRect>
#include <QPen>
#include <assert.h>

GraphDrawingScene::GraphDrawingScene(QObject *parent) : QGraphicsScene(parent)
{
    // delegates the parent parameter to the baseclass using the init list
    _graph                = NULL;
    _toolHandler          = NULL;
    _dummyNode            = NULL;
    _draggingGraphicsNode = NULL;
    _selectedGraphicsNode = NULL;
    _cachedNode           = NULL;
    _dummyEdge = new GraphicsEdge(NULL, this);
    _dummyEdge->setVisible(false);
}

GraphDrawingScene::~GraphDrawingScene()
{
    // delete all the observers
    for (QMap<Edge*, GraphicsEdge*>::iterator i = _edgeObservers.begin();i != _edgeObservers.end() ;++i)
        delete i.value();
    for (QMap<Node*, GraphicsNode*>::iterator i = _nodeObservers.begin();i != _nodeObservers.end() ;++i)
        delete i.value();
}

void GraphDrawingScene::startDummyEdge(const QPoint& from)
{
    _dummyEdge->setZValue(-2); // edges are always behind nodes, -1 is for edges that are selected
    _dummyEdge->setLine(from.x(), from.y(), from.x(), from.y());
    _dummyEdge->forceCalcArrow();
    _dummyEdge->setVisible(true);
    update(_dummyEdge->boundingRect());
}

void GraphDrawingScene::drawDummyEdge(const QPoint& from, const QPoint& to)
{
    // in this case we wan't to check if the _dummyEdge is allocated, it may be possible, that due to an exception we end up in this function
    if(!_dummyEdge->isVisible())
        return ;

    _dummyEdge->setLine(from.x(), from.y(), to.x(), to.y());
    _dummyEdge->forceCalcArrow();
}

void GraphDrawingScene::stopDummyEdge()
{
    // remove it from the scene
    _dummyEdge->hide();
}

void GraphDrawingScene::setFillColor(const RGB &rgb)
{
    _fillColor = rgb;
    for(QMap<Node*, GraphicsNode*>::iterator i =_nodeObservers.begin();i != _nodeObservers.end(); ++i)
        i.value()->setFillColor(_fillColor);
}

void GraphDrawingScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return ;
    assert(_toolHandler);
    GraphicsNode* tempNode;
    QList<QGraphicsItem*> itemsUnderCursor = items(event->scenePos());
    switch(_toolHandler->getToolType())
    {
    case ADDNODETOOL:
        _dummyNode = new GraphicsNode(NULL, this, 27);
        _dummyNode->setPos(event->scenePos().toPoint());
        _dummyNode->setOpacity(.50);
        break;
    case ADDEDGETOOL:
        // get the topmost GraphicsNode* under the cursor from the list of all items under the cursor
        tempNode = dynamic_cast<GraphicsNode*>(getTopItemClicked(items(event->scenePos()), GraphicsNode::NODEOBSERVER));
        if (tempNode) // if there are nodes under the cursor
        {
            _toolParameters.setSource(tempNode->getNode());
            startDummyEdge(QPoint(tempNode->getNode()->getCoords().getX(), tempNode->getNode()->getCoords().getY()));
        }
        break;
    case SELECTTOOL:
        // set the dragging graphics node, if it has been set, also set it as the selected node
        _draggingGraphicsNode = dynamic_cast<GraphicsNode*>(getTopItemClicked(itemsUnderCursor, GraphicsNode::NODEOBSERVER));
        if (_draggingGraphicsNode)
        {
            // if a node was selected, we set it
            _toolParameters.setSource(_draggingGraphicsNode->getNode());
            _toolParameters.setRGB(RGB::colorSelection());
        }
        else
        {
            GraphicsEdge* tempEdge = dynamic_cast<GraphicsEdge*>(getTopItemClicked(itemsUnderCursor, GraphicsEdge::EDGEOBSERVER));
            if (tempEdge)
            {
                _toolParameters.setEdge(tempEdge->getEdge());
                _toolParameters.setRGB(RGB::colorSelection());
            }
        }
            // it may be possible that the user clicked white space, in this case the selectedNode is set to NULL (basicly deselecting what was already selected)
            // if we didn't set any node, a deselection will occur
        _toolHandler->execute(_toolParameters);
        _toolParameters.reset();
        break;
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(event);
}

void GraphDrawingScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return ;
    // first stop the dummyEdge
    stopDummyEdge();
    // then handle everything that needs to be done
    QGraphicsScene::mouseReleaseEvent(event);
    assert(_toolHandler);
    GraphicsNode* tempNode;
    GraphicsEdge* tempEdge;
    switch(_toolHandler->getToolType())
    {
    case ADDNODETOOL:
        removeItem(_dummyNode);
        delete _dummyNode;
        _dummyNode = NULL;
        // create a node that holds the next logical name and with the position where the user clicked
        _toolParameters.setNode(Node(_graph->getNodeNameHint(), Point(event->scenePos().x(), event->scenePos().y())));
        _toolHandler->execute(_toolParameters);
        _toolParameters.reset();
        break;
    case ADDEDGETOOL:
        if (_toolParameters.getSource()) // if the source for the new edge has been set (meaning we started dragging from another node)
        {
            tempNode = dynamic_cast<GraphicsNode*>(getTopItemClicked(items(event->scenePos()), GraphicsNode::NODEOBSERVER));
            if (tempNode) // if there are nodes under the cursor
            {
                assert(tempNode->getNode());
                // get the first node (the one that is visible to the user and set that as the sourcenode)
                _toolParameters.setTarget(tempNode->getNode());
                _toolHandler->execute(_toolParameters);
            }
        }
        // finally reset the toolparameters (this will prevent any other mouseMoveEvent updates)
        _toolParameters.reset();
        break;
    case REMOVENODETOOL:
        tempNode = dynamic_cast<GraphicsNode*>(getTopItemClicked(items(event->scenePos()), GraphicsNode::NODEOBSERVER));
        if (tempNode) // if there are nodes under the cursor
        {
            // get the first node (the one that is visible to the user and set that as the sourcenode)
            _toolParameters.setSource(tempNode->getNode());
            _toolHandler->execute(_toolParameters);
            _toolParameters.reset();
        }
        break;
    case REMOVEEDGETOOL:
        tempEdge = dynamic_cast<GraphicsEdge*>(getTopItemClicked(items(event->scenePos()), GraphicsEdge::EDGEOBSERVER));
        if (tempEdge)
        {
            _toolParameters.setSource(tempEdge->getEdge()->getSource());
            _toolParameters.setTarget(tempEdge->getEdge()->getTarget());
            _toolParameters.setLabel(tempEdge->getEdge()->getLabel());
            _toolHandler->execute(_toolParameters);
            _toolParameters.reset();
        }
        break;
    case SELECTTOOL:
        if (_draggingGraphicsNode)
            expandSceneRect(_draggingGraphicsNode->getNode()->getCoords());
        _draggingGraphicsNode = NULL;
        break;
    }
}

void GraphDrawingScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    assert(_toolHandler);
    switch(_toolHandler->getToolType())
    {
    case ADDNODETOOL:
        if (_dummyNode)
            _dummyNode->setPos(event->scenePos());
        break;
    case ADDEDGETOOL:
        if (_toolParameters.getSource()) // if we started dragging from a source node
            drawDummyEdge(QPoint(_toolParameters.getSource()->getCoords().getX(),
                                       _toolParameters.getSource()->getCoords().getY()),
                                QPoint(event->scenePos().x(),
                                       event->scenePos().y()));
        break;
    case SELECTTOOL:
        // if _draggingGraphicsNode is set, in other words, if we are dragging a node
        if (_draggingGraphicsNode)
        {
            // update the position of the node that is being dragged
            _draggingGraphicsNode->updatePosition(Point(event->scenePos().x(), event->scenePos().y()));
            updateEdgesOfNode(_draggingGraphicsNode->getNode());
        }
        break;
    default: // addNode doesn't need to do anything
        ;
    }
}

QGraphicsItem* GraphDrawingScene::getTopItemClicked(QList<QGraphicsItem*> itemList, int type)
{
    // filter for nodes
    itemList = filterForType(itemList, type);
    if(itemList.empty())
        return NULL;
    else
        return dynamic_cast<QGraphicsItem*>(itemList.first());
}

void GraphDrawingScene::notify(Subject *subject)
{
    _graph = (Graph*)subject;
    // get the last added nodes, only these nodes have to be linked with observers
    addNewNodes(_graph->getLastAddedNodes());
    // add all the new edges and link these with observers
    addNewEdges(_graph->getLastAddedEdges());
    // remove old nodes and edges
    deleteOldNodes();
    deleteOldEdges();
    _cachedNode = NULL;
}
void GraphDrawingScene::addNewNodes(const list<Node*>& newNodes)
{
    if (newNodes.empty())
        return ;
    GraphicsNode* newGraphicsNode;
    for (list<Node*>::const_iterator i = newNodes.begin(); i != newNodes.end(); ++i)
    {
        // create the newGraphicsNode and put it in a temp variable
        newGraphicsNode = new GraphicsNode(NULL, this, 30);
        // add it to the nodeObservers map
        _nodeObservers.insert(*i, newGraphicsNode);

        /* telling the observers what toolhandler we are using making it possible to react
            in the proper way when ie the user hovers over a node using the remove tool*/
        newGraphicsNode->setToolHandler(_toolHandler);
        // update the scenerect so that it has extra space around it
        expandSceneRect((*i)->getCoords());
        newGraphicsNode->setFillColor(_fillColor);
        // register an observer
        (*i)->registerObserver(newGraphicsNode);
        // do the first notify manually, this will set the label and coords and such of the nodeObserver
        newGraphicsNode->notify((*i));
    }
}

void GraphDrawingScene::updateEdgesOfNode(Node* node)
{
    // nodepointer can't be NULL, this would give problems
    assert(node);
    /* this makes it a whole lot efficienter when reading big graphs without edges,
        the nodeedges don't have to be retrieved because it's empty anyways*/
    if (!_graph->getNumberOfEdges())
        return ;
    /* if the last cached node is diferrent from the node that we are updating
        the edges from, we change the cached node to the node that and cache those edges that need updating*/
    cacheEdgesForNode(node);
    // now update the cached edges
    updateEdges(_cachedEdges);
}

void GraphDrawingScene::removeFromMap(Node* node)
{
    _nodeObservers.erase(_nodeObservers.find(node));
}

void GraphDrawingScene::removeFromMap(Edge* edge)
{
    _edgeObservers.erase(_edgeObservers.find(edge));
}

void GraphDrawingScene::addToMap(Node* node, GraphicsNode* graphicsNode)
{
    _nodeObservers.insert(node, graphicsNode);
}

void GraphDrawingScene::addToMap(Edge* edge, GraphicsEdge* graphicsEdge)
{
    _edgeObservers.insert(edge, graphicsEdge);
}


void GraphDrawingScene::cacheEdgesForNode(Node *node)
{
    if (_cachedNode != node)
    {
        // this is the variable that the edges will be saved to temporarly to prevent calling the getOutgoingEdges and getIncommingEdges more than once
        list<Edge*> tempEdges;
        _cachedEdges.clear();

        tempEdges = _graph->getIncomingEdges(node);
        // add the outgoing edges
        for (list<Edge*>::iterator i = tempEdges.begin(); i != tempEdges.end(); ++i)
            _cachedEdges.push_back(*i);
        tempEdges = _graph->getOutgoingEdges(node);
        // append the stdlist, QList doesn't support appending from an stdlist
        for (list<Edge*>::iterator i = tempEdges.begin(); i != tempEdges.end(); ++i)
            _cachedEdges.push_back(*i);
        _cachedNode = node;
    }
}

void GraphDrawingScene::updateEdges(const QList<Edge*>& edges)
{
    // for efficiency, cancel the function if the list is empty
    if (edges.empty())
        return ;
    for (QList<Edge*>::const_iterator i = edges.begin(); i != edges.end(); ++i)
        (*i)->notifyObservers();
}

void GraphDrawingScene::addNewEdges(const list<Edge*>& newEdges)
{
    // for efficiency, cancel the function if the list is empty
    if (newEdges.empty())
        return ;
    GraphicsEdge* newGraphicsEdge;
    for (list<Edge*>::const_iterator i = newEdges.begin(); i != newEdges.end(); ++i)
    {
        newGraphicsEdge = new GraphicsEdge(NULL, this);
        newGraphicsEdge->setAcceptHoverEvents(true);
        newGraphicsEdge->setToolHandler(_toolHandler);

        (*i)->registerObserver(newGraphicsEdge);
        newGraphicsEdge->notify(*i);
        _edgeObservers.insert(*i, newGraphicsEdge);
    }
}

void GraphDrawingScene::setDeleteStyleEdges(Node* node)
{
    // first cache the edges for the node if it hasn't been done so yet
    cacheEdgesForNode(node);
    for (QList<Edge*>::iterator i = _cachedEdges.begin(); i != _cachedEdges.end(); ++i)
        _edgeObservers[*i]->setColor(RGB::colorDelete());
}

void GraphDrawingScene::setNormalStyleEdges(Node* node)
{
    // first cache the edges for the node if it hasn't been done so yet
    cacheEdgesForNode(node);
    for (QList<Edge*>::iterator i = _cachedEdges.begin(); i != _cachedEdges.end(); ++i)
        _edgeObservers[*i]->unSetColor();
}

QList<QGraphicsItem *> GraphDrawingScene::filterForType(QList<QGraphicsItem *>& itemList, int type)
{
    QList<QGraphicsItem *>::iterator i = itemList.begin();
    while(i != itemList.end())
    {
        if ((*i)->type() != (int)type)
        {
            itemList.erase(i);
            i = itemList.begin();
        }
        else
            ++i;
    }
    return itemList;
}

void GraphDrawingScene::deleteOldNodes()
{
    if (_nodeObserversToRemove.empty())
        return ;

    for (QList<GraphicsNode*>::iterator i = _nodeObserversToRemove.begin(); i != _nodeObserversToRemove.end();++i)
    {
        // first remove it from the _nodeObservers list
        _nodeObservers.erase(_nodeObservers.find((*i)->getNode()));
        // then remove it from the scene
        removeItem(*i);
        // finally free all the memory allocated to the node observer
        delete *i;
    }
    // don't want to have double free's next time
    _nodeObserversToRemove.clear();
}

void GraphDrawingScene::deleteOldEdges()
{
    if (_edgeObserversToRemove.empty())
        return ;
    for (QList<GraphicsEdge*>::iterator i = _edgeObserversToRemove.begin(); i != _edgeObserversToRemove.end();++i)
    {
        // first remove it from the _nodeObservers list
        _edgeObservers.erase(_edgeObservers.find((*i)->getEdge()));
        // then remove it from the scene
        removeItem(*i);
        // finally free all the memory allocated to the node observer
        delete *i;
    }
    // don't want to have double free's next time
    _edgeObserversToRemove.clear();
}

void GraphDrawingScene::deleteMeAtNextUpdate(GraphicsNode* me)
{
    _nodeObserversToRemove.push_back(me);
}

void GraphDrawingScene::deleteMeAtNextUpdate(GraphicsEdge* me)
{
    _edgeObserversToRemove.push_back(me);
}

void GraphDrawingScene::expandSceneRect(const Point& position)
{
    expandSceneRect(QPoint(position.getX(), position.getY()));
}

void GraphDrawingScene::expandSceneRect(const QPoint& position)
{
    // start by creating a rectangle around the position that has been passed
    QRect expander(position.x() - 250, position.y() - 250, 500, 500);
    // calculate the bounding rectangle of what we already have and what we wan to add
    setSceneRect(sceneRect().united(expander));
    dynamic_cast<GraphDrawingView*>(parent())->setSceneRect(sceneRect());
}
