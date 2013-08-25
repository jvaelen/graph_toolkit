/*
 Author: Balazs Nemeth
 Description: Dot Writer that reads a graph from a dot
     */
#ifndef DOTWRITER_H
#define DOTWRITER_H

#include "formathandlerstate.h"
#include <string>

using namespace std;

class DotWriter : public FormatHandlerState
{
public:
    DotWriter();
    // writer the graph in _graphPointer to a file
    void doIO();
    string getDescription() const {return description();}
    string getExtension() const {return extention();}
    static string extention() {return "dot";}
    static string description() { return "Graphviz (DOT Language File)";}
private:
    // converts nodes to the dot language
    string nodesToDot();
    // converts edges to the dot language
    string edgesToDot();
    // removes all character that are not letters or numbers
    string clearString(const string& name);
};

#endif // DOTWRITER_H
