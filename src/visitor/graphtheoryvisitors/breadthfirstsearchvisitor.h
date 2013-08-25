/*
   Author: Jeroen Vaelen
   Description: Visitor that traverses through a graph using breadth first search
   */

#ifndef BREADTHFIRSTSEARCHVISITOR_H
#define BREADTHFIRSTSEARCHVISITOR_H

#include "visitor/algorithmvisitor.h"
#include "visitor/graphtheoryvisitors/searchvisitor.h"
#include <queue>

class BreadthFirstSearchVisitor : public AlgorithmVisitor, public SearchVisitor
{
public:
    BreadthFirstSearchVisitor();

    void visit(Graph& Graph);

    // this function can be called to do 1 iterationstep of the algorithm,
    // allowing us to animate (redraw the nodes after each iterationstep) the algorithm
    void iterationStep(Graph& graph);
    bool isFinished() const { return end(); }
    string getName() const;

    // iterate one step ahead
    void next();
    // have we ran through the complete graph
    bool end() const;

private:
    queue<Node*> _breadthQueue;
    Node* _workingNode;

    void init(Graph* graph);


};

#endif // BREADTHFIRSTSEARCHVISITOR_H
