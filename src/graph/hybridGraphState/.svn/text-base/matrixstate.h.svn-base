/*
 Author: Balazs Nemeth
 Description: This class represents one of the states. Functions like addNode(label) are left out because everything is done in the context (HybridGraph)
     */
#ifndef MATRIXSTATE_H
#define MATRIXSTATE_H

#include "graph/graphComp/edge.h"
#include "graph/matrixgraph.h"
#include "graph/hybridGraphState/hybridgraphstate.h"

// private inheritance from MatrixGraph. The functions from MatrixGraph can only be called indirectly using the functions inherited from HybridGraphState
class MatrixState : public HybridGraphState
{
public:
    // the first 2 constructors will be delegated to the baseclass, nothing special happens here
    MatrixState() {_graph = new MatrixGraph();}
    MatrixState(string name) {_graph = new MatrixGraph(name);}
    // this constructor can change the state in the state pattern
    MatrixState(HybridGraph* context, const Graph& other);
    // copy the state from another state, notify the context if the state has to change
    MatrixState(HybridGraph* context, const HybridGraphState& other);
    MatrixState(const IntegerMatrix& other) {_graph = new MatrixGraph(other);}
    // the first set of functions change the structure of the graph and must be tested on the criterium that would invoke the state change
    void addNode(HybridGraph *context, const Node& other);
    void removeNodes(HybridGraph* context);
    void removeNode(HybridGraph* context, unsigned index);
    void removeNode(HybridGraph* context, unsigned long ID);
    void removeNode(HybridGraph* context, Node* node);
    void addEdge(HybridGraph* context, unsigned sourceIndex, unsigned targetIndex, const Label& label);
    void addEdge(HybridGraph* context, unsigned long sourceID, unsigned long targetID, const Label& label);
    void addEdge(HybridGraph* context, const Edge& edge);
    void removeEdges(HybridGraph* context);
    void removeEdge(HybridGraph* context, unsigned sourceIndex, unsigned targetIndex, const Label& label);
    void removeEdge(HybridGraph* context, unsigned long sourceID, unsigned long targetID, const Label& label);
    void recreateFrom(HybridGraph* context, const Graph& other);
    void recreateFrom(HybridGraph* context, const IntegerMatrix& other);
    void removeEdge(HybridGraph* context, Node* source, Node* target, const Label& label);
    HybridGraphState* clone() const {return new MatrixState(*this);}
    // friends
    friend QDebug operator<<(QDebug dbg, const MatrixState& other);
private:
    // the next 2 private functions check if the matrix should switch to another state, if so they will make the switch accordingly
    void switchState(HybridGraph* context, float e, float n);
    // returns true if the we should switch to ListState, this is a helpfunction and isn't really necessary and that's why it's not present in the base class
    void switchState(HybridGraph* context);
};

#endif // MATRIXSTATE_H
