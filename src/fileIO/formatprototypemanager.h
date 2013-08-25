/* Author: Jeroen Vaelen */

#ifndef FORMATPROTOTYPEMANAGER_H
#define FORMATPROTOTYPEMANAGER_H

#include <map>
#include <string>
using namespace std;

#include "fileIO/formats/formathandlerstate.h"

class FormatPrototypeManager
{
public:
    FormatPrototypeManager();
    ~FormatPrototypeManager();

    void addFormatReader(FormatHandlerState* newReader, string hash);
    void addFormatWriter(FormatHandlerState* newWriter, string hash);

    FormatHandlerState* getReader(string hash) const;
    FormatHandlerState* getWriter(string hash) const;

    // added by Balazs, returns for each instance in the prototypemanager what the function suggests
    vector<string> getWriterExtensions() const;
    vector<string> getReaderExtensions() const;
    vector<string> getWriterDescriptions() const;
    vector<string> getReaderDescriptions() const;
    // returns the extention (removes writer or reader from the end)
    static string convertHashToExtention(string hash);
private:
    map<string, FormatHandlerState*> _readers;
    map<string, FormatHandlerState*> _writers;

};

#endif // FORMATPROTOTYPEMANAGER_H
