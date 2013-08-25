/*
 Author: Balazs Nemeth
 Description: This class represents one of the states. Functions like addNode(label) are left out because everything is done in the context (HybridGraph)
     */
#ifndef LISTSTATE_H
#define LISTSTATE_H

#include "graph/graphComp/edge.h"
#include "graph/listgraph.h"
#include "graph/hybridGraphState/hybridgraphstate.h"

// ListState has one important member variable, namely the ListGraph that in encapsulates
class ListState : public HybridGraphState
{
public:
    // the first 2 constructors will be delegated to the baseclass, nothing special happens here
    ListState() {_graph = new ListGraph();}
    ListState(string name) {_graph = new ListGraph(name);}
    // this constructor can change the state in the state pattern
    ListState(HybridGraph* context, const Graph& other);
    // copy the state from another state, notify the context if the state has to change
    ListState(HybridGraph* context, const HybridGraphState& other);
    ListState(const IntegerMatrix& other) {_graph = new ListGraph(other);}
    // the first set of functions change the structure of the graph and must be tested on the criterium that would invoke the state change
    void addNode(HybridGraph* context, string nodeLabel);
    void addNode(HybridGraph *context, const Node& other);
    void removeNodes(HybridGraph* context);
    void removeNode(HybridGraph* context, unsigned index);
    void removeNode(HybridGraph* context, unsigned long ID);
    void removeNode(HybridGraph* context, Node* node);
    void addEdge(HybridGraph* context, unsigned sourceIndex, unsigned targetIndex, const Label& label);
    void addEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label);
    void addEdge(HybridGraph *context, const Edge& edge);
    void removeEdges(HybridGraph* context);
    void removeEdge(HybridGraph* context, unsigned sourceID, unsigned targetID, const Label& label);
    void removeEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label);
    void recreateFrom(HybridGraph* context, const Graph& other);
    void recreateFrom(HybridGraph* context, const IntegerMatrix& other);
    void removeEdge(HybridGraph* context, Node* source, Node* target, const Label& label);
    HybridGraphState* clone() const {return new ListState(*this);}
    // friends
    friend QDebug operator<<(QDebug dbg, const ListState& other);
private:
    // the next 2 functions are not const because they can change the state (and delete the instance of this class, although this happens indirectly)
    void switchState(HybridGraph* context, float e, float n);
    // returns true if the we should switch to MatrixState, this is a helpfunction and isn't really necessary and that's why it's not present in the base class
    void switchState(HybridGraph* context);
};

#endif // LISTSTATE_H
