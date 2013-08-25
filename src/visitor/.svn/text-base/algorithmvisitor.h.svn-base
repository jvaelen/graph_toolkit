/*
  Author: Balazs Nemeth & Jeroen Vaelen
  Description: This class is derived from the abstract class Visitor and forms an interface for all
  algorithm visitors (graph theory algorithms, graph drawing algorithms, ...)
  */

#ifndef ALGORITHMVISITOR_H
#define ALGORITHMVISITOR_H

#include "visitor.h"

class AlgorithmVisitor : public Visitor
{
public:
    AlgorithmVisitor();

    // the three possible graphstructures that can be visited by a visitor
    virtual void visit(Graph& graph) = 0;

    // this function can be called to do 1 iterationstep of the algorithm,
    // allowing us to animate (redraw the nodes after each iterationstep) the algorithm
    virtual void iterationStep(Graph& graph) = 0;
    virtual bool isFinished() const { return _finished; }
    virtual string getName() const = 0;
    void setFinished(bool val) { _finished = val; }

protected:
    // a reference that is kept to the graph that is being worked on
    Graph* _graph;
    // is set when the iterationStep() decides that the algorithm is finished
    bool _finished;

};

#endif // ALGORITHMVISITOR_H
