#include <sstream>
#include <cmath>

#include "point.h"

Point::Point(int x, int y)
{
    _x = x;
    _y = y;
}

Point::Point()
{
    _x = 0;
    _y = 0;
}

double Point::distance(const Point& other) const
{
    // use pythagoras to calculate the distance
    int deltaX = _x - other.getX();
    int deltaY = _y - other.getY();

    return sqrt(deltaX*deltaX + deltaY*deltaY);
}

float Point::length() const
{
    return sqrt(_x*_x + _y*_y);
}

bool Point::operator==(const Point& other) const
{
    return (other._x == _x && other._y == _y);
}

bool Point::operator!=(const Point& other) const
{
    return (other._x != _x || other._y != _y);
}

Point Point::operator-(const Point& other) const
{
    return Point(_x - other._x, _y - other._y);
}

// calculates the sum of the 2 vectors
Point Point::operator+(const Point& other) const
{
    return Point(_x + other._x, _y + other._y);
}

Point Point::operator/(const float scalar) const
{
    return Point(_x/scalar, _y/scalar);
}

Point Point::operator*(const float scalar) const
{
    return Point(_x * scalar, _y*scalar);
}

Point Point::median(const Point& pointOne, const Point& pointTwo)
{
    return Point((pointOne.getX() + pointTwo.getX())/2, (pointOne.getY() + pointTwo.getY())/2);
}

string Point::toString() const
{
    stringstream tempStream;
    tempStream <<  "(" << _x << "," <<  _y  << ")";
    return tempStream.str();
}

// friend
QDebug operator<<(QDebug dbg, const Point& other)
{
    dbg.nospace() << "(" << other._x << "," << other._y << ")";
    return dbg.space();
}
