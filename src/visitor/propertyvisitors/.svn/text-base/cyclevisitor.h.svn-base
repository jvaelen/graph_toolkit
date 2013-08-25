/*
  Author: Jeroen Vaelen
  Description: This visitor determines whether a graph has a cycle.
               The algorithm makes use of the strongly connected components algorithm,
               this is the most efficient way, with complexity  O(|V| + |E|)
               */

#ifndef CYCLEVISITOR_H
#define CYCLEVISITOR_H

#include "visitor/propertyvisitor.h"
#include <deque>
#include <vector>

class Node;

class CycleVisitor : public PropertyVisitor
{
public:

    CycleVisitor();
    void visit(Graph& graph);
    string getName() const { return "Cycle"; }

private:

    // this function calls strongconnect for every unvisited node
    void tarjan(Graph & graph);

    // recursive function used to build the stack and determine the strongly connected components
    void strongconnect(Graph* g, Node* v, int i);

//    // index used to determine when a node was visited
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
    // Strongly Connected Component partition set
    vector<vector<Node*> > _SCC;

};

#endif // CYCLEVISITOR_H
