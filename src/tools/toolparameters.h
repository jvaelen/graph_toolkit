/*
 Author: Balazs Nemeth
 Description: this class collects all the possible information that a tool could need.
     */
#ifndef TOOLPARAMETERS_H
#define TOOLPARAMETERS_H

#include "graph/graphComp/edge.h"
#include "graph/graphComp/label.h"
#include "graph/graphComp/node.h"
#include "graph/graphComp/point.h"
#include "graph/graphComp/rgb.h"

class ToolState;
class Graph;

class ToolParameters
{
public:
    // default constructor, sets all pointers to NULL
    ToolParameters();
    // creats a toolparameters instance and immediatly sets the _node
    ToolParameters(const Node& other);
    // getters
    Node* getSource() const {return _source;}
    Node* getTarget() const {return _target;}
    Node getNode() const {return _node;}
    Label getLabel() const {return _label;}
    Edge* getEdge() const {return _edge;}
    unsigned long getSourceID() const {return _sourceID;}
    unsigned long getTargetID() const {return _targetID;}
    // settters
    void setParametersFromEdge(Edge* edge);
    void setSource(Node* source);
    void setTarget(Node* target);
    void setNode(Node newNode);
    void setLabel(const Label& label);
    void setRGB(RGB rgb) {_rgb = rgb;}
    void setEdge(Edge* edge);
    RGB getRGB() const {return _rgb;}
    // resets everything
    void reset();
private:
    // if the parameter includes a new node
    Node _node;
    // source and target used with edges
    Node* _source;
    Node* _target;
    Edge* _edge;
    unsigned long _sourceID;
    unsigned long _targetID;
    RGB _rgb;
    Label _label;
};

#endif // TOOLPARAMETERS_H
