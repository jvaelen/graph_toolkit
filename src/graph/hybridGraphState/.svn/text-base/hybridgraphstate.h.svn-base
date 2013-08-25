/*
 Author: Balazs Nemeth
 Description: in the statepattern this is the general state, all the sates inherit from this class and implement all the virtual functions
     */

#ifndef HYBRIDGRAPHSTATE_H
#define HYBRIDGRAPHSTATE_H

#include <string>

#include "graph/graphComp/label.h"
#include "graph/integermatrix.h"
#include "graph/graphComp/edge.h"
#include "graph/graph.h"

// foreward decleration, only using pointers in this headerfile for HybridGraph
class HybridGraph;
class MatrixState;
class ListState;
class Node;

using namespace std;

class HybridGraphState
{
public:
    virtual void removeNodes(HybridGraph* context) = 0;
    virtual void removeNode(HybridGraph* context, unsigned index) = 0;
    virtual void removeNode(HybridGraph* context, unsigned long ID) = 0;
    virtual void removeNode(HybridGraph* context, Node* node) = 0;
    virtual void addEdge(HybridGraph* context, unsigned sourceIndex, unsigned targetIndex, const Label& label) = 0;
    virtual void addEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label) = 0;
    virtual void addEdge(HybridGraph *context, const Edge& edge) = 0;
    virtual void removeEdges(HybridGraph* context) = 0;
    virtual void removeEdge(HybridGraph* context, unsigned sourceIndex, unsigned targetIndex, const Label& label) = 0;
    virtual void removeEdge(HybridGraph *context, unsigned long sourceID, unsigned long targetID, const Label& label) = 0;
    virtual void removeEdge(HybridGraph* context, Node* source, Node* target, const Label& label) = 0;
    virtual void recreateFrom(HybridGraph* context, const Graph& other) = 0;
    virtual void recreateFrom(HybridGraph *context, const IntegerMatrix& other) = 0;
    virtual void addNode(HybridGraph *context, const Node& other) = 0;

    virtual HybridGraphState* clone() const = 0;

    // the next functions are basicly delegated to the underlying class, nothing special has to be done
    string getName() const {return _graph->getName();}
    int nodeToIndex(Node* node) const {return _graph->nodeToIndex(node);}
    Node* idToNode(unsigned long id) const {return _graph->idToNode(id);}
    list<Node*> getLastAddedNodes() {return _graph->getLastAddedNodes();}
    list<Edge*> getLastAddedEdges() {return _graph->getLastAddedEdges();}
    void setName(string name) {_graph->setName(name);}
    unsigned getNumberOfEdges() const {return _graph->getNumberOfEdges();}
    unsigned getNumberOfNodes() const {return _graph->getNumberOfNodes();}
    list<Node*> getNeighbours(Node* node) const {return _graph->getNeighbours(node);}
    list<Edge*> getOutgoingEdges(Node* node) const {return _graph->getOutgoingEdges(node);}
    list<Edge*> getIncomingEdges(Node* node) const {return _graph->getIncomingEdges(node);}
    IntegerMatrix getIntegerMatrix() const {return _graph->getIntegerMatrix();}
    string toString() const {return _graph->toString();}
    string toStringID() const {return _graph->toStringID();}
    const vector<Node*>& getNodes() const {return _graph->getNodes();}
    // returns the underlying graph, used in construction of other states etc.
    Graph* getGraph() const {return _graph;}
    bool edgeExists(Node* source, Node* target, const Label& label) const { return _graph->edgeExists(source, target, label); };
    // friends
    friend QDebug operator<<(QDebug dbg, const HybridGraphState& other);
protected:
    // help function for moving the observers from the old edges to the new edges
    void moveEdgeObservers(HybridGraphState* toState);
    // help function for moving the observers from the old nodes to the new nodes
    void moveNodeObservers(HybridGraphState* toState);
    // collect the edges from a given graph, the edges will be put in the list given as a second parameter, this way, we don't call the copyconstructor of list
    void collectEdges(HybridGraphState* state, list<Edge*>& edges);
    void setState(HybridGraph* context, HybridGraphState* state);
    // simple helpfunction to concatinate 2 lists
    void concatLists(const list<Edge*>& from, list<Edge*>& to);
    // the graphtype that the state encapsulates, using a pointer here to be able to constructo the listGraph when the state is constructed
    Graph* _graph;
};

#endif // HYBRIDGRAPHSTATE_H

