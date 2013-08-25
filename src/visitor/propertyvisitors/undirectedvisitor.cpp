#include "undirectedvisitor.h"
#include <vector>
#include <list>
#include "graph/graph.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"

UndirectedVisitor::UndirectedVisitor() : PropertyVisitor()
{
}

void UndirectedVisitor::visit(Graph& graph)
{
    // check if the graph is already open, if not add to map
    addToOpenGraphs(graph);

    // we set the bool _propertyResult to be true, in the algorithm we will only set this to false when we encounter a failure,
    // so if after all for loops the bool is still true, we know the property is true
    _openGraphs[&graph] = TRUEVAL;

    vector<Node*> nodes = graph.getNodes();
    list<Edge*> outgoing;
    int nodeSize = nodes.size();
    // for every node, get its outgoing edges
    // we can stop if _propertyResult gets false
    for (int i = 0; _openGraphs[&graph] && i < nodeSize; ++i)
    {
        outgoing = graph.getOutgoingEdges(nodes[i]);
        // for every outgoing edge, check if there is an incoming edge
        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
        {
            // if there is an edge from source to target with label, there should also be an edge from target to source with label
            // if not, the graph is not
            if (!graph.edgeExists( (*it)->getTarget(), (*it)->getSource(), (*it)->getLabel()))
                _openGraphs[&graph] = FALSEVAL;
        }
    }

    notifyObservers();
}
