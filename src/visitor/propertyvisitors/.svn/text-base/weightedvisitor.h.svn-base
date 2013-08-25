/*
  Author: Jeroen Vaelen
  Description: This Property visitor checks whether a graph is weighted (every edge's label is a cost)
  */

#ifndef WEIGHTEDVISITOR_H
#define WEIGHTEDVISITOR_H

#include "visitor/propertyvisitor.h"

class WeightedVisitor : public PropertyVisitor
{
public:
    WeightedVisitor();

    void visit(Graph& graph);
    string getName() const { return "Weighted"; }
};

#endif // WEIGHTEDVISITOR_H
