/* Author: Jeroen Vaelen */

#ifndef FORMATHANDLERSTATE_H
#define FORMATHANDLERSTATE_H

#include <string>
#include "graph/graph.h"

using namespace std;

class FormatHandlerState
{
public:
    FormatHandlerState() { _graphPointer = NULL; }
    void setFileName(const string& fileName) { _fileName = fileName; }
    void setGraphPointer(Graph* graphPointer) { _graphPointer = graphPointer; }
    virtual void doIO() = 0;
    // added by Balazs Nemeth
    virtual string getDescription() const = 0;
    virtual string getExtension() const = 0;
protected:
    // returns the filename
    string getFileName(const string& fileName);
    string _fileName;
    Graph* _graphPointer;
};

#endif // FORMATHANDLERSTATE_H
