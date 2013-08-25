#include "standardlayoutvisitor.h"
#include "graph/matrixgraph.h"
#include "graph/hybridgraph.h"
#include "graph/listgraph.h"
#include "graph/graph.h"
#include  "graph/graphComp/node.h"
#include <cmath>
#include <QEventLoop>

StandardLayoutVisitor::StandardLayoutVisitor()
{
    // default constructor
    _finished = false;
    _dist = 0;
}

void StandardLayoutVisitor::layoutGraph(Graph& graph)
{
    vector<Node*> nodes = graph.getNodes();
    unsigned numberOfNodes = graph.getNumberOfNodes();
    int squareRoot = round(sqrt(numberOfNodes));
    // set the new positions for the nodes, this will do the actual layout
    for (unsigned i = 0; i < numberOfNodes; ++i)
        nodes[i]->setCoords(Point(squareRoot*120/-2 + (i / squareRoot)*120, squareRoot*120/-2 + (i % squareRoot)*120));
}

void StandardLayoutVisitor::visit(Graph &graph)
{
    layoutGraph(graph);
}

void StandardLayoutVisitor::reset()
{
    _finished = false;
    endPoints.clear();
    originalPoints.clear();
    _sines.clear();
    _cosines.clear();
    _dist = 0;
}

float StandardLayoutVisitor::calculateAngle(float x1, float y1, float x2, float y2)
{
    // if x1 and x2 are the same, meaning that we would devide by zero if we didn't check this
    if (fabs(x2 - x1) < 0.00001)
    {
        // find out if it is 90 or 180 degress
        return ((y2 - y1) > 0)? 2.0*atan(1.0) : 6.0*atan(1.0);
    }
    else
        return atan((double)(endPoints.back().getY() - originalPoints.back().getY())/(double)(endPoints.back().getX() - originalPoints.back().getX()));
}

void StandardLayoutVisitor::iterationStep(Graph &graph)
{
    // if we haven't been itearting on a graph, we reset the algortihm
    if (_finished || &graph != _graph)
    {
        reset();
        // and save a pointer to the new graph
        _graph = &graph;

    }
    vector<Node*> nodes = _graph->getNodes();
    unsigned numberOfNodes = _graph->getNumberOfNodes();
    // if no endpoints have been calculated
        int squareRoot = round(sqrt(numberOfNodes));
    if (endPoints.size() != numberOfNodes)
    {
        reset();
        float angle;
        for (unsigned i = 0; i < numberOfNodes; ++i)
        {
            endPoints.push_back(Point(squareRoot*120/-2 + (i / squareRoot)*120, squareRoot*120/-2 + (i % squareRoot)*120));
            originalPoints.push_back(nodes[i]->getCoords());
            // calculate angle of slopes
            angle = calculateAngle(originalPoints.back().getX(), originalPoints.back().getY(), endPoints.back().getX(), endPoints.back().getY());
            /* we know that tangens(thetha + 180) = tangens(thetha), which gives problems when the angle is actually > 90 or <= -90,
               we solve this by checking on which side the endpoint is, if this is to the left (meaning that the angle between the 2
               points is in the danger zone, we add 180 degrees)*/
            // so we first correct the angle
            if (endPoints.back().getX() < originalPoints.back().getX())
                angle += 4.0*atan(1.0); // 4.0* atan(1.0) gives us pi
            _sines.push_back(sin(angle));
            _cosines.push_back(cos(angle));
        }

    }
    // update the positions of the points going towards the endpoints
    // the distance in each iteration is 5
    _dist += 5;
    bool updated = false;
    for (unsigned i = 0; i < numberOfNodes; ++i)
    {
        Point newPoint(originalPoints[i].getX() + _dist*_cosines[i], originalPoints[i].getY() + _dist*_sines[i]);
        if (endPoints[i].distance(nodes[i]->getCoords()) >= 5 )
        {
            updated = true;
            nodes[i]->setCoords(newPoint);
        }
        else // else the error is small enough to just put the nodes on their endpoints
            nodes[i]->setCoords(endPoints[i]);
    }
    // if no nodes have changed position, we know that the algorithm came to an end
    if (!updated)
    {
        // reset everything that we have calculated
        reset();
        _finished = true;
    }
}
