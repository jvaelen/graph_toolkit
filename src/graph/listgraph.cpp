#include "listgraph.h"
#include "matrixgraph.h"
#include "graphComp/node.h"
#include "graphComp/edge.h"
#include "exception/uniqueedgeex.h"
#include "exception/uniquenodeex.h"
#include "exception/unexistingedgeex.h"
#include "exception/unexistingnodeex.h"
#include <assert.h>
#include <sstream>
#include <QDebug>
#include <cmath>

void ListGraph::recreateFrom(const Graph& other)
{
    // calling recreateFrom with itself doesn't change anything
    if(&other == this)
        return ;
    _name = other.getName();
    list<Edge*> tempEdges;
    // clean up structure
    removeNodes();
    vector<Node*> otherNodes = other.getNodes();
    for (unsigned i = 0; i < otherNodes.size(); ++i)
        addNode(*otherNodes[i]); // addNode(otherNodes[i]) will NOT allocate new node!!

    // nodes have been added to the structure, now add all edges
    for (unsigned i = 0; i < _numberOfNodes; ++i)
    {
        tempEdges = other.getOutgoingEdges(otherNodes[i]);
        for (list<Edge*>::const_iterator j = tempEdges.begin(); j != tempEdges.end(); ++j)
        {
            Edge tempEdge = **j;
            tempEdge.setSource(_nodes[(other.nodeToIndex((*j)->getSource()))]);
            tempEdge.setTarget(_nodes[(other.nodeToIndex((*j)->getTarget()))]);
            addEdge(tempEdge);
        }
    }
}

ListGraph::ListGraph(const Graph& other)
{
    // do not call the copyconstructor of Graph. nodes will be created by recreateFrom(other);
    recreateFrom(other);
}

IntegerMatrix ListGraph::getIntegerMatrix() const
{

    IntegerMatrix result;
    for (vector<Node*>::const_iterator i = _nodes.begin(); i != _nodes.end(); ++i)
        result.addNode(**i);

    // run through adj list
    for (unsigned i = 0; i < this->_numberOfNodes; ++i)
    {
        // is there a self edge with the current node? if so add it
        if ( (*(this->_adjacencyList[i].begin())).second != NULL)
            result.addEdge( *(*this->_adjacencyList[i].begin()).first, *(*this->_adjacencyList[i].begin()).first );
        // run through every list, skipping the first element, and add all edges using Node references
        for (list<pair<Node*, Edge*> >::const_iterator it = ++this->_adjacencyList[i].begin();
             it != this->_adjacencyList[i].end(); ++it)
            // addEdge(First Node Of List (not pointer, reference), Current Iterated Note (not pointer))
            result.addEdge(*(*this->_adjacencyList[i].begin()).first, *((*it).first));
    }
    return result;

}

ListGraph::ListGraph(const IntegerMatrix& other)
{
    recreateFrom(other);
}


void ListGraph::recreateFrom(const IntegerMatrix& other)
{
    removeNodes();
    // Graph(integerMatrix) will create the nodes from the integerMatrix, each node with standard labels
    const vector<vector<unsigned> >& integers = other.getMatrix();
    for (unsigned i = 0; i < integers.size(); ++i)
    {
        Node newNode(getNodeNameHint());
        // use a standard name for the node, integermatrix doesn't hav information about this
        addNode(newNode);
    }
    // add edges
    for(unsigned i  = 0; i < integers.size(); ++i)
        for (unsigned j = 0; j < integers[i].size(); ++j)
            for (unsigned k = 0 ; k < integers[i][j]; ++k)
                addEdge(Edge(_nodes[i], _nodes[j]));
}



list<Edge*> ListGraph::getOutgoingEdges(Node* node) const
{
    // make sure node exists
    assert(node != NULL);

    bool stop = false;
    list<Edge*> result;
    // run through lists
    for (unsigned i = 0; i < this->_numberOfNodes && !stop; ++i)
    {
        if (this->_adjacencyList[i].front().first == node)
        {
            // list that represents our node has been found

            // first node can have a self edge, if it does not Edge* is NULL
            if (this->_adjacencyList[i].front().second != NULL)
                result.push_back(this->_adjacencyList[i].front().second);
            // iterate through rest of list and add all edges to result
            for (list<pair<Node*, Edge*> >::const_iterator it = ++this->_adjacencyList[i].begin();
                 it != this->_adjacencyList[i].end(); ++it)
                // no need for tests because every node in this list MUST HAVE a correct Edge*
                result.push_back((*it).second);
            stop = true;
        }
    }

    return result;
}

list<Edge*> ListGraph::getIncomingEdges(Node* node)  const
{
    // make sure node exists
    assert(node != NULL);

    list<Edge*> result;
    // run through lists
    for (unsigned i = 0; i < this->_numberOfNodes; ++i)
    {
        // if we are in the list that is not corresponding with node, we have to start from the second element
        // else we need the self edges and have to also check the first element

        // also test for the first element, could be a self edge
        if (this->_adjacencyList[i].front().first == node && this->_adjacencyList[i].front().second != NULL)
            result.push_back(this->_adjacencyList[i].front().second);

        for (list<pair<Node*, Edge*> >::const_iterator it = ++this->_adjacencyList[i].begin();
             it != this->_adjacencyList[i].end(); ++it)
        {
            if ( (*it).first == node )
                result.push_back( (*it).second );
        }

    }
    return result;
}

list<Node*> ListGraph::getNeighbours(Node* node) const
{
    // make sure node exists
    assert(node != NULL);

    bool stop = false;
    list<Node*> result;
    // get all nodes that are connected to node
    for (unsigned i = 0; i < this->_numberOfNodes && !stop; ++i)
    {
        if (this->_adjacencyList[i].front().first == node)
        {
            // iterate through list and add all nodes to result
            for (list<pair<Node*, Edge*> >::const_iterator it = this->_adjacencyList[i].begin();
                 it != this->_adjacencyList[i].end(); ++it)
            {
                // test 1 is a sanity check, test 2 makes sure we add node itself only when it has a self edge
                if ((*it).first != NULL && (*it).second != NULL)
                    result.push_back((*it).first);
            }
            stop = true;
        }
    }
    return result;
}

// this function cannot be called directly by the user!
// this function does NOT allocate a Node*, see addNode(Label)
void ListGraph::addNode(Node *node)
{
    // make sure node is not a NULL pointer
    assert(node);
    // add the node to the vector _nodes and increment _numberOfNodes
    Graph::addNode(node);
    // make room for a new spot in our vector
    list<pair<Node*, Edge*> > newElement;
    pair<Node*, Edge*> newPair;
    // when we add a new node, we make room for a new list in our adj matrix
    // the first element of the list is the node that is represented with this place in the vector
    // this element's second is NULL because it has no edge with itself.
    newPair.first = node;
    newPair.second = NULL;
    newElement.push_back(newPair);
    this->_adjacencyList.push_back(newElement);
    notifyObservers();
}

void ListGraph::addNode(const Node &other)
{
    addNode(new Node(other));
}

void ListGraph::removeNode(unsigned id)
{
    if (id > _numberOfNodes - 1)
        throw UnexistingNodeEx(Node(), "id does not exist");
    removeNode(_nodes[id]);
}

void ListGraph::removeNode(Node *node)
{
    int originalNodeIndex = nodeToIndex(node);

    // make sure the node exists
    assert(originalNodeIndex != -1);
    // we know that nodeToIndex(node) returns the index of _nodes corresponding with our node
    // let i be the i-th member of _nodes, then we also know that it's the i-th member of our _adjacencyListList!! [VERSLAG]
    // first clean the adjacencyList list (remove edges corresponding with our node)
    for (unsigned int i = 0; i < this->_numberOfNodes; ++i)
    {
        if (!(_adjacencyList[i].begin()->first == node))
        {
            // run through the list and check for edges with the node we want to delete-> delete these edges
            // notice that we begin at begin() + 1 because we already know that the first element is not important
            // and we test for *it.first

            list<pair<Node*, Edge*> >::iterator it = _adjacencyList[i].begin();
            while (it != _adjacencyList[i].end())
            {
                if ((*it).first == node)
                {
                    delete (*it).second;
                    // remove the pair from the list
                    _adjacencyList[i].erase(it);
                    // restart because iterator has changed
                    it = _adjacencyList[i].begin();
                }
                else
                    it++;
            }
        }
    }

    // now delete the entire list corresponding with our node (delete edges and remove the list)
    for (list<pair<Node*, Edge*> >::iterator it = this->_adjacencyList[originalNodeIndex].begin();
         it != this->_adjacencyList[originalNodeIndex].end(); ++it)
    {
        delete (*it).second;
    }

    // we have deleted all edges in the list corresponding with the node, now remove the entire list
    _adjacencyList.erase(_adjacencyList.begin() + originalNodeIndex);

    // remove from _nodes vector-> node is really gone now
    Graph::removeNode(node);
    notifyObservers();

}

void ListGraph::removeNodes()
{
    // clear all edges -> delete them
    removeEdges();

    // empty all lists -> no deletion, just list clearing
    _adjacencyList.clear();

    // remove and delete nodes in _node vector
    Graph::removeNodes();
    notifyObservers();
}

void ListGraph::addEdge(const Edge &edge)
{
    int sourceIndex = nodeToIndex(edge.getSource());
    int targetIndex = nodeToIndex(edge.getTarget());

    if (!isUniqueEdge(edge)) // check if the edge is unique
        throw UniqueEdgeEx(edge);
    // make sure the nodes exist -- replace with exception?
    assert(sourceIndex != -1 && targetIndex != -1);

    bool stop = false;
    /* we need to check for self-edges because else we can get the situation:
     [0]->1,NULL->2,Edge*->1,Edge*
     [1]->2,NULL->blabla
     [2]->3,NULL->blabla
     Where 1 has a self edge, instead of
     [0]->1,Edge*->2,Edge*->1,Edge*
     [1]->2,NULL->blabla
     [2]->3,NULL->blabla
     */
    bool isSelfEdge = (edge.getSource()== edge.getTarget());

    // edge does not exist yet, so create it
    Edge* newEdge = new Edge(edge);
    // parameters for adjacencyListlist
    pair<Node*, Edge*> newPair;
    newPair.first = edge.getTarget();
    newPair.second = newEdge;
    // navigate to the correct spot to add the edge
    for (unsigned int i = 0; i < _numberOfNodes && !stop; ++i)
    {
        if (_adjacencyList[i].front().first == edge.getSource())
        {
            // found the correct list (corresponding with the source node)
            // add the new pair (target, edge) or add the selfedge
            if (isSelfEdge && _adjacencyList[i].front().second == NULL)
                _adjacencyList[i].front().second  = newEdge;
            else
                _adjacencyList[i].push_back(newPair);
            stop = true;
            _lastAddedEdges.push_back(newEdge);
            _numberOfEdges++;
        }
    }
    notifyObservers();
}

void ListGraph::addEdge(unsigned sourceIndex, unsigned targetIndex, const Label& label)
{
    // if one of the nodes does not exist, throw exception
    if(sourceIndex + 1> _numberOfNodes || targetIndex + 1> _numberOfNodes)
        throw UnexistingNodeEx(Node(), "The edge can't be created, because one (or both) node(s) are invalid", 2);
    addEdge(Edge(_nodes[sourceIndex], _nodes[targetIndex], label));
}

void ListGraph::removeEdge(Node *source, Node *target, const Label& label)
{
    // make sure the nodes exist
    assert(source != NULL && target != NULL);

    bool isSelfEdge = (source == target);
    bool stop = false;

    for (unsigned i = 0; i < this->_numberOfNodes && !stop; ++i)
    {
        // list corresponding with our node
        if (_adjacencyList[i].front().first == source)
        {
            // run through list to find target
            list<pair<Node*, Edge*> >::iterator it = _adjacencyList[i].begin();
            while (it != _adjacencyList[i].end() && !stop)
            {
                if ( (*it).first == target && (*it).second != NULL && (*it).second->getLabel() == label )
                {
                    delete (*it).second;
                    stop = true;
                    this->_numberOfEdges--;
                    // if it is a self edge AND the self edge is the list head we only have to delete the pointer
                    // otherwise we also have to delete the pair out of our list
                    if (!(isSelfEdge && it == _adjacencyList[i].begin()))
                        _adjacencyList[i].erase(it);
                    else
                        // set to NULL so we don't have a danling pointer!
                        (*it).second = NULL;
                }
                else
                    it++;
            }
        }
    }
    notifyObservers();
}

void ListGraph::removeEdge(unsigned sourceIndex, unsigned targetIndex, const Label& label)
{
    if (sourceIndex + 1> _numberOfNodes || targetIndex + 1> _numberOfNodes)
        throw(UnexistingNodeEx(Node(), "invalid node id"));
    else if (!edgeExists(_nodes[sourceIndex], _nodes[targetIndex], label))
        throw(UnexistingEdgeEx(Edge(_nodes[sourceIndex], _nodes[targetIndex], label)));

    removeEdge(_nodes[sourceIndex], _nodes[targetIndex], label);
}


bool ListGraph::edgeExists(Node* source, Node* target, const Label& label) const
{
    // make sure the nodes are valid
    assert(nodeToIndex(source) != -1 && nodeToIndex(target) != -1);

    list<Edge*> temp = getOutgoingEdges(source);
    for (list<Edge*>::const_iterator i = temp.begin(); i != temp.end(); ++i)
        if ((*i)->getTarget() == target && (*i)->getLabel() == label)
            return true;
    return false;
}


void ListGraph::removeEdges()
{
    // if we want to remove all edges, we just wind up with all our nodes
    // we could use removeEdge(Node, Node) on all node couples, but we reimplement this function for the sake of efficiency

    // run through adjacencyList list
    for (unsigned i = 0; i < this->_numberOfNodes; ++i)
    {
        // clear every list, and push back the node
        for (list<pair<Node*, Edge*> >::iterator it = _adjacencyList[i].begin(); it != _adjacencyList[i].end(); ++it)
        {
            // delete all edges
            delete it->second;
        }
        _adjacencyList[i].clear();
        pair<Node*, Edge*> newPair;
        newPair.first = _nodes[i];
        newPair.second = NULL;
        _adjacencyList[i].push_back(newPair);
    }
    this->_numberOfEdges = 0;
    notifyObservers();
}


bool ListGraph::isUniqueEdge(const Edge& edge) const
{
    // loop lijsten af, kijk wanneer edge zijn source de first is van een lijst
    // loop dan die lijst af en kijk wanneer er een first gelijk is met de target
    // check die zijn label == edge.label
    for (unsigned i = 0; i < this->_numberOfNodes; ++i)
    {
        // located the list corresponding with our source
        if (this->_adjacencyList[i].front().first == edge.getSource())
        {
            // iterate through list
            for (list<pair<Node*, Edge*> >::const_iterator it = this->_adjacencyList[i].begin();
                 it != this->_adjacencyList[i].end(); ++it)
            {
                // if there is an edge between source and target, check if the labels are equal
                // if so, edge is not unique
                if ((*it).first == edge.getTarget() && (*it).second != NULL && (*it).second->getLabel() == edge.getLabel())
                    return false;
            }
        }
    }
    // if we get here, edge is unique
    return true;
}

Edge* ListGraph::labelToEdge(const Label& label) const
{
    // run through adjacencyListlist and find the first edge with label label
    for (unsigned i = 0; i < this->_numberOfNodes; ++i)
    {
        // run through list and check for every pair if the edge's label == label
        for (list<pair<Node*, Edge*> >::const_iterator it = this->_adjacencyList[i].begin();
             it != this->_adjacencyList[i].end(); ++it)
        {
            if ( (*it).second != NULL && (*it).second->getLabel() == label)
                return ( (*it).second );
        }
    }
    return NULL;
}


string ListGraph::toString() const
{
    ostringstream str;
    for (unsigned i = 0; i < _numberOfNodes; ++i)
    {
        for (list<pair<Node*, Edge*> >::const_iterator it = _adjacencyList[i].begin();
             it != _adjacencyList[i].end(); ++it)
        {
            if ((*it).second == NULL)
                str << (*it).first->getLabel() << "|N/A" << "->";
            else
                str << (*it).first->getLabel() << "|" << "\"" << (*it).second->getLabel() << "\"->";
        }
        str << endl;
    }
    return str.str();

}

string ListGraph::toStringID() const
{
    ostringstream str;
    for (unsigned i = 0; i < _numberOfNodes; ++i)
    {
        for (list<pair<Node*, Edge*> >::const_iterator it = _adjacencyList[i].begin();
             it != _adjacencyList[i].end(); ++it)
        {
            if ((*it).second == NULL) // hier moet ge nog voor getlabel ook doen
                str << nodeToIndex((*it).first) << "|N/A" << "->";
            else
                str << nodeToIndex((*it).first) << "|" << "\"" << (*it).second->getLabel() << "\"->";
        }
        str << endl;
    }
    return str.str();
}

QDebug operator<<(QDebug dbg, const ListGraph& other)
{
    qDebug() << other.toString().c_str();
    return dbg;
}

ostream& operator<<(ostream& dbg, const ListGraph& other)
{
    cout << other.toString();
    return dbg;
}

