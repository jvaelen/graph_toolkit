#include "hampathvisitor.h"
#include "graph/graphComp/node.h"
#include "graph/graphComp/edge.h"
#include "graph/graph.h"
#include <vector>
#include <list>
#include "exception/invalidgraph.h"

HamPathVisitor::HamPathVisitor() : AlgorithmVisitor()
{
    _pathFound = false;
    _finished = false;
}

HamPathVisitor::~HamPathVisitor()
{
}

bool HamPathVisitor::isFinished() const
{
    return _finished;
}

void HamPathVisitor::visit(Graph &graph)
{
    initialise(graph);
    while(!isFinished())
        iterationStep(graph);
}

bool HamPathVisitor::doubles(vector<int>& perm)
{
    for (unsigned i =0; i < perm.size(); ++i)
        for (unsigned j = i+1; j < perm.size(); ++j)
            if (perm[i] == perm[j])
                return true;
    return false;
}

void HamPathVisitor::iterationStep(Graph &graph)
{
    // input graph has no nodes
    if (graph.getNodes().empty())
        return;

    // new graph
    if (&graph != _graph || _finished)
        initialise(graph);

    if (_pathFound)
    {
        // last permutation was a path,color the nodes green
        for (unsigned i = 0; i < _permutation.size(); ++i)
            _permutation[i]->setColor(RGB::colorGreen());
        // color the edge colors green
        for (unsigned i = 0; i < _coloredEdges.size(); ++i)
            _coloredEdges[i]->setColor(RGB::colorGreen());
        _finished = true;
    }
    else
    {
        _drew = false;
        while (!_drew)
        {
            // reset the color of the edges
            for (unsigned i = 0; i < _coloredEdges.size(); ++i)
                _coloredEdges[i]->setColor(_edgeColors[i]);
            // go to the next valid permutation
            _pathFound = permutateAndValidate();
        }
    }

}

void HamPathVisitor::initialise(Graph& graph)
{
    _graph = &graph;
    _permutation.clear();
    _positions.clear();
    const vector<Node*>& nodes = _graph->getNodes();
    // set our first permutation
    // start at the first candidate
    for (unsigned i = 0; i < nodes.size()-1; ++i)
        _permutation.push_back(nodes[i]);
    _permutation.push_back(nodes[nodes.size()-2]);
    for (unsigned i = 0; i < _permutation.size(); ++i)
        _positions.push_back(graph.nodeToIndex(_permutation[i]));
    // set original colors
    for (unsigned i = 0; i < nodes.size(); ++i)
        _nodeColors.push_back(nodes[i]->getColor());
    _coloredEdges.clear();
    _edgeColors.clear();
    _finished = false;
    _pathFound = false;
}


bool HamPathVisitor::permutateAndValidate()
{
    _coloredEdges.clear();
    _edgeColors.clear();

    const vector<Node*>& nodes = _graph->getNodes();

    // keep on permutating until we get one without doubles
    do
    {
        _positions[_positions.size()-1]++;

        for ( unsigned i = _positions.size()-1; i > 0; i-- )
        {
            // overflowing, reset last position
            if (_positions[i] >= static_cast<int>(_positions.size()))
            {
                int dif = _positions[i] - (_positions.size() -1);
                _positions[i-1] += dif;
                _positions[i] = 0; // start value
            }
        }

        // reached the end, graph has no hamiltonian path
        if (_positions[0] >= static_cast<int>(_positions.size()))
        {
            _finished = true;
            // reset the color
            vector<Node*> nodes = _graph->getNodes();
            for (unsigned i = 0; i < nodes.size(); ++i)
                nodes[i]->setColor(_nodeColors[i]);
            for (unsigned i = 0; i < _coloredEdges.size(); ++i)
                _coloredEdges[i]->setColor(_edgeColors[i]);
            throw InvalidGraph("The graph does not contain an Hamiltonian path.", 1);
        }

        // set the new permutation and set it's color to orange because it's a candidate path
        for (unsigned i = 0; i < _positions.size(); ++i)
        {
            _permutation[i] = nodes[_positions[i]];
            _permutation[i]->setColor(RGB::colorOrange());
        }
    } while  (doubles(_positions) );


    // passed to isEdge
    Edge* edge;
    unsigned size = nodes.size();
    // check if the permutation is a hamiltonian path
    // verification stage
    for (unsigned i = 0; i < size - 1; ++i)
    {
        // if (_path[i], _path[i+1]) is not an edge
        if ( !isEdge(_permutation[i], _permutation[i+1], &edge) )
            return false;

        // if there is an edge, color it
        else
        {
            _drew = true;
            _edgeColors.push_back(edge->getColor());
            edge->setColor(RGB::colorOrange());
            _coloredEdges.push_back(edge);
        }
    }

    // if we get here, it was a hamiltonian path!
    return true;
}

bool HamPathVisitor::isEdge(Node* source, Node* target, Edge** edge)
{
    *edge = NULL;
    list<Edge*> edges = _graph->getOutgoingEdges( source );
    // check if their is an edge between source and target
    for (list<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        if ( (*it)->getTarget() == target )
        {
            *edge = *it;
            return true;
        }
    }
    return false;
}
