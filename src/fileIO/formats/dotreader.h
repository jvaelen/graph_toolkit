/*
 Author: Balazs Nemeth
 Description: Dot Reader that reads a graph from a dot, note that reading a dot file is very limited and should be very precicly constructed
     */
#ifndef DOTREADER_H
#define DOTREADER_H
#include "formathandlerstate.h"
#include <string>

using namespace std;

class DotReader : public FormatHandlerState
{
public:
    DotReader();
    void doIO();
    string getDescription() const {return description();}
    string getExtension() const {return extention();}
    static string extention() {return "dot";}
    static string description() { return "Graphviz (DOT Language File)";}
private:
    // process a line for a node
    void processLineNode(string line);
    // process line for an edge
    void processLineEdge(string line);
    // returns true if string contains '->'
    bool isEdgeLine(string line);
    // parses the name of the graph form the file
    bool parseName(string line);
    void readFile();
    // temp storage for the file lines
    list<string> _fileLines;
    // map between
    map<string, Node*> _nodeIDMap;
};

#endif // DOTREADER_H
