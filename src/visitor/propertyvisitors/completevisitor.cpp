#include "completevisitor.h"
#include <vector>
#include <list>
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"
#include "graph/graph.h"

CompleteVisitor::CompleteVisitor() : PropertyVisitor()
{
    _table = 0;
}

CompleteVisitor::~CompleteVisitor()
{
    delete _table;
}

void CompleteVisitor::visit(Graph &graph)
{
    // add to open graph map if it does not exist yet
    addToOpenGraphs(graph);

    // we set the bool _propertyResult to be true, in the algorithm we will only set this to false when we encounter a failure,
    // so if after all for loops the bool is still true, we know the property is true
    _openGraphs[&graph] = TRUEVAL;

    // seperate variable because we need to pass it more than once
    int numberOfElements = graph.getNumberOfNodes();
    // allocate the bool table with respect to number of nodes of graph
    _table = new bool[numberOfElements];

    vector<Node*> nodes = graph.getNodes();
    list<Edge*> edges;

    int nodeSize = nodes.size();

    // for every node, check if it is Complete with all the other nodes
    // we can stop if _propertyResult gets false
    for (int i = 0; _openGraphs[&graph] && i < nodeSize; ++i)
    {
        // reset bool table
        setBoolTable(numberOfElements);

        // get the outgoing edges for the current node
        edges = graph.getOutgoingEdges(nodes[i]);
        // run through the outgoing edges to check whether the node is Complete to all other nodes
        for ( list<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it )
        {
            // we mark every node that is Complete with our current node
            _table[graph.nodeToIndex( (*it)->getTarget() )] = true;
        }

        // and validate whether the entire table is checked, accept for a self edge
        _openGraphs[&graph] = validateBoolTable(numberOfElements, i);
    }
    notifyObservers();
}

void CompleteVisitor::setBoolTable(int numberOfElements)
{
    for (int i = 0; i < numberOfElements; ++i)
        _table[i] = false;
}


PropertyVisitor::propertyResult CompleteVisitor::validateBoolTable(int numberOfElements, int exclude)
{
    // run through bool table to check whether all positions are true
    // used to check whether a node is Complete to all other nodes
    for (int i = 0; i < numberOfElements; ++i)
    {
        // if _table[i] is false, it means there is no edge between our current node and node i
        if (i != exclude && !_table[i])
            return FALSEVAL;
    }
    return TRUEVAL;
}
