#include <sstream>
#include <assert.h>

#include "graph.h"
#include "graphComp/node.h"

Graph::Graph()
{
    _name = "";
    _numberOfNodes = 0;
    _numberOfEdges = 0;
}

Graph::Graph(const string& name) : _name(name)
{
    _numberOfNodes = 0;
    _numberOfEdges = 0;
}

// copy constructor is needed because we use a vector of Node*, the copyconstructor copies over all
Graph::Graph(const Graph& other) : Subject()
{
    // copy the name of the other graph
    _name = other.getName();
    for (unsigned i = 0; i < other.getNumberOfNodes(); ++i)
        _nodes.push_back(new Node(*(other._nodes[i])));
    // the rest of the copyconstructor is done in the derived classes
}

Graph::~Graph()
{
    removeNodes();
    // free nodes, edges are done in deriven classes, those will probabily call removeEdges();
}

void Graph::addNode(const Node& node)
{
    addNode(new Node(node));
}

// adds a Node by a pointer to a node
void Graph::addNode(Node* node)
{
    _nodes.push_back(node);
    // add this to the lastAddedNodes list so that it can be used to update the observers of the graph
    _lastAddedNodes.push_back(node);
    ++_numberOfNodes; // adjust counter
}

list<Edge*> Graph::getLastAddedEdges()
{
    list<Edge*> tempList = _lastAddedEdges;
    _lastAddedEdges.clear();
    return tempList;
}

list<Node*> Graph::getLastAddedNodes()
{
    list<Node*> tempList = _lastAddedNodes;
    _lastAddedNodes.clear();
    return tempList;
}

// removes ALL nodes from this graph
void Graph::removeNodes()
{
    // delete all the nodes we have created, keep deleting the first one untill there are none left
    for (vector<Node*>::iterator i = _nodes.begin(); i != _nodes.end(); ++i)
        delete *i;
    // now clear the nodes
    _nodes.clear();
    _numberOfNodes = 0; // adjust counter
//    notifyObservers(); // all removeNodes operations finish with this one, so notifyObservers() only needs to be here
}

// removes a given node identified by a pointer to that node
void Graph::removeNode(Node* node)
{
     delete node;
    _nodes.erase(_nodes.begin() + nodeToIndex(node));
    --_numberOfNodes; // adjust counter
//    notifyObservers(); // all removeNode operations finish with this one, so notifyObservers() only needs to be here
}

void Graph::removeNode(unsigned id)
{
    assert(id < _nodes.size() - 1);
    delete _nodes[id];
    _nodes.erase(_nodes.begin() + id);
    --_numberOfNodes;
//    notifyObservers();
}

// will return the node with label label
Node* Graph::labelToNode(const Label& label) const
{
    Node* result = NULL;
    // search for the node with the same label
    for (unsigned i = 0; i < this->_nodes.size(); ++i)
    {
        result = _nodes.at(i);
        if (result->getLabel() == label)
            return result;
    }

    return NULL;
}

// returns the index of the node* in the vector of nodes
int Graph::nodeToIndex(Node *node) const
{
    int index = -1;
    if (!node)
        return index;
    for (unsigned i = 0; i < this->_nodes.size(); ++i)
    {
        if (_nodes.at(i) == node)
            return i;
    }
    return index;
}

Node* Graph::idToNode(unsigned long id) const
{
    for (unsigned i = 0; i < _nodes.size(); ++i)
        if (_nodes[i]->getID() == id)
            return _nodes[i];
    return NULL;
}

bool Graph::isUniqueNode(const Label& label) const
{
    // empty labels are by definition unique
    if (label == Label(""))
        return true;
    for (unsigned i = 0; i < _nodes.size(); ++i)
    {
        // return true if we find a node with the same label
        if(_nodes[i]->getLabel() == label)
            return false;
    }
    return true;
}

QDebug operator<<(QDebug dbg, const Graph& other)
{
    dbg.nospace() << other.toString().c_str();
    return dbg;
}

ostream& operator<<(ostream& dbg, const Graph& other)
{
    cout << other.toString();
    return dbg;
}
