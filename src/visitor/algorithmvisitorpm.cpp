#include <assert.h>
#include <vector>

#include "algorithmvisitorpm.h"
#include "algorithmvisitor.h"

AlgorithmVisitorPM::AlgorithmVisitorPM()
{

}

AlgorithmVisitorPM::~AlgorithmVisitorPM()
{
    // remove all the visitors
    for (vector<AlgorithmVisitor*>::iterator i = _visitors.begin(); i != _visitors.end(); ++i)
        delete *i;
    // don't have to clear the visitors vector, the destructor will take care of that
}

void AlgorithmVisitorPM::addVisitor(AlgorithmVisitor* visitor)
{
    _visitors.push_back(visitor);
}

AlgorithmVisitor* AlgorithmVisitorPM::getVisitor(unsigned hash) const
{
    assert(hash < _visitors.size());
    return _visitors[hash];
}

list<string> AlgorithmVisitorPM::getNames() const
{
    list<string> names;
    // get all the names and push them back into the names list
    for (unsigned i = 0; i < _visitors.size(); ++i)
        names.push_back(_visitors[i]->getName());
    // return the constructed list
    return names;
}

void AlgorithmVisitorPM::resetAll()
{
    for (unsigned i = 0; i < _visitors.size(); ++i)
        _visitors[i]->setFinished(true);
}
