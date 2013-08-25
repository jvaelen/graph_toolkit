/*
  Author: Jeroen Vaelen
  Description: Manager that holds all Algorithm visitors (drawing and theory)
  */


#ifndef ALGORITHMVISITORPM_H
#define ALGORITHMVISITORPM_H

#include <vector>
#include <list>
#include <string>

class Graph;

using namespace std;

class AlgorithmVisitor;

class AlgorithmVisitorPM
{
public:
    AlgorithmVisitorPM();
    // frees up all the memory used by the visitors
    ~AlgorithmVisitorPM();
    // adds a given visitor to the prototypemanager
    void addVisitor(AlgorithmVisitor* visitor);
    // returns the visitor with the given hash
    AlgorithmVisitor* getVisitor(unsigned hash) const;
    /* returns a list containing the names of all the visitors
        (the names of all the Algorithems, this list can be used to be shown to the user)*/
    list<string> getNames() const;
    // resets all values of the visitors, used when we stop the algo to reset
    void resetAll();

private:
    vector<AlgorithmVisitor*> _visitors;

};
#endif // ALGORITHMVISITORPM_H
