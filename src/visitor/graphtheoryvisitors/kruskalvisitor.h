/*
  Author: Jeroen Vaelen
  Description: Visitor that computes the minimal spanning tree for a weighted graph using Kruskal's algorithm
  */

#ifndef KRUSKALVISITOR_H
#define KRUSKALVISITOR_H

#include "visitor/algorithmvisitor.h"
#include <queue>
#include "graph/graphComp/edge.h"
#include "graph/graph.h"

class Node;
class Edge;

class KruskalVisitor : public AlgorithmVisitor
{
public:
    // constructor & destructor
    KruskalVisitor();
    ~KruskalVisitor() {}

    // computes the MST and colors it
    void visit(Graph& graph);

    // does one iteration in Kruskal's algorithm
    void iterationStep(Graph& graph);

    // returns true if we have computed the minimal spanning tree
    bool isFinished() const;

    string getName() const { return "Kruskal's Algorithm"; }

private:
    // comparision functor that compares two edges' their label and sorts them so that the lowest weight is first in the prio queue
    class compare
    {
    public:
      bool operator() (const Edge* e1, const Edge* e2) const
      {
          return atoi(e1->getLabel().getLabelString().c_str()) > atoi(e2->getLabel().getLabelString().c_str());
      }
    };
    // forest, will ultimately contain the edges of the MST
    vector<Edge*> _forest;
    // cluster that is initialised as { {v1}, {v2}, ... } with vi a vertex of the graph
    vector<vector<Node*> > _cluster;
    // initializes the graph
    void init(Graph& graph);
    // graph has to be weighted
    bool isWeighted(Graph &graph);
    // priority queue that holds all weights with the lowest weight the highest priority element
    priority_queue<Edge*, vector<Edge*>, compare> Q;
    // inits the priority queue with the weights of the edges so that the top is the edge with the lowest weight
    void initQueue(priority_queue<Edge*, vector<Edge*>, compare>& Q);
    // removes all elements from the queue
    void clearQueue();
    // inits the cluster
    void initCluster();
    // checks if two vertices are in the same cluster, also sets cluster1 and cluster2 to the clusters where v1 and v2 are in
    bool sameCluster(Node* v1, Node* v2, unsigned & cluster1, unsigned & cluster2);
    // combines two clusters to one bigger cluster
    void clusterUnion(unsigned cluster1, unsigned cluster2);
    // boolean that tells us if we have initialised our environement yet
    bool initialised;
    // holds the Edge that has been rejected, so that we can deselect it
    Edge* rejected;
    // holds the color of the rejected Edge before we make it orange
    RGB rejcolor;

    QString printClusters();

};

#endif // KRUSKALVISITOR_H
