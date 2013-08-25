#include "hybridgraph.h"
#include "graph/hybridGraphState/liststate.h"
#include "graph/hybridGraphState/matrixstate.h"
#include "graphComp/node.h"
#include <sstream>

HybridGraph::HybridGraph()
{
    _oldState = NULL;
    // per definition the ListGraph is the first state, this is all what the empty constructor does
    _state = new ListState();
}


HybridGraph::HybridGraph(const string& name)
{
    _oldState = NULL;
    // the constructors that are already implemented will take care of everything
    _state = new ListState(name);
}

HybridGraph::HybridGraph(const Graph &other)
{
    _oldState = NULL;
    _state = NULL; // recreateFrom will delete it and set the new state
    recreateFrom(other);
}

void HybridGraph::addNode(const Node& other)
{
    _state->addNode(this, other);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::recreateFrom(const IntegerMatrix& other)
{
    _state->recreateFrom(this, other);
    deleteOldState();
    notifyObservers();
}

// removes nodes
void HybridGraph::removeNodes()
{
    _state->removeNodes(this);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::deleteOldState()
{
    if (_oldState)
    {
        // swap out the observers, the node and edge observers are handled by the HybridGraphStates themselves
        _state->getGraph()->registerObservers(_oldState->getGraph()->getObservers());
        delete _oldState;
        _oldState = NULL;
    }
}

void HybridGraph::removeNode(Node *node)
{
    _state->removeNode(this, node);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::removeNode(unsigned id)
{
    _state->removeNode(this, id);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::removeNode(unsigned long ID)
{
    _state->removeNode(this, ID);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::removeEdge(unsigned sourceID, unsigned targetID, const Label& label)
{
    _state->removeEdge(this, sourceID, targetID, label);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::removeEdge(unsigned long sourceID, unsigned long targetID, const Label& label)
{
    _state->removeEdge(this, sourceID, targetID, label);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::addEdge(unsigned sourceID, unsigned targetID, const Label& label)
{
    _state->addEdge(this, sourceID, targetID, label);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::addEdge(unsigned long sourceID, unsigned long targetID, const Label& label)
{
    _state->addEdge(this, sourceID, targetID, label);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::addEdge(const Edge& edge)
{
    _state->addEdge(this, edge);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::removeEdges()
{
    _state->removeEdges(this);
    deleteOldState();
    notifyObservers();
}

void HybridGraph::removeEdge(Node* source, Node* target, const Label& label)
{
    _state->removeEdge(this, source, target, label);
    deleteOldState();
    notifyObservers();
}

// recreates from other graphtypes
void HybridGraph::recreateFrom(const Graph& other)
{
    delete _state;
    _state = new ListState(other.getName());
    _state->recreateFrom(this, other);
    deleteOldState();
    notifyObservers();
}

// TODO: determin the state before starting the copy of the integerMatrix
HybridGraph::HybridGraph(const IntegerMatrix& integerMatrix)
{
    delete _state;
    _oldState = NULL;
    // default startingstate is list because an empty graph is sparse
    _state = new ListState(integerMatrix);
    deleteOldState();
    notifyObservers();
}

// destructor deletes the sate (also deleting the list or matrix graph)
HybridGraph::~HybridGraph()
{
    // remove the state that we have alocated for the state pattern
    delete _state;
    delete _oldState;
}

// friend
QDebug operator<<(QDebug dbg, const HybridGraph& other)
{
    dbg.nospace() << *(other._state);
    return dbg.space();
}

ostream& operator<<(ostream& dbg, const HybridGraph& other)
{
    cout << other.toString();
    return dbg;
}
