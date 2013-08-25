/*
 Author: Balazs Nemeth and Jeroen Vaelen
 Description: Graph is an abstract class that, when creating a new type of graph. All the implementation of graph structures
              are derived from this class. Note that because HybridGraph reimplements all the functions
              (delegates the functioncalls to it's states), all the functions in this class are virtual.
     */

#ifndef GRAPH_H
#define GRAPH_H

#include <QDebug>
#include <string>
#include <vector>

#include "graph/integermatrix.h"
#include "graphComp/label.h"
#include "visitor/visitor.h"
#include "observer/subject.h"
#include "graphComp/node.h"
#include "graphComp/edge.h"

// avoid circular dependence
class MatrixGraph;
class ListGraph;

using namespace std;

class Graph : public Subject
{
public:
    Graph();
    Graph(const string& name);
    // copy constructor is needed because we use a vector of Node*
    Graph(const Graph& other);
    // destructor will clear the nodes
    virtual ~Graph();

    /* adds a Node by a pointer to a node. the pointer should be allocated in some other method and then
        passed to this function. The node will then be added to the vector _nodes*/
    virtual void addNode(Node* node);
    // the name functions are virtual because HybridGraph reimplements them so that these 2 functions are delegated it's state
    virtual string getName() const {return _name;}
    virtual void setName(const string& name) {_name = name;}
    // returns the graph in the form of a two tuple (V, E)
    virtual IntegerMatrix getIntegerMatrix() const = 0;
    /* create a new Node with that label and add that using a help function, this function is only called from within graph
        when a node is created by another method, this function is public because the derived classes have to have this function
        publicly defined. Also this function can't be called directly because this class is abract*/
    // adds a node
    virtual void addNode(const Node& node = Node());
    // removes ALL nodes from this graph
    virtual void removeNodes();
    // removes a given node identified by a pointer to that node
    virtual void removeNode(Node* node);
    /* removeNode(Node*) moet niet virtual zijn omdat removeNode(id) al virtual is
       de correcte removeNode(id) gaat gecalled worden en er wordt dan op het juiste object ingewerkt
       op dit object wordt dan removeNode(Node*) gecalled en alles is in orde */
    // removes a node identified by it's label
    // this function is only used in CMD interface
    virtual void removeNode(unsigned id);
    // remove a node by it's ID
    virtual void removeNode(unsigned long ID) {removeNode(idToNode(ID));}
    // returns the nodes. this is used by algorithmes and to create MatrixGraph from ListGraph
    virtual const vector<Node*>& getNodes() const {return _nodes;}
    // accepts an algorithm
    virtual void accept(Visitor& v) = 0;

    // getters

    /* DON'T use the _nodes.size() because edges is a special case and we want to have uniformity,
       these functions are virtual so that hybridGraph override them and delegate them to the states*/
    virtual unsigned getNumberOfNodes() const {return _numberOfNodes; }
    virtual unsigned getNumberOfEdges() const {return _numberOfEdges;}

    // functions for adding and removing edges. These functions are defined in the derived classes which implement edges in their proper way
    // this function is pure virtual because it can't be called from the baseclass
    virtual void addEdge(unsigned sourceIndex, unsigned targetIndex, const Label& label) = 0;
    virtual void addEdge(unsigned long sourceID, unsigned long targetID, const Label& label) { addEdge(Edge(idToNode(sourceID), idToNode(targetID), label));}
    virtual void addEdge(const Edge& edge) = 0;
    virtual void removeEdge(Node* source, Node* target, const Label& label) = 0;
    virtual void removeEdge(unsigned long sourceID, unsigned long targetID, const Label& label) { removeEdge(idToNode(sourceID), idToNode(targetID), label);}
    // delete all the edges
    virtual void removeEdges() = 0;

    // remove an edge, an edge is unique by it's source-target-label combination
    virtual void removeEdge(unsigned , unsigned targetIndex, const Label& label) = 0;

    // a graph should be creatable from other types
    virtual void recreateFrom(const Graph& other) = 0;
    virtual void recreateFrom(const IntegerMatrix& integerMatrix) = 0;
//    // returns true if there are no nodes nor edges
//    virtual bool isEmpty() const {return _numberOfNodes == 0 && _numberOfEdges == 0;}
    // returns the neighbours of a node
    virtual list<Node*> getNeighbours(Node* node) const = 0;
    // translates the label to a node and returns what getNeighbours(Node* node) would return
    list<Node*> getNeighbours(const Label& label) const  {return getNeighbours(labelToNode(label));}
    // returns the outgoing edges of a node
    virtual list<Edge*> getOutgoingEdges(Node* node) const = 0;
    // returns the incoming edges of a node
    virtual list<Edge*> getIncomingEdges(Node* node)  const = 0;
    // public because used in recreateFrom(Graph&)
    virtual int nodeToIndex(Node* node) const;
    // returns a default name for a node, we use label to convert the integer to a label
    virtual string getNodeNameHint() const {return "Node " + Label(_numberOfNodes).getLabelString();}
    // returns the last added nodes, since this function was called, this function isn't const because it clears the _lastAddedNodes vector (virtual because it's reimplemented in HybridGraph)
    virtual list<Node*> getLastAddedNodes();
    virtual list<Edge*> getLastAddedEdges();
    // returns a node that has the id given in the paramter or if that node isn't in the graph, returns NULL
    virtual Node* idToNode(unsigned long id) const;
    virtual string toString() const = 0;
    virtual string toStringID() const = 0;
    // does the graph contain an edge from source to target with Label label
    virtual bool edgeExists(Node* source, Node* target, const Label& label) const = 0;
    friend ostream& operator<<(ostream& dbg, const Graph& other);
    friend QDebug operator<<(QDebug dbg, const Graph& other);

protected:
    // help methods
    // addEdge is properly defined in the deriven classes
    Node* labelToNode(const Label& label) const;
    // returns true if the parameter is a unique label, meaning there is no other node with the same label
    bool isUniqueNode(const Label& label) const;
   // virtual bool isUniqueEdge(Edge edge) const = 0;
private:
    // help methods

protected:
    string _name;
    vector<Node*> _nodes;
    list<Node*> _lastAddedNodes;
    list<Edge*> _lastAddedEdges;
    // keep track of the number of edges and nodes so that when the user of this class asks for these values, they don't have to be calculated.
    unsigned _numberOfEdges;
    unsigned _numberOfNodes;
};

#endif // GRAPH_H
