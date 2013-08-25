/*
  Author: Jeroen Vaelen
  Description: Visitor that finds the shortest possible route in a graph that visits every node exactly once (Traveling Salesman Problem)
  */

#ifndef TSPVISITOR_H
#define TSPVISITOR_H

#include "visitor/algorithmvisitor.h"
#include <vector>
#include <list>
#include "graph/graphComp/rgb.h"

class Node;
class Edge;

class TSPVisitor : public AlgorithmVisitor
{
public:
    TSPVisitor();
    ~TSPVisitor();
    void visit(Graph& graph);
    // do one iteration of the algorithm -- check if one path is hamiltonian
    void iterationStep(Graph& graph);
    string getName() const { return "Traveling Salesman Problem"; }
    bool isFinished() const;

private:
    // check whether there is an edge between source and target, edge is set to this edge if there is one, else NULL
    // the reason we do not use Graph::edgeExists() is because the label does not matter now
    bool isEdge( Node* source, Node* target, Edge** edge);
    // edges that have been colored in the proces of computing a cycle
    vector<Edge*> _coloredEdges;
    // bool to indicate that a cycle has been found
    bool _done;
    // init function
    void initialise(Graph& graph);
    // current permutation, to make sure we don't get out of bounds
    vector<Node*> _permutation;
    // calculates next permutation and returns true if it's a hamiltonian cycle
    bool permutateAndValidate();
    // vector that holds the indices of the current permutation's nodes in the graph.nodes vector
    vector<int> _positions;
    // vector that holds the original node's colors, used if we reset the colors
    vector<RGB> _nodeColors;
    // vector that holds the original edge's colors, used if we reset the colors
    vector<RGB> _edgeColors;
    // checks if the permutation has doubles
    bool doubles(vector<int>& perm);
    // bool that checks if any drawing action has been done, if not we iterate again so it does not look like the application might be freezing
    bool _drew;

    // vector that holds the currently shortest route
    vector<Edge*> _route;
    // the sum of the route's  costs
    int _lowestCost;
    // checks if the graph is weighted
    bool isWeighted(Graph &graph);
    // returns the cost of a couple of edges
    int cost(vector<Edge*> route) const;


};
#endif // TSPVISITOR_H
