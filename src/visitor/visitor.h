/*
 Author: Balazs Nemeth
 Description: Visitor is the base class for all the algorithmes that are used on graphs. It's originated from the visitor patterns
     */

#ifndef VISITOR_H
#define VISITOR_H

#include <string>

class MatrixGraph;
class ListGraph;
class HybridGraph;
class Graph;

using namespace std;

class Visitor
{
public:
    // default constructor suffices
    Visitor();

    // the three possible graphstructures that can be visited by a visitor
    virtual void visit(Graph& graph) = 0;
    virtual string getName() const = 0;
};

#endif // VISITOR_H
