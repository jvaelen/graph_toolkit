#include "graphicarrowhead.h"
#include <cmath>

GraphicArrowHead::GraphicArrowHead()
{
    _height = 0;
    _width = 0;
    _distance = 0;
    // allocate the memory for the polygon setting the size to 3
    _polygon = new QPolygon(3);
}

GraphicArrowHead::~GraphicArrowHead()
{
    delete _polygon;
}

void GraphicArrowHead::setValues(int height, int width, int distance)
{
    _height = height;
    _width = width;
    _distance = distance;
    updateTriangle();
}

// the arrow sits on this line
void GraphicArrowHead::setLine(const Point& start, const Point& end)
{
    if (_start != start || _end != end)
    {
        _end =  end;
        _start = start;
        updateTriangle();
    }
}

void GraphicArrowHead::setHeight(int height)
{
    _height = height;
    updateTriangle();
}

void GraphicArrowHead::setWidth(int width)
{
    _width = width;
    updateTriangle();
}

void GraphicArrowHead::updateTriangle()
{
    // an arrow with height of width with 0 can't be drawn, also the start and end parts have to be seperated
    if ((_width == 0 || _height == 0) && _start == _end)
        return;

    int x2 = _end.getX();
    int y2 = _end.getY();
    int x1 = _start.getX();
    int y1 = _start.getY();
    QPoint two = calcIntersection(x2, y2, x1, y1, _distance);
    // set the line from the source to the destination, but the line is from the side of one node to the side of the other
    // calculate 2 points one is 50 from the center of the node and the other is 70 from the node, so the segment is of length 20 and this we transform in the right position
    QPoint three = calcIntersection(x2, y2, x1, y1, _distance + _height);
    QPoint four = calcIntersection(x2, y2,  x1, y1, _distance + _height + _width/2);

    _polygon->setPoint(0, two);
    _polygon->setPoint(1, QPoint((four.y() - three.y()) + three.x(), (three.x() - four.x()) + three.y()));
    _polygon->setPoint(2, QPoint((three.y() - four.y()) + three.x(), (four.x() - three.x()) + three.y()));
}

// source for intersection of a line with a circle: http://mathworld.wolfram.com/Circle-LineIntersection.html
QPoint GraphicArrowHead::calcIntersection(float x1, float y1, float x2, float y2, float r)
{
    // in the formule given on the website, we choose x1 and y1 to be 0 (transformation to 0,0)
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dr = sqrt(dx*dx + dy*dy);
    if (dr <= 0.0001)
        dr = 1.0f;
    float x = (dy > 0? 1 : -1)*dx *((r/dr) > 0.0f ? (r/dr) : -(r/dr));
    float y = ((dy*r)/dr);
    y = (y > 0 ? y : -y);
    // next we check if the newly calculated point is on the line, if this isn't the case we need the other solution
    float newX1 = x + x1;
    float newY1 = y + y1;
    float newdx = newX1 - x2;
    float newdy = newY1 - y2;
    if (newdx*newdx + newdy*newdy < (dx)*(dx) + (dy)*(dy))
        return QPoint(x + x1, y + y1);
    else
        return QPoint(-x + x1, -y + y1);
}
