#include <assert.h>
// needed for round to decide if the condition for the state switch is met
#include <math.h>
#include "liststate.h"
#include "graph/hybridGraphState/matrixstate.h"

ListState::ListState(HybridGraph* context, const Graph& other)
{
    _graph = NULL;
    recreateFrom(context, other);
}

ListState::ListState(HybridGraph* context, const HybridGraphState& other)
{
    // first check that the state that is being constructor is the right state
    switchState(context, other.getNumberOfNodes(), other.getNumberOfEdges());
    // create this state from another state
    _graph = new ListGraph(*(other.getGraph()));
}

void ListState::recreateFrom(HybridGraph *context, const IntegerMatrix &other)
{
    _graph->recreateFrom(other);
    switchState(context);
}

void ListState::removeNodes(HybridGraph* context)
{
    _graph->removeNodes();
    switchState(context, _graph->getNumberOfEdges(), 0);
}

void ListState::removeNode(HybridGraph *context, Node *node)
{
    _graph->removeNode(node);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::addEdge(HybridGraph* context, unsigned sourceIndex, unsigned targetIndex, const Label& label)
{
    _graph->addEdge(sourceIndex, targetIndex, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::addEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label)
{
    _graph->addEdge(sourceID, targetID, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::addEdge(HybridGraph *context, const Edge& edge)
{
    _graph->addEdge(edge);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::removeEdge(HybridGraph* context, Node* source, Node* target, const Label& label)
{
    _graph->removeEdge(source, target, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::removeEdge(HybridGraph *context, unsigned sourceIndex, unsigned targetIndex, const Label& label)
{
    _graph->removeEdge(sourceIndex, targetIndex, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::removeEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label)
{
    _graph->removeEdge(sourceID, targetID, label);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::removeNode(HybridGraph *context, unsigned index)
{
    _graph->removeNode(index);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::removeNode(HybridGraph *context, unsigned long ID)
{
    _graph->removeNode(ID);
    switchState(context, _graph->getNumberOfEdges(), _graph->getNumberOfNodes());
}

void ListState::removeEdges(HybridGraph* context)
{
    // removing all the edges will keep the graph sparse
    _graph->removeEdges();
    switchState(context, 0, _graph->getNumberOfNodes());
}

void ListState::recreateFrom(HybridGraph* context, const Graph& other)
{
    // delete the old _graph, if recreateFrom is called the first time (by the constructor) _graph pointer is a NULL pointer
    delete _graph;
    assert(context);
    _graph = new ListGraph(other);
    // check if state switching would be needed, if so then make the switch
    switchState(context, other.getNumberOfEdges(), other.getNumberOfNodes());
}

void ListState::addNode(HybridGraph *context, const Node& other)
{
    _graph->addNode(other);
    switchState(context, getNumberOfEdges(), getNumberOfNodes());
}

void ListState::switchState(HybridGraph* context)
{
    assert(context);
    // the "default paramters" for switchstate are the current number of edges and nodes
    switchState(context, getNumberOfEdges(), getNumberOfNodes());
}

void ListState::switchState(HybridGraph* context, float e, float n)
{
    // context can't be the NULL pointer and can only be caused by programming error
    assert(context);
    // we have to switch to matrixstate if the following condition is true
    if (e > (n*n) && n >= 3)
    {
        qDebug() << "Setting state to: MatrixState";
        setState(context, new MatrixState(context , *this)); // this will "delete this"
    }
}

// friend
QDebug operator<<(QDebug dbg, const ListState& other)
{
    dbg.nospace() << other.toString().c_str();
    return dbg.space();
}
