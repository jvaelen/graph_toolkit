#include "depthfirstsearchvisitor.h"
#include <QDebug>
#include <list>
#include "graph/hybridgraph.h"
#include "graph/graphComp/node.h"
#include "graph/graphComp/edge.h"

DepthFirstSearchVisitor::DepthFirstSearchVisitor() : SearchVisitor()
{
}

void DepthFirstSearchVisitor::init(Graph *graph)
{
    setUpGraph(graph);
    // starting node
    _depthStack.push(_current);
    _current->setColor(RGB::colorGreen());
}

void DepthFirstSearchVisitor::visit(Graph& graph)
{
    init(&graph);
    while (!end())
        next();
}

void DepthFirstSearchVisitor::next()
{
    /* _current == NULL if either:
       1. we have called next() after we have set _current to NULL meaning we have reached the end -> GOOD
       2. we have used invalid data for the initialisation for our graph -> BAD */
    // stop condition
    if (_current == NULL)
    {
        return;
    }

    // get all outgoing from our current
    list<Edge*> currentOutgoing = _workingGraph->getOutgoingEdges(_current);
    unsigned size = currentOutgoing.size();

    // if there is no outgoing edge, pop current from stack and check if there is an element left
    if (size == 0)
    {
        _depthStack.pop();
        // if we are finished, there is no next
        if (end())
            _current = NULL;
        // else we continue with the previous element
        else
        {
            _current = _depthStack.top();
            next();
        }

    }
    else
    {

        // unique init
        int lowID = -1;

        // we know that size > 0 so we can init the lowID with the first edge of the list if it has not been visited already
        if (!_visited[_workingGraph->nodeToIndex((*currentOutgoing.begin())->getTarget())])
            lowID = _workingGraph->nodeToIndex((*currentOutgoing.begin())->getTarget());
        // run through the list of edges to find the edge to the lowest node id, this is going to be the next item we visit
        for (list<Edge*>::iterator it = ++currentOutgoing.begin(); it != currentOutgoing.end(); ++it)
        {
            // if we have not visited this node yet AND if the id has not been changed yet or the id is lower than the current id
            if (!_visited[_workingGraph->nodeToIndex((*it)->getTarget())] && (lowID == -1 || _workingGraph->nodeToIndex( (*it)->getTarget()) < lowID ))
                lowID = _workingGraph->nodeToIndex( (*it)->getTarget());
        }

        // we have not changed lowID -> all edges have already been visited!
        if (lowID == -1)
        {
            // go back again
            _depthStack.pop();
            // no more elements to visit
            if (end())
                _current = NULL;
            // continue with next
            else
            {
                _current = _depthStack.top();
                next();
            }
        }
        else
        {
            _visited[lowID] = true;
            _depthStack.push(_graphNodes[lowID]);
            _current = _graphNodes[lowID];
        }
    }

    if (_current != NULL)
        _current->setColor(RGB::colorGreen());

}

bool DepthFirstSearchVisitor::end() const
{
    return (_depthStack.empty());
}

string DepthFirstSearchVisitor::getName() const
{
    return "Depth First Search";
}

void DepthFirstSearchVisitor::iterationStep(Graph &graph)
{
    // if this is the first time we visit the graph, init it for the algorithm to work
    if (_workingGraph != &graph || end())
        init(&graph);
    // this is an else test because in the init phase, the first node gets selected
    else
        next();
}
