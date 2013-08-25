/*
  Author: Jeroen Vaelen
  Description: This visitor determines all strongly connected components of a graph using Tarjan's algorithm.
               Complexity: O(|V| + |E|)
               */

#ifndef STRONGLYCONNECTEDCOMPONENTSVISITOR_H
#define STRONGLYCONNECTEDCOMPONENTSVISITOR_H

#include "visitor/algorithmvisitor.h"
#include <deque>
#include <vector>

class Node;

class StronglyConnectedComponentsVisitor : public AlgorithmVisitor
{

public:

    // constructor & destructor
    StronglyConnectedComponentsVisitor();
    ~StronglyConnectedComponentsVisitor();

    // computes the SCC and colors them
    void visit(Graph& graph);

    // computes the SCC and colors them one SCC per iteration
    void iterationStep(Graph& graph);

    // returns true if we have colored all SCC
    bool isFinished() const;

    string getName() const { return "Strongly Connected Components"; }


private:

    // this function calls strongconnect for every unvisited node
    // if color is passed as true, it will also do the coloring, otherwise not
    void computeComponents(Graph & graph, bool color);

    // recursive function used to build the stack and determine the strongly connected components
    void strongconnect(Graph* g, Node* v, int i);


    /*** used in strongconnect */

    // index used to determine when a node was visited
    int _index;
    // table that holds the index for every node
    int *_indexTable;
    // table that holds the lowlink for every node
    int *_lowlinkTable;
    // init the tables according to the graph nodes size
    void initTables( int size );
    // the normal algorithm uses a stack that holds DFS paths, but we use a deque because we need a isInStack(Node*) function
    // we threat the deque as a stack
    deque<Node*> S;
    // help method used by strongconnect to check if a node is in S
    bool isInStack(Node* node) const;
    // colors all the SCC sets in a unique color
    void colorComponents();


    /*** build in strongconnect, result of algorithm */

    // vector containing vectors of SCC
    // { {1,2} , {3,5,6}  } would mean that {1,2} and {3,5,6} form SCC
    vector<vector<Node*> > _SCC;
    // frees components before we start again
    void freeComponents();


    /*** used in iterationstep */

    // what element of _SCC do we have to color now
    int _currentSCCToColor;
    // bool to make sure we don't compute the SCC again every iteration!
    bool _initDone;
    // computes SCC
    void initForIterations();
    // |_SCC|
    unsigned _numberOfSCC;
    // colors a particular SCC
    void colorComponent( int comp );


};

#endif // STRONGLYCONNECTEDCOMPONENTSVISITOR_H
