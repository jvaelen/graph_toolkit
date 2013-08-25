#include "formathandlerstate.h"

string FormatHandlerState::getFileName(const string& fileName)
{
    string result = "";
    for (unsigned i = 0; i < fileName.size(); ++i)
    {
        if (fileName.at(i) == '/')
            result = "";
        else
            result += fileName.at(i);
    }
    return result;
}
