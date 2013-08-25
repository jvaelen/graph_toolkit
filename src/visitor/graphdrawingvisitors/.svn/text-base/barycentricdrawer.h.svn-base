#ifndef BARYCENTRICDRAWER_H
#define BARYCENTRICDRAWER_H

#include "visitor/algorithmvisitor.h"
#include "graph/graphComp/point.h"
#include <list>

class Node;
class Edge;

class BarycentricDrawer : public AlgorithmVisitor
{
public:
    BarycentricDrawer();
    void visit(Graph& graph);

    // do one iteration of the aglorithm
    void iterationStep(Graph& graph);
    string getName() const { return "Barycentric -  William T. Tutte";}
private:
    void init(Graph &graph);
    bool isLocked(Node* node) const;
    void calculateCenterOfGraph(Graph& graph);
    void calculateOuterNodes(Graph& graph);
    // the treshold, if the movement falls below this value, the algoritm is terminated
    double _treshold;
    static const unsigned _lockedNumberOfNodes = 4;
    unsigned long _oldNumberOfEdges;
    unsigned long _oldNumberOfNodes;
    Point _center;
    list<Node*> _lockedNodes;
    map<Node*, list<Edge*> > _outgoingEdges;
    map<Node*, list<Edge*> > _incommingEdges;
    vector<Node*> _nodes;
    Graph* _oldGraph;
};

#endif // BARYCENTRICDRAWER_H
