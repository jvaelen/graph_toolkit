/* Author: Balazs Nemeth
   Description:Prototypemanager that manages the instances of algorithmes
*/

#ifndef STANDARDLAYOUTVISITOR_H
#define STANDARDLAYOUTVISITOR_H

#include "visitor/algorithmvisitor.h"
#include <vector>
#include "graph/graphComp/point.h"

class Graph;
class ListGraph;
class HybridGraph;
class MatrixGraph;

class StandardLayoutVisitor : public AlgorithmVisitor
{
public:
    StandardLayoutVisitor();
    void visit(Graph& graph);

    // do one iteration of the aglorithm
    void iterationStep(Graph& graph);
    string getName() const { return "Standard Layout Algorithm - Balazs Nemeth";}
protected:
    /* making the actual layout algorithm protected will allow any
        algorithmen that needs the standard layout algorithm to have a starting point to use it if it is deriven from this class*/
    void layoutGraph(Graph& graph);
private:
    // resets any calculations done so far
    void reset();
    void calculateEndPoints();
    float calculateAngle(float x1, float y1, float x2, float y2);
    // the calculated endpoints for the algorithm
    vector<Point> endPoints;
    vector<Point> originalPoints;
    // only calculate the slopes once
    vector<float> _sines;
    vector<float> _cosines;
    float _dist;
};

#endif // STANDARDLAYOUTVISITOR_H
