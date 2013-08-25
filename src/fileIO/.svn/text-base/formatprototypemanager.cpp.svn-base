#include "formatprototypemanager.h"
#include "assert.h"
#include "exception/invalidformatex.h"

FormatPrototypeManager::FormatPrototypeManager()
{
}

FormatPrototypeManager::~FormatPrototypeManager()
{
    // run through hash maps and delete all format handlers
    for (map<string, FormatHandlerState*>::iterator it = _readers.begin(); it != _readers.end(); ++it)
        delete it->second;
    for (map<string, FormatHandlerState*>::iterator it = _writers.begin(); it != _writers.end(); ++it)
        delete it->second;
}

void FormatPrototypeManager::addFormatReader(FormatHandlerState* newReader, string hash)
{
    assert(newReader != NULL);
    // make sure every reader hash is unique
    assert(_readers.count(hash) == 0);
    _readers[hash] = newReader;
}

void FormatPrototypeManager::addFormatWriter(FormatHandlerState *newWriter, string hash)
{
    assert(newWriter != NULL);
    // make sure every writer hash is unique
    assert(_writers.count(hash) == 0);
    _writers[hash] = newWriter;
}

FormatHandlerState* FormatPrototypeManager::getReader(string hash) const
{
    // trying to get a reader that does not exist
    if (!_readers.count(hash))
        throw (InvalidFormatEx(convertHashToExtention(hash), 3));
    else
        return _readers.at(hash);
}

FormatHandlerState* FormatPrototypeManager::getWriter(string hash) const
{
    // trying to get a writer that does not exist
    if (!_writers.count(hash))
        throw (InvalidFormatEx(convertHashToExtention(hash), 3));
    else
        return _writers.at(hash);
}

string FormatPrototypeManager::convertHashToExtention(string hash)
{
    return hash.substr(0, hash.size() - 6);
}


vector<string> FormatPrototypeManager::getWriterExtensions() const
{
    vector<string> result;
    result.reserve(_writers.size());
    for (map<string, FormatHandlerState*>::const_iterator it = _writers.begin(); it != _writers.end(); ++it)
        result.push_back(it->second->getExtension());
    return result;
}

vector<string> FormatPrototypeManager::getReaderExtensions() const
{
    vector<string> result;
    result.reserve(_readers.size());
    for (map<string, FormatHandlerState*>::const_iterator it = _readers.begin(); it != _readers.end(); ++it)
        result.push_back(it->second->getExtension());
    return result;
}

vector<string> FormatPrototypeManager::getWriterDescriptions() const
{
    vector<string> result;
    result.reserve(_writers.size());
    for (map<string, FormatHandlerState*>::const_iterator it = _writers.begin(); it != _writers.end(); ++it)
        result.push_back(it->second->getDescription());
    return result;
}

vector<string> FormatPrototypeManager::getReaderDescriptions() const
{
    vector<string> result;
    result.reserve(_readers.size());
    for (map<string, FormatHandlerState*>::const_iterator it = _readers.begin(); it != _readers.end(); ++it)
        result.push_back(it->second->getDescription());
    return result;
}
