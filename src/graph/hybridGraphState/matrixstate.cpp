#include <math.h>
#include <assert.h>

#include "matrixstate.h"
#include "graph/hybridgraph.h"
#include "graph/hybridGraphState/liststate.h"

MatrixState::MatrixState(HybridGraph* context, const Graph& other)
{
    _graph = NULL;
    recreateFrom(context, other);
}

MatrixState::MatrixState(HybridGraph* context, const HybridGraphState& other)
{
    // create this state from another state
    _graph = new MatrixGraph(*(other.getGraph()));
    switchState(context, other.getNumberOfEdges(), other.getNumberOfNodes());
}

void MatrixState::recreateFrom(HybridGraph *context, const IntegerMatrix &other)
{
    _graph->recreateFrom(other);
    switchState(context);
}

void MatrixState::addNode(HybridGraph *context, const Node& other)
{
    _graph->addNode(other);
    switchState(context, getNumberOfEdges(), getNumberOfNodes());
}

void MatrixState::removeNodes(HybridGraph* context)
{
     _graph->removeNodes();
    switchState(context, _graph->getNumberOfEdges(), 0);
}

void MatrixState::removeNode(HybridGraph *context, Node *node)
{
    _graph->removeNode(node);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::addEdge(HybridGraph* context, unsigned sourceIndex, unsigned targetIndex, const Label& label)
{
    _graph->addEdge(sourceIndex, targetIndex, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::addEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label)
{
    _graph->addEdge(sourceID, targetID, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::addEdge(HybridGraph *context, const Edge& edge)
{
    _graph->addEdge(edge);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}


void MatrixState::removeEdge(HybridGraph* context, Node* source, Node* target, const Label& label)
{
    _graph->removeEdge(source, target, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::removeEdges(HybridGraph* context)
{
    switchState(context, 0, _graph->getNumberOfNodes());
    _graph->removeEdges();
}

void MatrixState::removeEdge(HybridGraph *context, unsigned sourceIndex, unsigned targetIndex, const Label& label)
{
    _graph->removeEdge(sourceIndex, targetIndex, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::removeEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label)
{
    _graph->removeEdge(sourceID, targetID, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::removeNode(HybridGraph *context, unsigned index)
{
    _graph->removeNode(index);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::removeNode(HybridGraph* context, unsigned long ID)
{
    _graph->removeNode(ID);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void MatrixState::recreateFrom(HybridGraph* context, const Graph& other)
{
    // delete the old _graph, if recreateFrom is called the first time (by the constructor) _graph pointer is a NULL pointer
    delete _graph;
    assert(context);
    // check if state switching would be needed, if so then make the switch
    _graph = new MatrixGraph(other);
    switchState(context, other.getNumberOfEdges(), other.getNumberOfNodes());
}

void MatrixState::switchState(HybridGraph* context)
{
    switchState(context, getNumberOfEdges(), getNumberOfNodes());
}

void MatrixState::switchState(HybridGraph* context, float e, float n)
{
    if (round(e*1.1F) <= (n*n) && n >= 3)
    {
        qDebug() << "Setting state to: ListState";
        setState(context, new ListState(context, *this)); // this will "delete this"
    }
}

// friend
QDebug operator<<(QDebug dbg, const MatrixState& other)
{
    dbg.nospace() << other.toString().c_str();
    return dbg.space();
}
