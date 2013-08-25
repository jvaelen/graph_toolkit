/*
  Author: Jeroen Vaelen
  Description: This Property visitor checks whether a graph is connected (every node is connected to all other nodes)
  */

#ifndef COMPLETEVISITOR_H
#define COMPLETEVISITOR_H

#include "visitor/propertyvisitor.h"

class CompleteVisitor : public PropertyVisitor
{
public:
    CompleteVisitor();
    ~CompleteVisitor();

    void visit(Graph& graph);
    string getName() const { return "Complete"; }

private:
    bool *_table;
    void setBoolTable(int numberOfElements);
    PropertyVisitor::propertyResult validateBoolTable(int numberOfElements, int exclude);

};

#endif // COMPLETEVISITOR_H
