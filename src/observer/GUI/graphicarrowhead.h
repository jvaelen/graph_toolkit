/*
 Author: Balazs Nemeth
 Description: This class represents the arrowhead, it is basicly a wrapper around a polygon.
     */

#ifndef GRAPHICARROWHEAD_H
#define GRAPHICARROWHEAD_H

#include <QPolygon>
#include "graph/graphComp/point.h"

class GraphicArrowHead
{
public:
    GraphicArrowHead();
    // clears the allocated memory for the QPolygon
    ~GraphicArrowHead();
    // the arrow sits on this line
    void setLine(const Point& start, const Point& end);
    // set the width and height, this will recalculate the arrowhead only once
    void setValues(int height, int width, int distance);
    // set the width or the height, every set will recalculate the arrowhead
    void setHeight(int height);
    void setWidth(int width);
    void setDistance(int distance);
    // returns the polygon
    const QPolygon& getPolygon() const {return *_polygon;}
    // calculate the intersection of a line with a circle, this function is made static so that it can be used outside
    static QPoint calcIntersection(float x1, float y1, float x2, float y2, float r);
private:
    // this function recalculates the polygon that describes the arrow
    void updateTriangle();
    Point _start, _end;
    // the height of the arrow, this is used to calculate where the base is of the triangle of the arrow
    int _height;
    // the width is how far the arrow sticks out on both sides of the lie
    int _width;
    // the arrowhead will be drawn this amount from the end of the line
    int _distance;
    // the polygon (arrowhead)
    QPolygon* _polygon;
};

#endif // GRAPHICARROWHEAD_H
