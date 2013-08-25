/*
   Author: Jeroen Vaelen
   Description: Visitor that traverses through a graph using depth first search
   */

#ifndef DEPTHFIRSTSEARCHVISITOR_H
#define DEPTHFIRSTSEARCHVISITOR_H

#include "visitor/algorithmvisitor.h"
#include "visitor/graphtheoryvisitors/searchvisitor.h"
#include <stack>

class DepthFirstSearchVisitor : public AlgorithmVisitor, public SearchVisitor
{
public:
    DepthFirstSearchVisitor();

    void visit(Graph& graph);

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
    stack<Node*> _depthStack;

    void init(Graph* graph);

};

#endif // DEPTHFIRSTSEARCHVISITOR_H
