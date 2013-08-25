/*
 Author: Balazs Nemeth
 Description: This class is a special in the sense that it uses the statepattern to switch between exactly 2 states,
              namely MatrixState and ListState
              This allows us to use the best implementation for each possible graph.
              For a sparse graph an adjacencyList-list implementation is optimal while for a dense graph a adjacencyList-matrix
              implementation is a better choice.
              Most of the functions (the getters) are delegated to the _state pointer which will take care of the state switching.
              one other thing to note is that the HybridGraph handles the observers and
              functions that change the graph should call notifyObservers()
*/

#ifndef HYBRIDGRAPH_H
#define HYBRIDGRAPH_H

#include "graph.h"
#include "matrixgraph.h"
#include "listgraph.h"
#include "graph/hybridGraphState/hybridgraphstate.h"
#include "graph/integermatrix.h"
#include "graphComp/edge.h"

class MatrixGraph;
class ListGraph;

class HybridGraph : public Graph
{
public:
    // create a hybrid graph from another graph type (copy constructor is implied here).
    HybridGraph(const Graph& other);
    HybridGraph(const IntegerMatrix& other);
    HybridGraph(const string& name);
    HybridGraph();
    // destructor deletes the sate (also deleting the list or matrix graph)
    ~HybridGraph();

    /* the next set of functions are functions that return information about the underlying graph,
        these doens't change the graph itself */
    string getName() const {return _state->getName();}
    void setName(const string& name) {_state->setName(name);}
    // simple delegation to the state
    IntegerMatrix getIntegerMatrix() const {return _state->getIntegerMatrix();}
    // override the getNumberOfNodes and getNumberOfEdges functions so that they can be delegated to the state
    // returns the number of edges of the state, which is the number of edges in the graph
    unsigned getNumberOfEdges() const {return _state->getNumberOfEdges();}
    // returns the number of nodes of the state, which is the number of nodes in the graph
    unsigned getNumberOfNodes() const {return _state->getNumberOfNodes();}
    // returns the last added nodes from the current state
    list<Edge*> getLastAddedEdges() { return _state->getLastAddedEdges(); }
    list<Node*> getLastAddedNodes() { return _state->getLastAddedNodes(); }
    list<Node*> getNeighbours(Node* node) const { return _state->getNeighbours(node); }
    list<Edge*> getOutgoingEdges(Node* node) const {return _state->getOutgoingEdges(node); }
    list<Edge*> getIncomingEdges(Node* node)  const {return _state->getIncomingEdges(node); }
    int nodeToIndex(Node* node) const {return _state->nodeToIndex(node);}
    Node* idToNode(unsigned long id) const {return _state->idToNode(id);}
    // returns a string that gives information about the graph as one would expect
    string toString() const { return _state->toString();}
    string toStringID() const { return _state->toStringID();}
    // returns true if the edge exists in the state
    bool edgeExists(Node* source, Node* target, const Label& label) const { return _state->edgeExists(source,target,label); }
    const vector<Node*>& getNodes() const {return _state->getNodes();}
    string getNodeNameHint() const {return "Node " + Label(_state->getNumberOfNodes()).getLabelString();}


    void setName(string name) {_state->setName(name);}
    // adds a node with a given string
    void addNode(const Node& other = Node());
    // removes nodes
    void removeNodes();
    void removeNode(unsigned id);
    void removeNode(unsigned long ID);
    void removeNode(Node* node);
    // use labels to create edges, calls the function from the baseclass after checking if the labels are valid
    void addEdge(unsigned sourceID, unsigned targetID, const Label& label);
    void addEdge(unsigned long sourceID, unsigned long targetID, const Label& label);
    void addEdge(const Edge& edge);
    // removes edges
    void removeEdges();
    void removeEdge(Node* source, Node* target, const Label& label);
    void removeEdge(unsigned long sourceID, unsigned long targetID, const Label& label);
    void removeEdge(unsigned sourceIndex, unsigned targetIndex, const Label& label);
    // recreates from other graphtypes
    void recreateFrom(const Graph& other);
    void recreateFrom(const IntegerMatrix& other);



    // visitor pattern function, this is the same as in all the other derived functions. The this pointer points to something else in this case
    void accept(Visitor &v) { v.visit(*this); }

    // friends
    friend QDebug operator<<(QDebug dbg, const HybridGraph& other);
    friend ostream& operator<<(ostream& dbg, const HybridGraph& other);
    // the state is a friend class
    friend class HybridGraphState;

protected:
    void deleteOldState();
    // will be called after each functiondelegation to the state that can change the state, when the state desides to change to another state, the old state is recorded here and is deleted right after that using deleteOldState
    void setOldState(HybridGraphState* old) {_oldState = old;}
private:
     // a pointer to the current state. this is used for the statepattern
    HybridGraphState* _state;
    HybridGraphState* _oldState; // last state will be deleted after that adding or removing has been done
};

#endif // HYBRIDGRAPH_H

