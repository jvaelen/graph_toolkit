/*
 Author: Balazs Nemeth
 Description: implements an adjacencyList matrix
     */

#ifndef MATRIXGRAPH_H
#define MATRIXGRAPH_H

#include <QDebug>
#include <list>
#include <vector>

#include "graph.h"

using namespace std;
/* adjacencyList matrix looks like this:

                target
            +---+---+---+
            |   |   |   |
            +---+---+---+
   source   |   |   |   |
            +---+---+---+
            |   | x |   |
            +---+---+---+

            x means that there is a edge from source index 2 tot target index 1
            */


class MatrixGraph : public Graph
{
public:
    MatrixGraph();
    // copy constructor -- also used for other Graph types (ListGraph, HybridGraph)
    MatrixGraph(const Graph& other);
    // create a MatrixGrgaph using a graphtuple. The vectors are created by the superclass
    MatrixGraph(const IntegerMatrix& integerMatrix);
    // creates an empty MatrixGraph with a name, the baseclass handles this
    MatrixGraph(string name) : Graph(name) {}
    // clean up
    ~MatrixGraph();
    // returns this graph in the form of a graphTuple
    IntegerMatrix getIntegerMatrix() const;
    // adds a node to the graph without any edges connecting to this node. Note that after calling this function the graph is disconnected
    void addNode(const Node& other = Node());
    // removes all nodes from the graph, including the edges that start or end here. Afcter calling this function the graph is empty because there can be no edges without nodes
    void removeNodes();
    // removes the node by id
    void removeNode(unsigned id);
    void removeEdges();
    // removes the edge between from and target with Label label
    void removeEdge(Node * source, Node * target, const Label& label);
    // remove edge by id
    void removeEdge(unsigned sourceID, unsigned targetID, const Label& label);
    // same as copyconstructor
    void recreateFrom(const Graph& other);
    // recreates the graph form an integermatrix
    void recreateFrom(const IntegerMatrix& integerMatrix);
    // returns the neighbours of node, an alternative version of this function is availible in the baseclass that calls this function
    list<Node*> getNeighbours(Node* node) const;
    list<Edge*> getOutgoingEdges(Node* node) const;
    list<Edge*> getIncomingEdges(Node* node)  const;
    void accept(Visitor& v) {v.visit(*this);}
    // use labels to create edges, calls the function from the baseclass after checking if the labels are valid
    void addEdge(unsigned sourceID, unsigned targetID, const Label& label);
    void addEdge(const Edge& edge);
    bool isUniqueEdge(const Edge& edge) const;
    bool edgeExists(Node* source, Node* target, const Label& label) const;
    //friends

    // public because GUI uses these functions
    // see the base class for comments
    void addNode(Node* node);
    // adds an edge with a label between
    void addEdge(Node* source, Node * target, const Label& label = string(""));
    // removes a node including the edges(!) that are connected to this node
    void removeNode(Node* node);


    friend QDebug operator<<(QDebug dbg, const MatrixGraph& other);
    friend ostream& operator<<(ostream& dbg, const MatrixGraph& other);

    string toString() const;
    string toStringID() const;
protected:
private:
    // delets ALL the edges between 2 nodes, this will also take care of memory management
    void deleteEdgesBetweenNodes(int i, int j);
    // helpfunction that extends the matrix by n
    void extendMatrix(int n = 1);
    /* helpfunction that removes one colomn and one row from the matrix given by the index.
       retractMatrix will only change the matrix strucurally. In other words edges wont be deleted*/
    void retractMatrix(int index);
private:
    vector<vector<list<Edge*> > > _matrix;
};

#endif // MATRIXGRAPH_H
