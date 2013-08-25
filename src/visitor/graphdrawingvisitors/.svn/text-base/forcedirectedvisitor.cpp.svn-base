#include "forcedirectedvisitor.h"
#include <QDebug>
#include <cmath>
#include <algorithm>
#include "graph/graphComp/node.h"
#include "graph/graphComp/edge.h"
#include "graph/graph.h"

ForceDirectedVisitor::ForceDirectedVisitor()
{

}

void ForceDirectedVisitor::visit(Graph& graph)
{
    _finished = true;
    for (unsigned i = 0; i < 200; ++i)
        iterationStep(graph);
}

void ForceDirectedVisitor::initIteration(Graph& graph)
{
    _finished = false;
    _graph = &graph;
    _numberOfNodes = graph.getNumberOfNodes();
    _nodes = graph.getNodes();
    _width = calcWidth(_nodes) + 50;
    _height = calcWidth(_nodes) + 50;
    _edges = getEdgesFromNodes(_graph, _nodes);
    // each vertex has 2 vectors: .pos and .disp
    _disp.clear();
    /* because we use a straitline to represent the
            matrix, the frame that we are working in is
            defined by the outermost nodes */
    _area = _width* _height;
    _k = sqrt(_area/_numberOfNodes);
    _t = _width/4;
    _disp.clear();
    _disp.resize(_numberOfNodes);
}

// do one iteration of the aglorithm
void ForceDirectedVisitor::iterationStep(Graph& graph)
{
    // if the graph has no nodes, the algorithm can't work, or in other words it has already finished
    if (!graph.getNumberOfNodes())
    {
        _finished = true;
        return;
    }

    // if the graph changed from the last graph, we have to init variables
    if (_finished || _graph != &graph)
        initIteration(graph);


    /* initialize the _disp vector with Point(0,0)'s, the values need to be calculated every
        iterationstep, so we need to reset these every iteartion */
    for (unsigned i = 0; i < _disp.size(); ++i)
        _disp[i] = Point(0,0);

    float deltaLength;
    float deltaX;
    float deltaY;
    float force;

    unsigned v, u;
    // calculate repulsive forces
    for (v = 0; v < _numberOfNodes; ++v)
    {
        for (u = 0; u < _numberOfNodes; ++u)
        {
            if ( u != v)
            {
                deltaLength = _nodes[v]->getCoords().distance(_nodes[u]->getCoords());
                deltaX = _nodes[v]->getCoords().getX() - _nodes[u]->getCoords().getX();
                deltaY = _nodes[v]->getCoords().getY() - _nodes[u]->getCoords().getY();
                if (deltaLength <= 1.0f)
                    deltaLength = 1.0f;
                force = (_k*_k)/deltaLength*.02;
                // if the forces would be to extreme
                if (force > 100)
                    force = 10;
                _disp[v].setX(_disp[v].getX() + deltaX*force/deltaLength);
                _disp[v].setY(_disp[v].getY() + deltaY*force/deltaLength);
            }
        }
    }

    float dx;
    float dy;

    // calculate attractive forces
    for (list<Edge*>::iterator e = _edges.begin(); e != _edges.end(); ++e)
    {
        Point source = (*e)->getSource()->getCoords();
        Point target = (*e)->getTarget()->getCoords();
        deltaX = source.getX() - target.getX();
        deltaY = source.getY() - target.getY();
        deltaLength = source.distance(target);
        if (deltaLength < 1.0f)
            deltaLength = 1.0f;
        force = (deltaLength*deltaLength)/_k*.04;
        if (force > 100)
            force = 10;
        v = graph.nodeToIndex((*e)->getSource());
        u = graph.nodeToIndex((*e)->getTarget());
        dx = (deltaX/deltaLength)*force;
        dy = (deltaY/deltaLength)*force;
        _disp[v].setX(_disp[v].getX() - dx);
        _disp[v].setY(_disp[v].getY() - dy);
        _disp[u].setX(_disp[u].getX() + dx);
        _disp[u].setY(_disp[u].getY() + dy);
    }

    float x;
    float y;
    Point newCoords;
    // limit max displacement to temperature t and prevent from displacement outside frame
    for (unsigned v = 0; v < _numberOfNodes; ++v)
    {
        if (_nodes[v]->getColor() != RGB::colorSelection())
        {
            newCoords = _nodes[v]->getCoords() + (_disp[v]); /* has to review this line*/
            x = newCoords.getX();
            y = newCoords.getY();
            x = fmin(_width/2 , fmax(-_width/2, x));
            y = fmin(_height/2, fmax(-_height/2, y));
            _nodes[v]->setCoords(Point(x, y));
        }
    }
}

float ForceDirectedVisitor::calcWidth(const vector<Node*>& nodes)
{
    // temp values to squize out more performance
    float x;
    /* first find the node with the minimum and maximum x values,
        dx of these 2 x values is the width of the frame*/
    float xmin, xmax;
    xmin = xmax = nodes.front()->getCoords().getX();
    for (unsigned i = 0; i < nodes.size(); ++i)
    {
        x = nodes[i]->getCoords().getX();
        if (xmin > x)
            xmin = x;
        if (xmax < x)
            xmax = x;
    }
    return (xmax-xmin);
}

float ForceDirectedVisitor::calcHeight(const vector<Node*>& nodes)
{
    // temp values to squize out more performance
    float y;
    /* first find the node with the minimum and maximum x values,
        dx of these 2 x values is the width of the frame */
    float ymin, ymax;
    ymin = ymax = nodes.front()->getCoords().getY();
    for (unsigned i = 0; i < nodes.size(); ++i)
    {
        y = nodes[i]->getCoords().getY();
        if (ymin > y)
            ymin = y;
        if (ymax < y)
            ymax = y;
    }
    return (ymax-ymin);
}



list<Edge*> ForceDirectedVisitor::getEdgesFromNodes(Graph *graph, const vector<Node *>& nodes)
{
    list<Edge*> edgeList;
    list<Edge*> tempList;
    for (unsigned i = 0; i < nodes.size() && edgeList.size() != graph->getNumberOfEdges(); ++i)
    {
        tempList = graph->getOutgoingEdges(nodes[i]);
        for (list<Edge*>::const_iterator j = tempList.begin(); j != tempList.end(); ++j)
        {
            if (!((*j)->isSelfEdge()) && !(alreadyHaveEdge(edgeList, *j)))
                edgeList.push_back(*j);
        }
    }
    return edgeList;
}

bool ForceDirectedVisitor::alreadyHaveEdge(const list<Edge*>& edgeList, Edge* edge)
{
    for (list<Edge*>::const_iterator j = edgeList.begin(); j != edgeList.end(); ++j)
    {
        if (edge->isUndirected((*j)))
            return true;
    }


    return false;
}
