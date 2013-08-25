#include "toolparameters.h"

ToolParameters::ToolParameters()
{
    reset();
}

ToolParameters::ToolParameters(const Node &other) : _node(other)
{
    // the init list is used to create fill in _node
    _source = NULL;
    _target = NULL;
    _edge = NULL;
}

void ToolParameters::setParametersFromEdge(Edge *edge)
{
    setEdge(edge);
    setSource(edge->getSource());
    setTarget(edge->getTarget());
    setLabel(edge->getLabel());
}

void ToolParameters::setEdge(Edge* edge)
{
    _edge = edge;
}

void ToolParameters::setSource(Node* source)
{
    _source = source;
    _sourceID = _source->getID();
}

void ToolParameters::setTarget(Node* target)
{
    _target = target;
    _targetID = _target->getID();
}

void ToolParameters::setNode(Node newNode)
{
    _node = newNode;
    _label = _node.getLabel();
}

void ToolParameters::setLabel(const Label& label)
{
    _label = label;
}

void ToolParameters::reset()
{
    _edge = NULL;
    _source = NULL;
    _sourceID = 0;
    _targetID = 0;
    _target = NULL;
    _label.setLabelString("");
    _node = Node();
}
