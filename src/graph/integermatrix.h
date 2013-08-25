/*
 Author: Balazs Nemeth
 Description: integerMatrix is a class that represents a graph in a primitive way. It has a nxn (with n the number of nodes) matrix of integers.
     the integers stand for the multiplicity of the edges. 0 stands for no edges between the given nodes.
     */

#ifndef INTEGERMATRIX_H
#define INTEGERMATRIX_H


#include <vector>
#include <utility>
#include <QDebug>

#include "graphComp/label.h"


// only references are used
class Node;
class Edge;

class IntegerMatrix
{
public:
    IntegerMatrix();
    // default copy constructor
    // default constructor will be used
    // default destructor onyl vectors are used and nothing is allocated

    // addNode, this class will take care of it (ie where and if it will be added in the matrix of integers)
    void addNode(const Node& node);
    // adds ONE edge between the given nodes. If the source or target nodes have a label that doesn't exist, an exception will be thrown
    void addEdge(const Node& source, const Node& target);
    // adds the edge given in the parameter. It will use the edge.getSource() and edge.getTarget() to add the edge in the right position in the matrix.
    void addEdge(const Edge& edge);
    // removes ONE edge between the source, target nodes
    void removeEdge(const Node& source, const Node& target);
    // removes the node including all it's edges
    void removeNode(const Node& node);
    // returns true if the node with id, unsigned id, has at least one edge
    bool nodeHasEdge(unsigned id) const;
    // converts the integermatrix to
    void toUndirected();
    /* returns a reference to the matrix that holds all the integers that has been constructed with the add and remove operations.
        This is the matrix that gets parsed outside of this class*/
    const vector<vector<unsigned> >& getMatrix() const {return _matrix;}
    // reserves the gives size. The result reserved matrix will be a square matrix. This method is used for efficiency
    void reserveSize(int n);
    // the dimension of the square matrix equals the number of nodes
    unsigned getNumberOfNodes() const { return _matrix.size();}
    unsigned getNumberOfEdges() const;
    // friend
    friend QDebug operator<<(QDebug dbg, const IntegerMatrix& other);
private:
    // extends the matrix with zeros
    void extendMatrix(int n = 1);
    // returns the index of the label in the _nodes vector., -1 for invalid label
    unsigned labelToIndex(const Label& label) const;
private:
    // _matrix is the matrix of integers that is build during adding and removing of nodes and edges
    vector<vector<unsigned> > _matrix;
    // _nodes is used to keep track of what nodes are already inserted in the matrix
    vector<Label> _nodes;
};


#endif // INTEGERMATRIX_H
