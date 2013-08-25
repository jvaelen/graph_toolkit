/*
 Author: Balazs Nemeth
 Description: This class represents a node in a graph. It has a label that can be a cost or just a string of text, it also has a position
     */


#ifndef NODE_H
#define NODE_H

#include <QDebug>

#include "point.h"
#include "observer/subject.h"
#include "graphcomp.h"

class Node : public GraphComp
{
public:
    // sets the label and sets the coords to 0,0
    Node(const Label& label);
    // constructs a node from a label and a coord
    Node(const Label& label, const Point& coord);
    Node(const Label& label, const Point& coord, const RGB& rgb);
    // constructs a node from another node
    Node(const Node& other);
    // creates a node with an empty label and coords at 0,0
    Node();
    // destructor sets _willBeDeleted and notifies the observers telling them that the object will be deleted
    ~Node();
    // the node needs an ID to make it possible to identify edges even after the nodes that the edge connect are removed
    unsigned long getID() const { return _id;}

    const Point& getCoords() const {return _coord;}
    void setCoords(const Point& coords);
    //friends
    friend QDebug operator<<(QDebug dbg, const Node& other);
protected:
    // returns the next id and also increments the id to prepare it for the next time
    static unsigned long getNextID();
    unsigned long _id;
    Point _coord;
};
//unsigned long Node::_nextId = 0;
#endif // NODE_H
