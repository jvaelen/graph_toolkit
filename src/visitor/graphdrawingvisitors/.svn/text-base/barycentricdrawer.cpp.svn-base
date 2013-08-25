#include <QDebug>
#include <vector>

#include "graph/graph.h"
#include "barycentricdrawer.h"
#include "exception/invalidgraph.h"
using namespace std;

BarycentricDrawer::BarycentricDrawer()
{
    _treshold = 3.0f;
    _oldGraph = NULL;
    _oldNumberOfEdges = 0;
    _oldNumberOfNodes = 0;
}

void BarycentricDrawer::visit(Graph &graph)
{
    _finished = false;
    vector<Point> lastPositions;
    lastPositions.resize(graph.getNodes().size());

    // while not finished, do an iterationstep
    while (!_finished)
    {
        // save all the positions
        for (unsigned i = 0; i < graph.getNodes().size(); ++i)
            lastPositions[i] = graph.getNodes()[i]->getCoords();
        // do an iteration
        iterationStep(graph);
        // start by thinking that we're finished
        _finished = true;
        // check is the positions haven't changed so much anymore
        for (unsigned i = 0; i < lastPositions.size(); ++i)
        {
            if(lastPositions[i].distance(graph.getNodes()[i]->getCoords()) > _treshold)
                _finished = false;
        }
    }
}

void BarycentricDrawer::init(Graph &graph)
{
    if (_finished)
    {
        _oldNumberOfEdges = 0;
        _oldNumberOfNodes = 0;
        _lockedNodes.clear();
        _outgoingEdges.clear();
        _incommingEdges.clear();
        _nodes.clear();
        _oldGraph = 0;
        _finished = false;
    }
    if (&graph != _oldGraph || graph.getNumberOfEdges() != _oldNumberOfEdges || graph.getNumberOfNodes() != _oldNumberOfNodes)
    {
        if (graph.getNumberOfNodes() < _lockedNumberOfNodes)
            throw InvalidGraph("This algorithm needs at least 4 nodes, have: " + Label(graph.getNumberOfNodes()).getLabelString());
        _oldGraph = &graph;
        _oldNumberOfEdges = graph.getNumberOfEdges();
        _oldNumberOfNodes = graph.getNumberOfNodes();
        _finished = false;
        _nodes = graph.getNodes();

        /* for each node we get the outgoingEdges because these operations are
        computationaly intense and wont change while the algoritme executes */
        for (unsigned i = 0; i < _nodes.size(); ++i)
        {
            _outgoingEdges.insert(pair<Node*, list<Edge*> >(_nodes[i], graph.getOutgoingEdges(_nodes[i])));
            _incommingEdges.insert(pair<Node*, list<Edge*> >(_nodes[i], graph.getIncomingEdges(_nodes[i])));
        }
        calculateOuterNodes(graph);
    }
}

void BarycentricDrawer::iterationStep(Graph &graph)
{
    init(graph);
    const vector<Node*>& nodes = graph.getNodes();
    vector<Point> points;
    points.resize(nodes.size());
    Point Origin(_center);
    int counter = 0;
    int degree;
    // create the iterators that we'll need outside the look for efficiency
    list<Edge*>::const_iterator j;
    vector<Node*>::const_iterator i;
    list<Edge*>& outGoingEdges = _outgoingEdges.at(_nodes[0]);
    list<Edge*>& incomingEdges = _incommingEdges.at(_nodes[0]);
    Point sumVector;
    for (i = nodes.begin(); i != nodes.end(); ++i)
    {
        if (!(isLocked(*i) || (*i)->getColor() == RGB::colorSelection()))
        {
            // set the sumvector to (0,0)
            sumVector.resetToZeros();
            degree = 0;

            // load from what we've cashed in the init function of this algorithm
            outGoingEdges = _outgoingEdges.at(*i);
            incomingEdges = _incommingEdges.at(*i);

            for (j = outGoingEdges.begin(); j != outGoingEdges.end(); ++j, degree++)
                sumVector = sumVector + (*j)->getTarget()->getCoords() - Origin;
            for (j = incomingEdges.begin(); j != incomingEdges.end(); ++j, degree++)
                sumVector = sumVector + (*j)->getSource()->getCoords() - Origin;

            points[counter] = Origin + sumVector/(double)degree;
        }
        counter++;
    }

    counter = 0;
    for(i = nodes.begin(); i != nodes.end(); ++i)
    {
        if (!(isLocked(*i) || (*i)->getColor() == RGB::colorSelection()))
            (*i)->setCoords(points[counter]);
        counter++;
    }
}

void BarycentricDrawer::calculateCenterOfGraph(Graph& graph)
{
    int leftMost    = graph.getNodes()[0]->getCoords().getX();
    int rightMost   = graph.getNodes()[0]->getCoords().getX();
    int topMost     = graph.getNodes()[0]->getCoords().getY();
    int bottomMost  = graph.getNodes()[0]->getCoords().getY();
    // calculate the center of the graph
    for (unsigned i  = 0; i < graph.getNodes().size(); ++i)
    {
        if (graph.getNodes()[i]->getCoords().getX() > rightMost)
            rightMost   = graph.getNodes()[i]->getCoords().getX();
        if (graph.getNodes()[i]->getCoords().getX() < leftMost)
            leftMost    = graph.getNodes()[i]->getCoords().getX();
        if (graph.getNodes()[i]->getCoords().getY() > topMost)
            topMost     = graph.getNodes()[i]->getCoords().getY();
        if (graph.getNodes()[i]->getCoords().getY() < bottomMost)
            bottomMost  = graph.getNodes()[i]->getCoords().getY();
    }
    _center.setX((leftMost + rightMost)/2);
    _center.setY((topMost + bottomMost)/2);
}

bool BarycentricDrawer::isLocked(Node* node) const
{
    for (list<Node*>::const_iterator i = _lockedNodes.begin(); i != _lockedNodes.end(); ++i)
        if (node == *i)
            return true;
    return false;
}

void BarycentricDrawer::calculateOuterNodes(Graph& graph)
{
    // get rid of anything that we might have calculated in a previous iteration.
    _lockedNodes.clear();
    calculateCenterOfGraph(graph);

    float distanceToCenter;
    bool found;
    // find the new nodes
    for (unsigned i = 0; i < graph.getNodes().size(); ++i)
    {
        if (_lockedNodes.size() == _lockedNumberOfNodes)
        {
            found = false;
            distanceToCenter = graph.getNodes()[i]->getCoords().distance(_center);
            for (list<Node*>::iterator j = _lockedNodes.begin(); !found && j != _lockedNodes.end(); ++j)
            {
                if ((found = ((*j)->getCoords().distance(_center) < distanceToCenter)))
                {
                    _lockedNodes.erase(j);
                    _lockedNodes.push_front(graph.getNodes()[i]);
                }
            }
        }
        else
        {
            _lockedNodes.push_front(graph.getNodes()[i]);
        }
    }
}
