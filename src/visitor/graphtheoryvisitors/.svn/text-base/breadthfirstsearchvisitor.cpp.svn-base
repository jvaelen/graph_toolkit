#include "breadthfirstsearchvisitor.h"
#include <QDebug>
#include <list>
#include "graph/hybridgraph.h"
#include "graph/graphComp/node.h"
#include "graph/graphComp/edge.h"

BreadthFirstSearchVisitor::BreadthFirstSearchVisitor() : SearchVisitor()
{
}

void BreadthFirstSearchVisitor::init(Graph* graph)
{
    setUpGraph(graph);
    _workingNode = _current;
    _breadthQueue.push(_workingNode);
    _current->setColor(RGB::colorGreen());
}

string BreadthFirstSearchVisitor::getName() const
{
    return "Breadth First Search";
}

void BreadthFirstSearchVisitor::iterationStep(Graph &graph)
{
    // if this is the first time we visit the graph, init it for the algorithm to work
    if (_workingGraph != &graph || end())
        init(&graph);
    // this is an else test because in the init phase, the first node gets selected
    else
        next();
}

void BreadthFirstSearchVisitor::visit(Graph& graph)
{
    init(&graph);
    while (!end())
        next();
}

void BreadthFirstSearchVisitor::next()
{
    // stop condition used when we change the working node by popping from the queue and calling next() again
    // in the end _workingNode will be a NULL node
    if (_workingNode == NULL)
        return;

    list<Edge*> currentOutgoing = _workingGraph->getOutgoingEdges(_workingNode);

    // var used to check whether some node has been chosen as the new current
    int lowID = -1;

    // ga alle edges af en als ge er gene kunt currenten de volgende in de queue pakken en deleten
    for (list<Edge*>::iterator it = currentOutgoing.begin(); it != currentOutgoing.end(); ++it)
    {
        // if we have not visited the edge yet AND there was no good previous edge to a node or this node has a smaller id
        if (!_visited[_workingGraph->nodeToIndex((*it)->getTarget())] && (lowID == -1 || _workingGraph->nodeToIndex( (*it)->getTarget()) < lowID ))
            lowID = _workingGraph->nodeToIndex( (*it)->getTarget());
    }

    // node has no edges or no correct (unseen) edges
    if (lowID == -1)
    {
        // if the queue is empty, we cannot continue with a new workingNode --
        // this is also safety test (graphs with only nodes and no edges and no if (!bfs.end()) test before a bfs.next())
        if (end())
            return;
        else
        {
            // there is an item waiting in the queue -- change the working node
            _breadthQueue.pop();
            _workingNode = _breadthQueue.front();
            next();
        }
    }
    // change current (not working node, we stay working on the same because new edges were found!)
    else
    {
        _visited[lowID] = true;
        _breadthQueue.push(_graphNodes[lowID]);
        _current = _graphNodes[lowID];
        _current->setColor(RGB::colorGreen());
    }
}

bool BreadthFirstSearchVisitor::end() const
{
    return (_breadthQueue.empty());
}
