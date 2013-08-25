/*
  Author: Jeroen Vaelen
  Description: Class where all property visitors will derive from
  */


#ifndef PROPERTYVISITOR_H
#define PROPERTYVISITOR_H

#include "visitor.h"
#include "observer/subject.h"
#include <map>

using std::map;

class PropertyVisitor : public Visitor, public Subject
{

public:

    enum propertyResult { UNDEFINED = -1, FALSEVAL = 0, TRUEVAL = 1 };

    PropertyVisitor();

    virtual void visit(Graph& graph) = 0;
    virtual string getName() const = 0;

    // used by graph tool kit to delete a graph that is deleted by the user
    void removeFromOpenGraphs(Graph * graph);
    // returns the property result of the _focusGraph
    PropertyVisitor::propertyResult getPropertyResult();
    // sets the focus graph
    void setFocusGraph(Graph* graph);
    // visits the focus graph
    void visitFocusGraph();


protected:

    // graph we are currently working on
    Graph* _workingGraph;
    // vector to keep track of all open graphs and their current property result
    map<Graph*, propertyResult> _openGraphs;
    // last visited graph - set in graphtoolkit.cpp
    Graph* _focusGraph;

    // when a visit is being done with a new graph, add it to openGraphs (if it is not already there)
    void addToOpenGraphs(Graph& graph);


};

#endif // PROPERTYVISITOR_H
