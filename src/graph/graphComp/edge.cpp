#include <assert.h>

#include "edge.h"
#include "node.h"


Edge::~Edge()
{
    _willBeDeleted = true;
    // basicly tell the observers that the edge will be deleted
    notifyObservers();
}

Edge::Edge(const Edge& other) : GraphComp()
{
    _source = other._source;
    _target = other._target;
    _rgbColor = other._rgbColor;
    _willBeDeleted = other._willBeDeleted;
    _label = other._label;
}

Edge::Edge(Node* source, Node* target, const Label& label, const RGB& rgb)
{
    _rgbColor = rgb;
    // source and target should never be NULL
    assert(source);
    assert(target);
    _willBeDeleted = false;
    _label  = label;
    _source = source;
    _target = target;
}

bool Edge::isSelfEdge() const
{
    return _source == _target;
}

bool Edge::isUndirected(Edge *edge) const
{
    return (_source == edge->getTarget() && _target == edge->getSource() && _label == edge->getLabel());
}

void Edge::setSource(Node* source)
{
    assert(source);
    _source = source;
}

void Edge::setTarget(Node* target)
{
    assert(target);
    _target = target;
}

// friend
QDebug operator<<(QDebug dbg, const Edge& other)
{
    dbg.nospace() << "Edge:\nLabel: " << other._label << ", source:\n" << *(other._source) << "target:\n " << *(other._target);
    return dbg.space();
}
