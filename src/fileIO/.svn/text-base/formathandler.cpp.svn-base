#include "formathandler.h"
#include <assert.h>

FormatHandler::FormatHandler()
{
    _state = NULL;
}

FormatHandler::~FormatHandler()
{
    // don't delete the _state! this is managed by prototypemanager!
}

void FormatHandler::doIO()
{
    assert(_state);
    _state->doIO();
}

void FormatHandler::setFileName(const string& fileName)
{
    assert(_state);
    _state->setFileName(fileName);
}

void FormatHandler::setGraphPointer(Graph* graphPointer)
{
    assert(_state);
    _state->setGraphPointer(graphPointer);
}

void FormatHandler::setState(FormatHandlerState* state)
{
    _state = state;
}
