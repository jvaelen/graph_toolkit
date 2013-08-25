#include "propertyvisitor.h"
#include "graph/graph.h"

PropertyVisitor::PropertyVisitor()
{
    _workingGraph = NULL;
    _focusGraph = NULL;
}

void PropertyVisitor::removeFromOpenGraphs(Graph* graph)
{
    if (_openGraphs.count(graph))
        _openGraphs.erase(graph);
    notifyObservers();
}

void PropertyVisitor::addToOpenGraphs(Graph& graph)
{
    // add to map if it does not exist yet
    if (_openGraphs.count(&graph) == 0)
        _openGraphs[&graph] = PropertyVisitor::UNDEFINED;
}

PropertyVisitor::propertyResult PropertyVisitor::getPropertyResult()
{
    if (_focusGraph)
        return _openGraphs[_focusGraph];
    else
        return PropertyVisitor::UNDEFINED;
}

void PropertyVisitor::setFocusGraph(Graph *graph)
{
    _focusGraph = graph;
    addToOpenGraphs(*_focusGraph);
    notifyObservers();
}

void PropertyVisitor::visitFocusGraph()
{
    _focusGraph->accept(*this);
}
