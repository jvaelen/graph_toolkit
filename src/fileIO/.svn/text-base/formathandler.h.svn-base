/* Author: Jeroen Vaelen */

#ifndef FORMATHANDLER_H
#define FORMATHANDLER_H

#include <string>
#include <fileIO/formats/formathandlerstate.h>

class Graph;

using namespace std;

class FormatHandler
{
public:
    FormatHandler();
    ~FormatHandler();

    // delegated to the state
    void doIO();
    void setFileName(const string& fileName);
    void setGraphPointer(Graph* graphPointer);

    void setState(FormatHandlerState* state);

protected:
    FormatHandlerState* _state;
};

#endif // FORMATHANDLER_H
