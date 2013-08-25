#include "searchvisitor.h"
#include <assert.h>
#include "graph/hybridgraph.h"

SearchVisitor::SearchVisitor()
{
    _workingGraph = NULL;
    _current = NULL;
    _visited = NULL;
}

SearchVisitor::~SearchVisitor()
{
    delete _visited;
}

void SearchVisitor::setUpGraph(Graph *graph)
{
    // if this function is called in all constructors, the asserts make sure that we are working with non NULL graphs that have >= 1 nodes
    assert(graph != NULL); // REPLACE WITH THROW(Cannot setup NULL graph)
    assert(graph->getNumberOfNodes() > 0); // REPLACE WITH THROW(Valid graph but no nodes, cannot iterate)
    _workingGraph = graph;
    _graphNodes = graph->getNodes();
    _visited = new bool[_graphNodes.size()];
    // we have asserted that numberOfNodes > 0
    // node we start with is the first node that has been added
    _current = _graphNodes[0];
    _visited[0] = true;
}
