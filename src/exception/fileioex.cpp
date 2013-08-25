#include "fileioex.h"

FileIOEx::FileIOEx(const string& path, string  extraInfo, int priority) : BaseEx(extraInfo, priority)
{
    _path = path;
}

void FileIOEx::setPath(const string& path)
{
    _path = path;
}

string FileIOEx::getMessage() const
{
    string result;
    result += "There was a critical error regarding fileIO with a file at the following path: ";
    result += _path;
    if (!_extraInfo.empty())
        result += "extra information: " + _extraInfo;
    return result;
}
