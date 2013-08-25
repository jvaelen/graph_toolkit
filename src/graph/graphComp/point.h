/*
 Author: Balazs Nemeth
 Description: Represents a point in R^2, Using this class will reduce dependence on the Qt framework. */


#ifndef POINT_H
#define POINT_H

#include <QDebug>
#include <string>

using namespace std;

class Point
{
public:
    // only way to construct a point is to give both x and y.
    Point(int x, int y);
    // default constructor sets _x and _y to 0
    Point();
    // copyconstructor suffices
    // returns the length of the line between this point and another point
    double distance(const Point& other) const;
    // setters and getters
    int getX() const {return _x;}
    int getY() const {return _y;}
    void setX(int x) {_x = x;}
    void setY(int y) {_y = y;}
    // sets the point to the point at (0,0). this function is used to efficiently reset a point to the origin
    void resetToZeros() {_x = 0; _y = 0;}
    // if the point would describe a vector, this would be it's length
    float length() const;
    // overload == operator to check if 2 points are at the same coordinates
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
    // calculates the difference vector described by the 2 points
    Point operator-(const Point& other) const;
    // calculates the sum of the 2 vectors
    Point operator+(const Point& other) const;
    // devides the vector that is described by the Point by a scalar
    Point operator/(const float scalar) const;
    Point operator*(const float scalar) const;
    string toString() const;
    static Point median(const Point& pointOne, const Point& pointTwo);
    // friends
    friend QDebug operator<<(QDebug dbg, const Point& other);
private:
    int _x;
    int _y;
};

#endif // POINT_H
