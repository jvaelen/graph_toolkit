#include "stronglyconnectedcomponentsvisitor.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"
#include "graph/graph.h"
// includes needed to generate random RGB values
#include <ctime>
#include <cstdlib>
#include <QVector>

StronglyConnectedComponentsVisitor::StronglyConnectedComponentsVisitor() : AlgorithmVisitor()
{
    // seed
    srand ((unsigned)time(0));
    _currentSCCToColor = 0;
    _index = 0;
    _initDone = false;
}

StronglyConnectedComponentsVisitor::~StronglyConnectedComponentsVisitor()
{
    delete _indexTable;
    delete _lowlinkTable;
}

void StronglyConnectedComponentsVisitor::iterationStep(Graph& graph)
{
    if (&graph != _graph)
    {
        // set working graph to graph
        _graph = &graph;
        // re-initialize
        _initDone = false;
    }

    // computes components (without coloring them) and sets how many SCC the graph has -- this should only be done ONCE
    initForIterations();

    // color one component
    colorComponent( _currentSCCToColor++ );

}

void StronglyConnectedComponentsVisitor::initForIterations()
{
    // if test to make sure we don't compute the SCC again every iteration!
    if (!_initDone)
    {
        computeComponents(*_graph, false);
        _numberOfSCC = _SCC.size();
        _initDone = true;
    }
}

void StronglyConnectedComponentsVisitor::colorComponent( int comp )
{
    if ( comp > static_cast<int>(_numberOfSCC-1) )
    {
        // start over again
        _currentSCCToColor = 1;
        comp = 0;
    }

    unsigned char r = (rand()%256), g = (rand()%256), b = (rand()%256);

    for (unsigned i = 0; i < _SCC[comp].size() ; ++i)
    {
        _SCC[comp][i]->setColor(RGB(r,g,b));
        // current node's outgoing edges
        list<Edge*> currentOutgoing = _graph->getOutgoingEdges(_SCC[comp][i]);
        // color current node's outgoing edge if it is going to a node that is in the same strongly connected component
        for (list<Edge*>::iterator it = currentOutgoing.begin(); it != currentOutgoing.end(); ++it)
            for ( unsigned k = 0; k < _SCC[comp].size(); ++k )
                if ( (*it)->getTarget() ==  _SCC[comp][k])
                    (*it)->setColor(RGB(r,g,b));
    }
}

bool StronglyConnectedComponentsVisitor::isFinished() const
{
    // if the SCC we have to color now is >= the total number of SCC, we are done
    return (_currentSCCToColor >= static_cast<int>(_numberOfSCC));
}

void StronglyConnectedComponentsVisitor::visit(Graph& graph)
{
    if (&graph != _graph)
        _graph = &graph;
    // compute components and color them
    computeComponents(*_graph, true);
}

void StronglyConnectedComponentsVisitor::computeComponents(Graph & graph, bool color)
{
    // reset _SCC
    _SCC.clear();

    vector<Node*> nodes = graph.getNodes();
    int size = nodes.size();

    initTables(size);

    for ( int i = 0; i < size; ++i )
    {
        // if nodes[i] has no index
        if ( _indexTable[i] == -1 )
            strongconnect( &graph, nodes[i], i );
    }

    if ( color )
    // color the different strongly connected components to distinguish them
        colorComponents();
}


// Node v is the i-the node
// Graph is passed to use getOutgoingEdges
void StronglyConnectedComponentsVisitor::strongconnect(Graph* g, Node *v, int i)
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

void StronglyConnectedComponentsVisitor::initTables( int size )
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

bool StronglyConnectedComponentsVisitor::isInStack(Node* w) const
{
    for ( deque<Node*>::const_iterator it = S.begin(); it != S.end(); ++it)
    {
        if ( (*it) == w )
            return true;
    }
    return false;
}

void StronglyConnectedComponentsVisitor::colorComponents()
{
    unsigned char r = (rand()%256), g = (rand()%256), b = (rand()%256);

    // run through all vectors in _SCC vector and give components different colors
    for ( unsigned i = 0 ; i < _SCC.size(); ++i )
    {
        for ( unsigned j = 0; j < _SCC[i].size(); ++j )
        {
            _SCC[i][j]->setColor(RGB(r,g,b));
            // current node's outgoing edges
            list<Edge*> currentOutgoing = _graph->getOutgoingEdges(_SCC[i][j]);
            // color current node's outgoing edge if it is going to a node that is in the same strongly connected component
            for (list<Edge*>::iterator it = currentOutgoing.begin(); it != currentOutgoing.end(); ++it)
                for ( unsigned k = 0; k < _SCC[i].size(); ++k )
                    if ( (*it)->getTarget() ==  _SCC[i][k])
                        (*it)->setColor(RGB(r,g,b));
        }
        r = (rand()%256);
        g = (rand()%256);
        b = (rand()%256);
    }
}
