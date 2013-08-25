/*
  Author: Jeroen Vaelen
  Description: This Property visitor checks whether a graph is undirected (every outgoing edge has an incoming edge with the same label)
  */

#ifndef UNDIRECTEDVISITOR_H
#define UNDIRECTEDVISITOR_H

#include "visitor/propertyvisitor.h"

class UndirectedVisitor : public PropertyVisitor
{
public:
    UndirectedVisitor();

    void visit(Graph& graph);
    string getName() const { return "Undirected"; }

};

#endif // UNDIRECTEDVISITOR_H
