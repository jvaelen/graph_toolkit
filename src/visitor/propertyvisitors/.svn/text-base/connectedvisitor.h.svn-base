/*
  Author: Jeroen Vaelen
  Description: This Property visitor checks whether a graph is connected (there is a path between every two nodes)
  */


#ifndef CONNECTEDVISITOR_H
#define CONNECTEDVISITOR_H

#include "visitor/propertyvisitor.h"
#include <vector>

class Node;

class ConnectedVisitor : public PropertyVisitor
{
public:
    ConnectedVisitor();
    ~ConnectedVisitor();

    void visit(Graph& graph);
    string getName() const { return "Connected"; }

private:
    // returns all node's that form a path with n
    vector<Node*> path(Node* n, Graph& g);
    // check if all elements of bool table with length n are false instead of element exclude
    bool validate(bool* table, int n, int exclude);

};

#endif // CONNECTEDVISITOR_H
