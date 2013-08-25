#include "tspvisitor.h"
#include "graph/graphComp/node.h"
#include "graph/graphComp/edge.h"
#include "graph/graph.h"
#include <vector>
#include <list>
#include "exception/invalidgraph.h"

TSPVisitor::TSPVisitor() : AlgorithmVisitor()
{
    _done = false;
    _finished = false;
    _drew = false;
    _lowestCost = -1;
}

TSPVisitor::~TSPVisitor()
{
}

bool TSPVisitor::isFinished() const
{
    return _finished;
}

void TSPVisitor::visit(Graph &graph)
{
    initialise(graph);
    while (!isFinished())
        iterationStep(graph);
}

bool TSPVisitor::doubles(vector<int>& perm)
{
    for (unsigned i =0; i < perm.size(); ++i)
        for (unsigned j = i+1; j < perm.size(); ++j)
            if (perm[i] == perm[j])
                return true;
    return false;
}

void TSPVisitor::iterationStep(Graph &graph)
{
    // new graph
    if (&graph != _graph || _finished)
        initialise(graph);

    if (_done)
    {
        // color the nodes
        for (unsigned i = 0; i < _permutation.size(); ++i)
            _permutation[i]->setColor(RGB::colorGreen());
        // color the route
        for (unsigned i = 0; i < _coloredEdges.size(); ++i)
            _route[i]->setColor(RGB::colorGreen());
        _finished = true;
    }
    else
    {
        _drew = false;
        while (!_drew && !_done)
        {
            // reset the color of the edges
            for (unsigned i = 0; i < _coloredEdges.size(); ++i)
                _coloredEdges[i]->setColor(_edgeColors[i]);
            // go to the next valid permutation
            _done = permutateAndValidate();
        }
    }

}

void TSPVisitor::initialise(Graph& graph)
{
    // input graph has no nodes
    if (graph.getNodes().empty())
        return;
    if (!isWeighted(graph))
        throw (InvalidGraph("Graph is not weighted",2));
    _graph = &graph;
    _permutation.clear();
    _positions.clear();
    const vector<Node*>& nodes = _graph->getNodes();
    // set our first permutation
    for (unsigned i = 0; i < nodes.size(); ++i)
        _permutation.push_back(nodes[0]);
    for (unsigned i = 0; i < _permutation.size(); ++i)
        _positions.push_back(graph.nodeToIndex(_permutation[i]));
    // set original colors
    for (unsigned i = 0; i < nodes.size(); ++i)
        _nodeColors.push_back(nodes[i]->getColor());
    _coloredEdges.clear();
    _edgeColors.clear();
    _finished = false;
    _done = false;
    _lowestCost = -1;
}


bool TSPVisitor::permutateAndValidate()
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

        // reached the end, the lowest cost route is now final
        if (_positions[0] >= static_cast<int>(_positions.size()))
        {
            // throw an exception if no route was found
            if (_lowestCost == -1)
            {
                // reset the color
                vector<Node*> nodes = _graph->getNodes();
                for (unsigned i = 0; i < nodes.size(); ++i)
                    nodes[i]->setColor(_nodeColors[i]);
                for (unsigned i = 0; i < _coloredEdges.size(); ++i)
                    _coloredEdges[i]->setColor(_edgeColors[i]);
                throw InvalidGraph("The graph does not contain any Hamiltonian cycle", 1);
            }

            // we are done
            return true;
        }

        // set the new permutation and set it's color to orange because it's a candidate cycle
        for (unsigned i = 0; i < _positions.size(); ++i)
        {
            _permutation[i] = nodes[_positions[i]];
            _permutation[i]->setColor(RGB::colorOrange());
        }
    } while  (doubles(_positions) );


    // passed to isEdge
    Edge* edge;
    unsigned size = nodes.size();
    // check if the permutation is a hamiltonian cycle
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

    // this checks if the last node is also connected to the first
    if ( !isEdge(_permutation[size-1], _permutation[0], &edge) )
        return false;

    // else color it
    else
    {
        _drew = true;
        _edgeColors.push_back(edge->getColor());
        edge->setColor(RGB::colorOrange());
        _coloredEdges.push_back(edge);
    }

    // if we get here, it was a hamiltonian cycle, check if it's a shorter one
    if ( cost(_coloredEdges) < _lowestCost || _lowestCost == -1)
    {
        _route.clear();
        // new optimal route
        for (unsigned i = 0; i < _route.size(); ++i)
            _route.push_back(_coloredEdges[i]);
        _lowestCost = cost(_coloredEdges);
    }

    // we aren't done yet
    return false;
}

int TSPVisitor::cost(vector<Edge*> route) const
{
    int sum = 0;
    // somation of all label costs
    for (unsigned i = 0; i < route.size(); ++i)
        sum += atoi(route[i]->getLabel().getLabelString().c_str());
    return sum;
}

bool TSPVisitor::isEdge(Node* source, Node* target, Edge** edge)
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

bool TSPVisitor::isWeighted(Graph &graph)
{
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
                return false;
        }
    }
    return true;
}

//#include "tspvisitor.h"
//#include "graph/graphComp/node.h"
//#include "graph/graphComp/edge.h"
//#include "graph/graph.h"
//#include <vector>
//#include <list>
//#include "exception/invalidgraph.h"

//TSPVisitor::TSPVisitor() : AlgorithmVisitor()
//{
//    _done = false;
//    _finished = false;
//    _drew = false;
//    _lowestCost = -1;
//}

//TSPVisitor::~TSPVisitor()
//{
//}

//bool TSPVisitor::isFinished() const
//{
//    return _finished;
//}

//void TSPVisitor::visit(Graph &graph)
//{
//    initialise(graph);
//    while (!isFinished())
//        iterationStep(graph);
//}

//bool TSPVisitor::doubles(vector<int>& perm)
//{
//    for (unsigned i =0; i < perm.size(); ++i)
//        for (unsigned j = i+1; j < perm.size(); ++j)
//            if (perm[i] == perm[j])
//                return true;
//    return false;
//}

//void TSPVisitor::iterationStep(Graph &graph)
//{
//    // new graph
//    if (&graph != _graph || _finished)
//        initialise(graph);

//    if (_done)
//    {
//        // color the nodes
//        for (unsigned i = 0; i < _permutation.size(); ++i)
//            _permutation[i]->setColor(RGB::colorGreen());
//        // color the route
//        for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//            _route[i]->setColor(RGB::colorGreen());
//        _finished = true;
//    }
//    else
//    {
//        _drew = false;
//        while (!_drew && !_done)
//        {
//            // reset the color of the edges
//            for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//                _coloredEdges[i]->setColor(_edgeColors[i]);
//            // go to the next valid permutation
//            _done = permutateAndValidate();
//        }
//    }

//}

//void TSPVisitor::initialise(Graph& graph)
//{
//    // input graph has no nodes
//    if (graph.getNodes().empty())
//        return;
//    if (!isWeighted(graph))
//        throw (InvalidGraph("Graph is not weighted",2));
//    _graph = &graph;
//    _permutation.clear();
//    _positions.clear();
//    const vector<Node*>& nodes = _graph->getNodes();
//    // set our first permutation
//    for (unsigned i = 0; i < nodes.size(); ++i)
//        _permutation.push_back(nodes[0]);
//    for (unsigned i = 0; i < _permutation.size(); ++i)
//        _positions.push_back(graph.nodeToIndex(_permutation[i]));
//    // set original colors
//    for (unsigned i = 0; i < nodes.size(); ++i)
//        _nodeColors.push_back(nodes[i]->getColor());
//    _coloredEdges.clear();
//    _edgeColors.clear();
//    _finished = false;
//    _done = false;
//    _lowestCost = -1;
//}


//bool TSPVisitor::permutateAndValidate()
//{
//    _coloredEdges.clear();
//    _edgeColors.clear();

//    const vector<Node*>& nodes = _graph->getNodes();

//    // keep on permutating until we get one without doubles
//    do
//    {
//        _positions[_positions.size()-1]++;

//        for ( unsigned i = _positions.size()-1; i > 0; i-- )
//        {
//            // overflowing, reset last position
//            if (_positions[i] >= static_cast<int>(_positions.size()))
//            {
//                int dif = _positions[i] - (_positions.size() -1);
//                _positions[i-1] += dif;
//                _positions[i] = 0; // start value
//            }
//        }

//        // reached the end, the lowest cost route is now final
//        if (_positions[0] >= static_cast<int>(_positions.size()))
//        {
//            // throw an exception if no route was found
//            if (_lowestCost == -1)
//            {
//                // reset the color
//                vector<Node*> nodes = _graph->getNodes();
//                for (unsigned i = 0; i < nodes.size(); ++i)
//                    nodes[i]->setColor(_nodeColors[i]);
//                for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//                    _coloredEdges[i]->setColor(_edgeColors[i]);
//                throw InvalidGraph("The graph does not contain any Hamiltonian cycle", 1);
//            }

//            // we are done
//            return true;
//        }

//        // set the new permutation and set it's color to orange because it's a candidate cycle
//        for (unsigned i = 0; i < _positions.size(); ++i)
//        {
//            _permutation[i] = nodes[_positions[i]];
//            _permutation[i]->setColor(RGB::colorOrange());
//        }
//    } while  (doubles(_positions) );


//    // passed to isEdge
//    Edge* edge;
//    unsigned size = nodes.size();
//    // check if the permutation is a hamiltonian cycle
//    // verification stage
//    for (unsigned i = 0; i < size - 1; ++i)
//    {
//        // if (_path[i], _path[i+1]) is not an edge
//        if ( !isEdge(_permutation[i], _permutation[i+1], &edge) )
//            return false;

//        // if there is an edge, color it
//        else
//        {
//            _drew = true;
//            _edgeColors.push_back(edge->getColor());
//            edge->setColor(RGB::colorOrange());
//            _coloredEdges.push_back(edge);
//        }
//    }

//    // this checks if the last node is also connected to the first
//    if ( !isEdge(_permutation[size-1], _permutation[0], &edge) )
//        return false;

//    // else color it
//    else
//    {
//        _drew = true;
//        _edgeColors.push_back(edge->getColor());
//        edge->setColor(RGB::colorOrange());
//        _coloredEdges.push_back(edge);
//    }

//    // if we get here, it was a hamiltonian cycle, check if it's a shorter one
//    if ( cost(_coloredEdges) < _lowestCost || _lowestCost == -1)
//    {
//        _route.clear();
//        // new optimal route
//        for (unsigned i = 0; i < _route.size(); ++i)
//            _route.push_back(_coloredEdges[i]);
//        _lowestCost = cost(_coloredEdges);
//    }

//    // we aren't done yet
//    return false;
//}

//int TSPVisitor::cost(vector<Edge*> route) const
//{
//    int sum = 0;
//    // somation of all label costs
//    for (unsigned i = 0; i < route.size(); ++i)
//        sum += atoi(route[i]->getLabel().getLabelString().c_str());
//    return sum;
//}

//bool TSPVisitor::isEdge(Node* source, Node* target, Edge** edge)
//{
//    *edge = NULL;
//    list<Edge*> edges = _graph->getOutgoingEdges( source );
//    // check if their is an edge between source and target
//    for (list<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it)
//    {
//        if ( (*it)->getTarget() == target )
//        {
//            *edge = *it;
//            return true;
//        }
//    }
//    return false;
//}

//bool TSPVisitor::isWeighted(Graph &graph)
//{
//    // visit all nodes from the graph and check if their outgoing edges all have number labels
//    vector<Node*> nodes = graph.getNodes();
//    unsigned size = nodes.size();
//    for (unsigned i = 0; i < size; ++i)
//    {
//        list<Edge*> outgoing = graph.getOutgoingEdges(nodes[i]);
//        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
//        {
//            // if this edge is no cost, the property is false
//            if (!(*it)->getLabel().isCost())
//                return false;
//        }
//    }
//    return true;
//}

//#include "tspvisitor.h"
//#include "graph/graphComp/node.h"
//#include "graph/graphComp/edge.h"
//#include "graph/graph.h"
//#include <vector>
//#include <list>
//#include "exception/invalidgraph.h"

//TSPVisitor::TSPVisitor() : AlgorithmVisitor()
//{
//    _done = false;
//    _finished = false;
//    _drew = false;
//    _lowestCost = -1;
//}

//TSPVisitor::~TSPVisitor()
//{
//}

//bool TSPVisitor::isFinished() const
//{
//    return _finished;
//}

//void TSPVisitor::visit(Graph &graph)
//{
//    initialise(graph);
//    while (!isFinished())
//        iterationStep(graph);
//}

//bool TSPVisitor::doubles(vector<int>& perm)
//{
//    for (unsigned i =0; i < perm.size(); ++i)
//        for (unsigned j = i+1; j < perm.size(); ++j)
//            if (perm[i] == perm[j])
//                return true;
//    return false;
//}

//void TSPVisitor::iterationStep(Graph &graph)
//{
//    // new graph
//    if (&graph != _graph || _finished)
//        initialise(graph);

//    if (_done)
//    {
//        // color the nodes
//        for (unsigned i = 0; i < _permutation.size(); ++i)
//            _permutation[i]->setColor(RGB::colorGreen());
//        // color the route
//        for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//            _route[i]->setColor(RGB::colorGreen());
//        _finished = true;
//    }
//    else
//    {
//        _drew = false;
//        while (!_drew && !_done)
//        {
//            // reset the color of the edges
//            for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//                _coloredEdges[i]->setColor(_edgeColors[i]);
//            // go to the next valid permutation
//            _done = permutateAndValidate();
//        }
//    }

//}

//void TSPVisitor::initialise(Graph& graph)
//{
//    // input graph has no nodes
//    if (graph.getNodes().empty())
//        return;
//    if (!isWeighted(graph))
//        throw (InvalidGraph("Graph is not weighted",2));
//    _graph = &graph;
//    _permutation.clear();
//    _positions.clear();
//    const vector<Node*>& nodes = _graph->getNodes();
//    // set our first permutation
//    for (unsigned i = 0; i < nodes.size(); ++i)
//        _permutation.push_back(nodes[0]);
//    for (unsigned i = 0; i < _permutation.size(); ++i)
//        _positions.push_back(graph.nodeToIndex(_permutation[i]));
//    // set original colors
//    for (unsigned i = 0; i < nodes.size(); ++i)
//        _nodeColors.push_back(nodes[i]->getColor());
//    _coloredEdges.clear();
//    _edgeColors.clear();
//    _finished = false;
//    _done = false;
//    _lowestCost = -1;
//}


//bool TSPVisitor::permutateAndValidate()
//{
//    _coloredEdges.clear();
//    _edgeColors.clear();

//    const vector<Node*>& nodes = _graph->getNodes();

//    // keep on permutating until we get one without doubles
//    do
//    {
//        _positions[_positions.size()-1]++;

//        for ( unsigned i = _positions.size()-1; i > 0; i-- )
//        {
//            // overflowing, reset last position
//            if (_positions[i] >= static_cast<int>(_positions.size()))
//            {
//                int dif = _positions[i] - (_positions.size() -1);
//                _positions[i-1] += dif;
//                _positions[i] = 0; // start value
//            }
//        }

//        // reached the end, the lowest cost route is now final
//        if (_positions[0] >= static_cast<int>(_positions.size()))
//        {
//            // throw an exception if no route was found
//            if (_lowestCost == -1)
//            {
//                // reset the color
//                vector<Node*> nodes = _graph->getNodes();
//                for (unsigned i = 0; i < nodes.size(); ++i)
//                    nodes[i]->setColor(_nodeColors[i]);
//                for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//                    _coloredEdges[i]->setColor(_edgeColors[i]);
//                throw InvalidGraph("The graph does not contain any Hamiltonian cycle", 1);
//            }

//            // we are done
//            return true;
//        }

//        // set the new permutation and set it's color to orange because it's a candidate cycle
//        for (unsigned i = 0; i < _positions.size(); ++i)
//        {
//            _permutation[i] = nodes[_positions[i]];
//            _permutation[i]->setColor(RGB::colorOrange());
//        }
//    } while  (doubles(_positions) );


//    // passed to isEdge
//    Edge* edge;
//    unsigned size = nodes.size();
//    // check if the permutation is a hamiltonian cycle
//    // verification stage
//    for (unsigned i = 0; i < size - 1; ++i)
//    {
//        // if (_path[i], _path[i+1]) is not an edge
//        if ( !isEdge(_permutation[i], _permutation[i+1], &edge) )
//            return false;

//        // if there is an edge, color it
//        else
//        {
//            _drew = true;
//            _edgeColors.push_back(edge->getColor());
//            edge->setColor(RGB::colorOrange());
//            _coloredEdges.push_back(edge);
//        }
//    }

//    // this checks if the last node is also connected to the first
//    if ( !isEdge(_permutation[size-1], _permutation[0], &edge) )
//        return false;

//    // else color it
//    else
//    {
//        _drew = true;
//        _edgeColors.push_back(edge->getColor());
//        edge->setColor(RGB::colorOrange());
//        _coloredEdges.push_back(edge);
//    }

//    // if we get here, it was a hamiltonian cycle, check if it's a shorter one
//    if ( cost(_coloredEdges) < _lowestCost || _lowestCost == -1)
//    {
//        _route.clear();
//        // new optimal route
//        for (unsigned i = 0; i < _route.size(); ++i)
//            _route.push_back(_coloredEdges[i]);
//        _lowestCost = cost(_coloredEdges);
//    }

//    // we aren't done yet
//    return false;
//}

//int TSPVisitor::cost(vector<Edge*> route) const
//{
//    int sum = 0;
//    // somation of all label costs
//    for (unsigned i = 0; i < route.size(); ++i)
//        sum += atoi(route[i]->getLabel().getLabelString().c_str());
//    return sum;
//}

//bool TSPVisitor::isEdge(Node* source, Node* target, Edge** edge)
//{
//    *edge = NULL;
//    list<Edge*> edges = _graph->getOutgoingEdges( source );
//    // check if their is an edge between source and target
//    for (list<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it)
//    {
//        if ( (*it)->getTarget() == target )
//        {
//            *edge = *it;
//            return true;
//        }
//    }
//    return false;
//}

//bool TSPVisitor::isWeighted(Graph &graph)
//{
//    // visit all nodes from the graph and check if their outgoing edges all have number labels
//    vector<Node*> nodes = graph.getNodes();
//    unsigned size = nodes.size();
//    for (unsigned i = 0; i < size; ++i)
//    {
//        list<Edge*> outgoing = graph.getOutgoingEdges(nodes[i]);
//        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
//        {
//            // if this edge is no cost, the property is false
//            if (!(*it)->getLabel().isCost())
//                return false;
//        }
//    }
//    return true;
//}

//#include "tspvisitor.h"
//#include "graph/graphComp/node.h"
//#include "graph/graphComp/edge.h"
//#include "graph/graph.h"
//#include <vector>
//#include <list>
//#include "exception/invalidgraph.h"

//TSPVisitor::TSPVisitor() : AlgorithmVisitor()
//{
//    _done = false;
//    _finished = false;
//    _drew = false;
//    _lowestCost = -1;
//}

//TSPVisitor::~TSPVisitor()
//{
//}

//bool TSPVisitor::isFinished() const
//{
//    return _finished;
//}

//void TSPVisitor::visit(Graph &graph)
//{
//    initialise(graph);
//    while (!isFinished())
//        iterationStep(graph);
//}

//bool TSPVisitor::doubles(vector<int>& perm)
//{
//    for (unsigned i =0; i < perm.size(); ++i)
//        for (unsigned j = i+1; j < perm.size(); ++j)
//            if (perm[i] == perm[j])
//                return true;
//    return false;
//}

//void TSPVisitor::iterationStep(Graph &graph)
//{
//    // new graph
//    if (&graph != _graph || _finished)
//        initialise(graph);

//    if (_done)
//    {
//        // color the nodes
//        for (unsigned i = 0; i < _permutation.size(); ++i)
//            _permutation[i]->setColor(RGB::colorGreen());
//        // color the route
//        for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//            _route[i]->setColor(RGB::colorGreen());
//        _finished = true;
//    }
//    else
//    {
//        _drew = false;
//        while (!_drew && !_done)
//        {
//            // reset the color of the edges
//            for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//                _coloredEdges[i]->setColor(_edgeColors[i]);
//            // go to the next valid permutation
//            _done = permutateAndValidate();
//        }
//    }

//}

//void TSPVisitor::initialise(Graph& graph)
//{
//    // input graph has no nodes
//    if (graph.getNodes().empty())
//        return;
//    if (!isWeighted(graph))
//        throw (InvalidGraph("Graph is not weighted",2));
//    _graph = &graph;
//    _permutation.clear();
//    _positions.clear();
//    const vector<Node*>& nodes = _graph->getNodes();
//    // set our first permutation
//    for (unsigned i = 0; i < nodes.size(); ++i)
//        _permutation.push_back(nodes[0]);
//    for (unsigned i = 0; i < _permutation.size(); ++i)
//        _positions.push_back(graph.nodeToIndex(_permutation[i]));
//    // set original colors
//    for (unsigned i = 0; i < nodes.size(); ++i)
//        _nodeColors.push_back(nodes[i]->getColor());
//    _coloredEdges.clear();
//    _edgeColors.clear();
//    _finished = false;
//    _done = false;
//    _lowestCost = -1;
//}


//bool TSPVisitor::permutateAndValidate()
//{
//    _coloredEdges.clear();
//    _edgeColors.clear();

//    const vector<Node*>& nodes = _graph->getNodes();

//    // keep on permutating until we get one without doubles
//    do
//    {
//        _positions[_positions.size()-1]++;

//        for ( unsigned i = _positions.size()-1; i > 0; i-- )
//        {
//            // overflowing, reset last position
//            if (_positions[i] >= static_cast<int>(_positions.size()))
//            {
//                int dif = _positions[i] - (_positions.size() -1);
//                _positions[i-1] += dif;
//                _positions[i] = 0; // start value
//            }
//        }

//        // reached the end, the lowest cost route is now final
//        if (_positions[0] >= static_cast<int>(_positions.size()))
//        {
//            // throw an exception if no route was found
//            if (_lowestCost == -1)
//            {
//                // reset the color
//                vector<Node*> nodes = _graph->getNodes();
//                for (unsigned i = 0; i < nodes.size(); ++i)
//                    nodes[i]->setColor(_nodeColors[i]);
//                for (unsigned i = 0; i < _coloredEdges.size(); ++i)
//                    _coloredEdges[i]->setColor(_edgeColors[i]);
//                throw InvalidGraph("The graph does not contain any Hamiltonian cycle", 1);
//            }

//            // we are done
//            return true;
//        }

//        // set the new permutation and set it's color to orange because it's a candidate cycle
//        for (unsigned i = 0; i < _positions.size(); ++i)
//        {
//            _permutation[i] = nodes[_positions[i]];
//            _permutation[i]->setColor(RGB::colorOrange());
//        }
//    } while  (doubles(_positions) );


//    // passed to isEdge
//    Edge* edge;
//    unsigned size = nodes.size();
//    // check if the permutation is a hamiltonian cycle
//    // verification stage
//    for (unsigned i = 0; i < size - 1; ++i)
//    {
//        // if (_path[i], _path[i+1]) is not an edge
//        if ( !isEdge(_permutation[i], _permutation[i+1], &edge) )
//            return false;

//        // if there is an edge, color it
//        else
//        {
//            _drew = true;
//            _edgeColors.push_back(edge->getColor());
//            edge->setColor(RGB::colorOrange());
//            _coloredEdges.push_back(edge);
//        }
//    }

//    // this checks if the last node is also connected to the first
//    if ( !isEdge(_permutation[size-1], _permutation[0], &edge) )
//        return false;

//    // else color it
//    else
//    {
//        _drew = true;
//        _edgeColors.push_back(edge->getColor());
//        edge->setColor(RGB::colorOrange());
//        _coloredEdges.push_back(edge);
//    }

//    // if we get here, it was a hamiltonian cycle, check if it's a shorter one
//    if ( cost(_coloredEdges) < _lowestCost || _lowestCost == -1)
//    {
//        _route.clear();
//        // new optimal route
//        for (unsigned i = 0; i < _route.size(); ++i)
//            _route.push_back(_coloredEdges[i]);
//        _lowestCost = cost(_coloredEdges);
//    }

//    // we aren't done yet
//    return false;
//}

//int TSPVisitor::cost(vector<Edge*> route) const
//{
//    int sum = 0;
//    // somation of all label costs
//    for (unsigned i = 0; i < route.size(); ++i)
//        sum += atoi(route[i]->getLabel().getLabelString().c_str());
//    return sum;
//}

//bool TSPVisitor::isEdge(Node* source, Node* target, Edge** edge)
//{
//    *edge = NULL;
//    list<Edge*> edges = _graph->getOutgoingEdges( source );
//    // check if their is an edge between source and target
//    for (list<Edge*>::iterator it = edges.begin(); it != edges.end(); ++it)
//    {
//        if ( (*it)->getTarget() == target )
//        {
//            *edge = *it;
//            return true;
//        }
//    }
//    return false;
//}

//bool TSPVisitor::isWeighted(Graph &graph)
//{
//    // visit all nodes from the graph and check if their outgoing edges all have number labels
//    vector<Node*> nodes = graph.getNodes();
//    unsigned size = nodes.size();
//    for (unsigned i = 0; i < size; ++i)
//    {
//        list<Edge*> outgoing = graph.getOutgoingEdges(nodes[i]);
//        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
//        {
//            // if this edge is no cost, the property is false
//            if (!(*it)->getLabel().isCost())
//                return false;
//        }
//    }
//    return true;
//}

