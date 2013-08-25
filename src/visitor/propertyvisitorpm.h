/*
  Author: Jeroen Vaelen
  Description: Prototypemanager for property visitors
*/

#ifndef PROPERTYVISITORPM_H
#define PROPERTYVISITORPM_H

#include <vector>
#include <list>
#include <string>

using namespace std;

#include "observer/subject.h"
#include "visitor/propertyvisitor.h"

class PropertyVisitorPM
{
public:
    PropertyVisitorPM();
    // frees up all the memory used by the visitors
    ~PropertyVisitorPM();
    // adds a given visitor to the prototypemanager
    void addVisitor(PropertyVisitor* visitor);
    // returns the visitor with the given hash
    PropertyVisitor* getVisitor(unsigned hash) const;
    /* returns a list containing the names of all the visitors
        (the names of all the Algorithems, this list can be used to be shown to the user)*/
    list<string> getNames() const;
    // tells all visitors that a graph has been deleted in the tool kit
    void notifyGraphRemoved(Graph * graph);
    // sets focus graph for all visitors
    void setFocusGraph(Graph * graph);
    // returns the visitors
    const vector<PropertyVisitor*>& getPropertyVisitors() const { return _visitors; }


private:
    vector<PropertyVisitor*> _visitors;

};

#endif // PROPERTYVISITORPM_H
