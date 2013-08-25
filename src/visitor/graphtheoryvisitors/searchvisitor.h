/*
  Author: Jeroen Vaelen
  Description: Abstract base class for depth first search and breadth first search visitors
  */

#ifndef SEARCHVISITOR_H
#define SEARCHVISITOR_H

#include <vector>

class Node;
class Graph;

using namespace std;


class SearchVisitor
{
public:
    // all subclasses should only have a constructor SUB(Graph*)
    // these constructors should call setUpGraph() making sure the initialization is done correctly
    SearchVisitor();
    ~SearchVisitor();

    // iterate one step ahead
    virtual void next() = 0;
    // have we ran through the complete graph
    virtual bool end() const = 0;

    // returns the current graph item (node)
    Node* current() const { return _current; }
    // init function that sets up the iterator
    // called in the constructor of all non abstract subclasses
    void setUpGraph(Graph* graph);

protected:

    Graph* _workingGraph;
    Node* _current;
    vector<Node*> _graphNodes;
    // maps nodes to whether they have or have not been visited yet in the current run
    bool* _visited;

};

#endif // SEARCHVISITOR_H
