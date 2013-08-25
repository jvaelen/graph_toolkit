#include "node.h"

Node::Node()
{
    // default value for label
    _label = Label("");
    _willBeDeleted = false;
    _id = Node::getNextID();
    // default constructor for the RGB class will be used and a black node will be created
}

Node::~Node()
{
    _willBeDeleted = true;
    // basicly tell the observers that the node will be deleted
    notifyObservers();
}

Node::Node(const Label& label)
{
    // set the label
    _label = label;
    _willBeDeleted = false;
    _id = Node::getNextID();
}

// copying the observers would give us problems, so the observers aren't copied
Node::Node(const Node& other) : GraphComp()
{
    _label = other._label;
    _coord = other._coord;
    _willBeDeleted = other._willBeDeleted;
    _rgbColor = other._rgbColor;
    _id = other._id;
}

Node::Node(const Label& label, const Point& coord)
{
    _label = label;
    _coord = coord;
    _willBeDeleted = false;
    _id = Node::getNextID();
    // default constructor for RGB class will be used
}

Node::Node(const Label& label, const Point &coord, const RGB &rgb)
{
    _label = label;
    _coord = coord;
    _willBeDeleted = false;
    _rgbColor = rgb;
    _id = Node::getNextID();
}

unsigned long Node::getNextID()
{
    static unsigned long _nextId = 0;
    return _nextId++;
}


void Node::setCoords(const Point& coords)
{
    // set the new coords
    _coord = coords;
    // and notify the observers telling them about the new position
    notifyObservers();
}

//friend
QDebug operator<<(QDebug dbg, const Node& other)
{
    dbg.nospace() << "Node:\nLabel:" << other._label << "\nColor: " << other._rgbColor;
    return dbg.space();
}
