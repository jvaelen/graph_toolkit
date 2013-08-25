#include "weightedvisitor.h"
#include "graph/graph.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"
#include <vector>
#include <list>

WeightedVisitor::WeightedVisitor()
{
}

void WeightedVisitor::visit(Graph &graph)
{
    // check if the graph is already open, if not add to map
    addToOpenGraphs(graph);

    // we set the bool _propertyResult to be true, in the algorithm we will only set this to false when we encounter a failure,
    // so if after all for loops the bool is still true, we know the property is true
    _openGraphs[&graph] = TRUEVAL;

    // visit all nodes from the graph and check if their outgoing edges all have number labels
    vector<Node*> nodes = graph.getNodes();
    unsigned size = nodes.size();
    for (unsigned i = 0; i < size; ++i)
    {
        list<Edge*> outgoing = graph.getOutgoingEdges(nodes[i]);
        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
        {
            // if this edge is no cost, the property is false
            if (!(*it)->getLabel().isCost())
                _openGraphs[&graph] = FALSEVAL;
        }
    }

    notifyObservers();
}
