#include "cyclevisitor.h"
#include "visitor/graphtheoryvisitors/stronglyconnectedcomponentsvisitor.h"
#include <QDebug>
#include "graph/graph.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"


CycleVisitor::CycleVisitor() : PropertyVisitor()
{
}

void CycleVisitor::visit(Graph& graph)
{
    // check if the graph is already open, if not add to map
    addToOpenGraphs(graph);

    // no cycle unless we find one
    _openGraphs[&graph] = FALSEVAL;

    // compute the SCC of the graph (build _SCC)
    tarjan(graph);

    bool stop = false;

    // run through SSC and check if any of the components has a size greater or equal than 2, if so there is a cycle
    for (unsigned i = 0; i < _SCC.size() && !stop; ++i)
    {
        if (_SCC[i].size() >= 2)
        {
            _openGraphs[&graph] = TRUEVAL;
            stop = true;
        }
    }

    notifyObservers();
}


void CycleVisitor::tarjan(Graph& graph)
{
    _SCC.clear();
    _index = 0;

    vector<Node*> nodes = graph.getNodes();
    int size = nodes.size();

    initTables(size);

    for ( int i = 0; i < size; ++i )
    {
        // if nodes[i] has no index
        if ( _indexTable[i] == -1 )
            strongconnect( &graph, nodes[i], i );
    }

}

void CycleVisitor::strongconnect(Graph* g, Node* v, int i)
{
    // Set the depth index for v to the smallest unused index
    _indexTable[i] = _index;
    _lowlinkTable[i] = _index;
    _index = _index +1;
    S.push_front(v);

    list<Edge*> outgoing = g->getOutgoingEdges(v);
    // Consider successors of v
    // For each (v, w) in E
    for (list<Edge*>::iterator it = outgoing.begin() ; it != outgoing.end(); ++it)
    {
        // current w
        Node* w = (*it)->getTarget();
        // if w's index is undefined
        if ( _indexTable[g->nodeToIndex(w)] == -1)
        {
            // Successor w has not yet been visited; recurse on it
            strongconnect(g, w, g->nodeToIndex(w));
            // v.lowlink := min(v.lowlink, w.lowlink)
            _lowlinkTable[g->nodeToIndex(v)] = min( _lowlinkTable[g->nodeToIndex(v)], _lowlinkTable[g->nodeToIndex(w)] );
        }
        // else if ( w is in S )
        else if ( isInStack(w) )
        {
            // Successor w is in stack S and hence in the current SCC
            // v.lowlink := min(v.lowlink, w.index)
            _lowlinkTable[g->nodeToIndex(v)] = min(_lowlinkTable[g->nodeToIndex(v)], _indexTable[g->nodeToIndex(w)] );
        }
    }

    // If v is a root node, pop the stack and generate a SCC
    if (_lowlinkTable[g->nodeToIndex(v)] == _indexTable[g->nodeToIndex(v)])
    {
        Node * w;
        // start a new strongly connected component
        vector<Node*> scc;
        do
        {
            w = S.front();
            S.pop_front();
            // add w to current strongly connected component
            scc.push_back(w);
        } while (!(w==v));

        // add the current strongly connected component to the vector of strongly connected component
        _SCC.push_back(scc);
    }

}

void CycleVisitor::initTables( int size )
{
    _indexTable = new int[size];
    _lowlinkTable = new int[size];

    // set default values to -1 (no index/lowlink yet)
    for ( int i = 0 ; i < size ; ++i)
    {
        _indexTable[i] = -1;
        _lowlinkTable[i] = -1;
    }
}

bool CycleVisitor::isInStack(Node* w) const
{
    for ( deque<Node*>::const_iterator it = S.begin(); it != S.end(); ++it)
    {
        if ( (*it) == w )
            return true;
    }
    return false;
}

