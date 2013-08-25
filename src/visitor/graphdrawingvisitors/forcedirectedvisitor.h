/* Author: Balazs Nemeth
   Description: this forcedirected algorithm is the algorithm of Fruchterman and Reingold */

#ifndef FORCEDIRECTEDVISITOR_H
#define FORCEDIRECTEDVISITOR_H

#include "visitor/algorithmvisitor.h"
#include <vector>
#include <list>
#include "graph/graphComp/point.h"

class Node;
class Edge;

class ForceDirectedVisitor : public AlgorithmVisitor
{
public:
    ForceDirectedVisitor();
    void visit(Graph& graph);

    // do one iteration of the aglorithm
    void iterationStep(Graph& graph);
    string getName() const { return "Force Directed Algorithm - Fruchterman and Reingold";}

private:
    // calculates the area that is occupied by the nodes
    float calcWidth(const vector<Node*>& nodes);
    float calcHeight(const vector<Node*>& nodes);
    void initIteration(Graph& graph);

    // will return a list containing ALL the edges in the graph, calling this function is very expensive, should be done only when REALLY needed
    list<Edge*> getEdgesFromNodes(Graph* graph, const vector<Node*>& nodes);
    bool alreadyHaveEdge(const list<Edge*>& edgeList, Edge* edge);
    Graph* _graph;
    double _width;
    double _height;
    double _k;
    double _area;
    // cooling value
    double _t;
    vector<Point> _disp;
    vector<Node*> _nodes;
    unsigned _numberOfNodes;
    list<Edge*> _edges;
};

#endif // FORCEDIRECTEDGRAPH_H
