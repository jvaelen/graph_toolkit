#include <assert.h>
#include <vector>
#include <QDebug>
#include "propertyvisitorpm.h"
#include "propertyvisitor.h"

PropertyVisitorPM::PropertyVisitorPM()
{

}

PropertyVisitorPM::~PropertyVisitorPM()
{
    // remove all the visitors
    for (vector<PropertyVisitor*>::iterator i = _visitors.begin(); i != _visitors.end(); ++i)
        delete *i;
    // don't have to clear the visitors vector, the destructor will take care of that
}

void PropertyVisitorPM::addVisitor(PropertyVisitor* visitor)
{
    _visitors.push_back(visitor);
}

PropertyVisitor* PropertyVisitorPM::getVisitor(unsigned hash) const
{
    assert(hash < _visitors.size());
    return _visitors[hash];
}

list<string> PropertyVisitorPM::getNames() const
{
    list<string> names;
    // get all the names and push them back into the names list
    for (unsigned i = 0; i < _visitors.size(); ++i)
        names.push_back(_visitors[i]->getName());
    // return the constructed list
    return names;
}

void PropertyVisitorPM::notifyGraphRemoved(Graph* graph)
{
    // run through all visitors and tell them to delete graph
    for (unsigned i = 0; i < _visitors.size(); ++i)
        _visitors[i]->removeFromOpenGraphs(graph);
}

void PropertyVisitorPM::setFocusGraph(Graph* graph)
{
    for (unsigned i = 0; i < _visitors.size(); ++i)
        _visitors[i]->setFocusGraph(graph);
}
