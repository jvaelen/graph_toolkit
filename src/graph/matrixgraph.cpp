#include <assert.h>
#include <list>
#include <vector>
#include <sstream>
#include <cmath>

#include "matrixgraph.h"
#include "graphComp/node.h"
#include "graphComp/edge.h"
#include "listgraph.h"
#include "exception/uniqueedgeex.h"
#include "exception/unexistingedgeex.h"
#include "exception/unexistingnodeex.h"

MatrixGraph::MatrixGraph() : Graph()
{
    // default constructor does nothing for now
}

MatrixGraph::MatrixGraph(const Graph& other)
{
    // do not call the copyconstructor of Graph. nodes will be created by recreateFrom(other);
    recreateFrom(other);
}

MatrixGraph::MatrixGraph(const IntegerMatrix& integerMatrix)
{
    recreateFrom(integerMatrix);
}

void MatrixGraph::recreateFrom(const IntegerMatrix& integerMatrix)
{
    // clear the graph
    removeNodes();
    // temp edge variable that holds the allocated edge
    Edge* newEdge;
    const vector<vector<unsigned> >& integers = integerMatrix.getMatrix();
    for (unsigned i = 0; i < integers.size(); ++i)
    {
        Node newNode(getNodeNameHint());
        addNode(newNode);
    }
    // add the edges
    for(unsigned i  = 0; i < integers.size(); ++i)
        for (unsigned j = 0; j < integers[i].size(); ++j)
            for (unsigned k = 0 ; k < integers[i][j]; ++k) // add k number of edges from i to j
            {
                newEdge = new Edge(_nodes[i], _nodes[j]);
                _matrix[i][j].push_back(newEdge);
                _lastAddedEdges.push_back(newEdge);
            }
    notifyObservers();
}

MatrixGraph::~MatrixGraph()
{
    // removeNodes will also remove all the edges
    this->removeNodes();
}

IntegerMatrix MatrixGraph::getIntegerMatrix() const
{
    IntegerMatrix result;
    for (vector<Node*>::const_iterator i = _nodes.begin(); i != _nodes.end(); ++i)
        result.addNode(**i);

    for (unsigned i = 0; i < _matrix.size(); ++i)
        for (unsigned j = 0; j < _matrix[i].size(); ++j)
            for (unsigned k = 0; k < _matrix[i][j].size(); ++k) // add k edges from i to j
                result.addEdge(*_nodes[i], *_nodes[j]);
    return result;
}

void MatrixGraph::addNode(Node* node)
{
    /* node should not be the NULL pointer, this isn't handeld by an exception,
        using a NULL pointer would just be wrong and can only be caused by bad programming */
    assert(node);
    // add the node to the node vector using the superclass
    Graph::addNode(node);
    // now extend the matrix by one
    extendMatrix(1);
}

void MatrixGraph::addNode(const Node& other)
{
    MatrixGraph::addNode(new Node(other));
    notifyObservers();
}

void MatrixGraph::removeNodes()
{
    // immediatly quit if the matrix is empty, also this is for efficiency
    if (_matrix.empty())
        return ;
    // remove everything from the matrix
    for (int i = static_cast<int>(_matrix.size()) -1; i >= 0; --i)
    {
        for (int j =  static_cast<int>(_matrix[i].size()) - 1; j >= 0 ; --j)
        {
            // remove all the edges between node i and j
            deleteEdgesBetweenNodes(i, j);
        }
    }
    //reset the matrix, all the pointers in the matrix should be freed.
    _matrix.clear();
    // now we have no edges
    _numberOfEdges = 0;
    // finish by removing the nodes form the _nodes vector. this is done by the baseclass
    Graph::removeNodes();
    notifyObservers();
}

void MatrixGraph::removeNode(unsigned id)
{
    if (id > _numberOfNodes - 1)
        throw UnexistingNodeEx(Node(), "id does not exist");
    removeNode(_nodes[id]);
}


void MatrixGraph::removeNode(Node* node)
{
    // get the index of a node
    int index = Graph::nodeToIndex(node);
    // this function is private, and can only be called by functions from within MatrixGraph, the invalid Node* can only be caused by bad programming
    assert(index != -1);

    // remove the actual edges
    for (int i = static_cast<int>(_matrix.size()) - 1; i >=0; --i)
    {
        deleteEdgesBetweenNodes(index, i);
        deleteEdgesBetweenNodes(i, index);
    }
    // remove the right colomn and row from the matrix
    retractMatrix(index);
    // removing the node from the _nodes vector is done by the baseclass
    Graph::removeNode(node);
    notifyObservers();
}


void MatrixGraph::addEdge(unsigned sourceID, unsigned targetID, const Label& label)
{
    // if one of the nodes does not exist, throw exception
    if(sourceID + 1> _numberOfNodes || targetID + 1> _numberOfNodes)
        throw UnexistingNodeEx(Node(), "The edge can't be created, because one (or both) node(s) are invalid", 2);
    addEdge(Edge(_nodes[sourceID], _nodes[targetID], label));
}

void MatrixGraph::addEdge(const Edge& edge)
{
    int sourceIndex = nodeToIndex(edge.getSource());
    int targetIndex = nodeToIndex(edge.getTarget());
    // both souldn't be -1, this would mean that source or target don't exists and this can only be caused by bad programming
    assert(sourceIndex != -1 && targetIndex != -1);
    // new edge
    if (!isUniqueEdge(Edge(edge))) // check if the edge is unique
        throw UniqueEdgeEx(edge);
    Edge* newEdge = new Edge(edge);
    _matrix[sourceIndex][targetIndex].push_back(newEdge);
    _numberOfEdges++; // increase the number of edges
    _lastAddedEdges.push_back(newEdge);
    notifyObservers();
}

void MatrixGraph::removeEdges()
{
    /* for efficiency (!!), removeEdge() isn't used here because that would require consecutive looping through
       the lists for each edge that we would delete instead we delete the all the edges and clear the lists*/
    for (unsigned i = 0; i < _matrix.size(); ++i)
        for (unsigned j = 0; j < _matrix.size(); ++j)
        {
            // free up the memory used by the edges
            for (list<Edge*>::iterator k = _matrix[i][j].begin(); k != _matrix[i][j].end(); ++k)
                delete *k;
            // remove all the cleared edge pointers from the matrix
            _matrix[i][j].clear();
        }
    // update the number of edges
    _numberOfEdges = 0;
    notifyObservers();
}

void MatrixGraph::removeEdge(unsigned sourceID, unsigned targetID, const Label& label)
{
    /* the plus one is on the right side of the
        equation because if _numberOfNodes would be 0, 0 - 1 on an unsigned integer would cause an overflow*/
    if (sourceID + 1> _numberOfNodes || targetID + 1> _numberOfNodes)
        throw(UnexistingNodeEx(Node(), "invalid node id"));
    else if (!edgeExists(_nodes[sourceID], _nodes[targetID], label))
        throw(UnexistingEdgeEx(Edge(_nodes[sourceID], _nodes[targetID], label)));

    removeEdge(_nodes[sourceID], _nodes[targetID], label);
}


void MatrixGraph::removeEdge(Node * source, Node * target, const Label& label)
{
    _numberOfEdges--;
    int sourceIndex = nodeToIndex(source);
    int targetIndex = nodeToIndex(target);
    assert(sourceIndex != -1 && targetIndex != -1);

    bool found = false;
    // at this point we are dealing with valid source and target
    for (list<Edge*>::iterator k = _matrix[sourceIndex][targetIndex].begin(); !found && k != _matrix[sourceIndex][targetIndex].end(); ++k)
    {
        if ((found = ((*k)->getLabel() == label)))
        {
            // free the memory allocated for that edge
            delete *k;
            // remove that element (= pointer in this case) from the list
            _matrix[sourceIndex][targetIndex].erase(k);
        }
    }
    notifyObservers();
}

void MatrixGraph::recreateFrom(const Graph& other)
{
    // calling recreateFrom with itself doesn't change anything
    if(&other == this)
        return ;
    _name = other.getName();
    list<Edge*> tempEdges;
    // remove any previous existing nodes
    removeNodes();
    // copy the nodes
    vector<Node*> otherNodes = other.getNodes(); // the vector will be created only once
    for (unsigned i = 0; i < otherNodes.size(); ++i)
        /* add each node from the other graph to the graph,
           addNode(otherNodes[i]) will NOT allocate new node so we want to call the
           one with a const Node& as the parameter*/
        addNode(*otherNodes[i]);
    // for each node
    for (unsigned i = 0; i < _numberOfNodes; ++i)
    {
        // get the outgoing Edges
        tempEdges = other.getOutgoingEdges(otherNodes[i]);
        // add those edges to the destination graph (this one)
        for (list<Edge*>::const_iterator j = tempEdges.begin(); j != tempEdges.end(); ++j)
        {
            Edge tempEdge = **j;
            tempEdge.setSource(_nodes[(other.nodeToIndex((*j)->getSource()))]);
            tempEdge.setTarget(_nodes[(other.nodeToIndex((*j)->getTarget()))]);
            addEdge(tempEdge);
        }
    }
}

list<Node*> MatrixGraph::getNeighbours(Node* node) const
{
    list<Node*> neighbours;
    int sourceIndex = Graph::nodeToIndex(node);
    assert(sourceIndex != -1); // TODO: replace with exception
    for(unsigned i = 0; i < _matrix[sourceIndex].size(); ++i)
    {
        if(!_matrix[sourceIndex][i].empty()) // if there is at least one edge from source to i
            neighbours.push_back(_nodes[i]);
    }
    return neighbours;
}

list<Edge*> MatrixGraph::getOutgoingEdges(Node* node) const
{
    list<Edge*> outgoingEdges;
    int sourceIndex = Graph::nodeToIndex(node);
    assert(sourceIndex != -1);
    // save the size in a temporary variable so we don't have to get the size every time
    unsigned size = _matrix[sourceIndex].size();
    for (unsigned i = 0; i < size; ++i)
    {
        // in each cell in the matrix there can be more edges.
        for (list<Edge*>::const_iterator k = _matrix[sourceIndex][i].begin(); k != _matrix[sourceIndex][i].end(); ++k)
            outgoingEdges.push_back(*k);
    }

    return outgoingEdges;
}

list<Edge*> MatrixGraph::getIncomingEdges(Node *node) const
{
    list<Edge*> incomingEdges;
    int sourceIndex = Graph::nodeToIndex(node);
    assert(sourceIndex != -1);
    // save the size in a temporary variable so we don't have to get the size every time
    unsigned size = _matrix[sourceIndex].size();
    for (unsigned j = 0; j < size; ++j)
    {
        // in each cell in the matrix there can be more edges.
        for (list<Edge*>::const_iterator k = _matrix[j][sourceIndex].begin(); k != _matrix[j][sourceIndex].end(); ++k)
            incomingEdges.push_back(*k);
    }

    return incomingEdges;
}


void MatrixGraph::deleteEdgesBetweenNodes(int i, int j)
{
    // update the number of edges;
    _numberOfEdges -= _matrix[i][j].size();

    // delete all the edges from i to j
    for (list<Edge*>::const_iterator k = _matrix[i][j].begin(); k != _matrix[i][j].end(); ++k)
        delete *k;
    // also remove all the pointers
    _matrix[i][j].clear();
}

// helpfunction to easely extend the matrix by n. using this function and this function only will ensure that the matrix stays a squar
void MatrixGraph::extendMatrix(int n)
{
    vector<list<Edge*> > newLine;
    list<Edge*> emptyList;
    while(n > 0)
    {
        // increase the size of the matrix, add one cell to each line
        for(unsigned i = 0; i < _matrix.size(); ++i)
        {
            // add one element on each row
            _matrix[i].push_back(emptyList);
            // prepare to line to add
            newLine.push_back(emptyList);
        }
        newLine.push_back(emptyList); // bottom right corner of the matrix

        _matrix.push_back(newLine); // add the new line that we have created to the matrix
        // one less to extend
        newLine.clear();
        emptyList.clear();
        --n;
    }
    assert(_matrix.size() == _matrix[0].size());
}

void MatrixGraph::retractMatrix(int index)
{
    assert(_matrix[0].size() == _matrix.size());
    // remove that line and kolom of the matrix to update the matrix
    for (unsigned i = 0; i < _matrix.size(); ++i)
        _matrix[i].erase(_matrix[i].begin() + index); // remove colom in each line
    _matrix.erase(_matrix.begin() + index); // remove line
    assert(_matrix[0].size() == _matrix.size());
}

bool MatrixGraph::isUniqueEdge(const Edge& edge) const
{
    int sourceIndex = nodeToIndex(edge.getSource());
    int targetIndex = nodeToIndex(edge.getTarget());
    // this is a help function that is called only from other functions within MatrixGraph, a bad source/target is caused by errorneous programming
    assert(sourceIndex != -1 && targetIndex != -1);
    for (list<Edge*>::const_iterator k = _matrix[sourceIndex][targetIndex].begin(); k != _matrix[sourceIndex][targetIndex].end(); ++k)
    {
        if((*k)->getLabel() == edge.getLabel())
            return false;
    }
    return true;
}

bool MatrixGraph::edgeExists(Node* source, Node* target, const Label& label) const
{
    int sourceIndex = nodeToIndex(source);
    int targetIndex = nodeToIndex(target);
    assert(sourceIndex != -1 && targetIndex != -1);
    // if there are no edges from the source to the target
    if (_matrix[sourceIndex][targetIndex].empty())
        return false;
    else // do the real search
        for (list<Edge*>::const_iterator k = _matrix[sourceIndex][targetIndex].begin(); k != _matrix[sourceIndex][targetIndex].end(); ++k)
        {
            if((*k)->getLabel() == label)
                return true;
        }

    return false;
}

string MatrixGraph::toStringID() const
{
    ostringstream resultString;
    unsigned maxDepth = 0;

    resultString << "GrapName: " << _name.c_str() << "\n";
    resultString << "nodes["<< _numberOfNodes << "]: ";
    // nodes:
    for (unsigned i = 0; i < _numberOfNodes; ++i)
        resultString << i << ", ";

    for (unsigned i = 0; i < _numberOfNodes; ++i)
        for (unsigned j = 0; j < _numberOfNodes; ++j)
            if(maxDepth < _matrix[i][j].size())
                maxDepth = _matrix[i][j].size();

    for(unsigned tempCounter = 0; tempCounter < maxDepth || tempCounter == 0; ++tempCounter)
    {
        resultString << "\nlayer " << tempCounter << ": \n";
        for (unsigned i = 0; i < _matrix.size(); ++i)
        {
            for (unsigned j = 0 ; j < _matrix[i].size(); ++j)
            {
                // if tempCounter (current Layer) is more than the deepest index of a cell
                if(_matrix[i][j].size() <= tempCounter)
                    resultString << ".";
                else
                {
                    // go to the right layer

                    list<Edge*>::const_iterator k = _matrix[i][j].begin();
                    for (int temp = tempCounter; k != _matrix[i][j].end() && temp > 0; ++k)
                        --temp;

                    if ((*k)->getLabel().getLabelString() == "")
                        resultString << " ";
                    else
                        resultString << (*k)->getLabel();
                }
            }
            resultString << "\n";
        }

    }
    return resultString.str();

}

string MatrixGraph::toString() const
{
    ostringstream resultString;
    unsigned maxDepth = 0;

    resultString << "GrapName: " << _name.c_str() << "\n";
    resultString << "nodes["<< _numberOfNodes << "]: ";
    // nodes:
    for (unsigned i = 0; i < _numberOfNodes; ++i)
        resultString << _nodes[i]->getLabel() << ", ";

    for (unsigned i = 0; i < _numberOfNodes; ++i)
        for (unsigned j = 0; j < _numberOfNodes; ++j)
            if(maxDepth < _matrix[i][j].size())
                maxDepth = _matrix[i][j].size();

    for(unsigned tempCounter = 0; tempCounter < maxDepth || tempCounter == 0; ++tempCounter)
    {
        resultString << "\nlayer " << tempCounter << ": \n";
        for (unsigned i = 0; i < _matrix.size(); ++i)
        {
            for (unsigned j = 0 ; j < _matrix[i].size(); ++j)
            {
                // if tempCounter (current Layer) is more than the deepest index of a cell
                if(_matrix[i][j].size() <= tempCounter)
                    resultString << ".";
                else
                {
                    // go to the right layer

                    list<Edge*>::const_iterator k = _matrix[i][j].begin();
                    for (int temp = tempCounter; k != _matrix[i][j].end() && temp > 0; ++k)
                        --temp;

                    if ((*k)->getLabel().getLabelString() == "")
                        resultString << " ";
                    else
                        resultString << (*k)->getLabel();
                }
            }
            resultString << "\n";
        }

    }
    return resultString.str();
}

// friend, this function is not efficient and should only be used in debugmode
QDebug operator<<(QDebug dbg, const MatrixGraph& other)
{
    dbg.nospace() << other.toString().c_str();
    return dbg;
}

ostream& operator<<(ostream& dbg, const MatrixGraph& other)
{
    cout << other.toString();
    return dbg;
}
