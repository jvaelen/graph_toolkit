#include <fstream>

#include "dotreader.h"
#include "exception/fileioex.h"

DotReader::DotReader()
{

}

void DotReader::doIO()
{
    // reset the map that might have been filled in a previous doIO()
    _nodeIDMap.clear();
    // readFile will fill _fileLines
    readFile();

    list<string>::iterator i = _fileLines.begin();

    // first line should countain the name of the graph
    if (!parseName(*i))
        throw FileIOEx(_fileName, "can't read the graph name or this dot file isn't supported");
    ++i;
    while (i != _fileLines.end())
    {
        if (!(((*i).size() >= 1 &&((*i).at(0) == '}' || (*i).at(0) == '{'))  || (*i).size() <= 2))
        {
            if (isEdgeLine(*i))
                processLineEdge(*i);
            else
                processLineNode(*i);
        }
        ++i;
    }
}

bool DotReader::isEdgeLine(string line)
{
    for (unsigned i = 0; i < line.size(); ++i)
    {
        if (line.at(i) == '-' && i + 1 < line.size() && line.at(i+1) == '>')
            return true;
    }
    return false;
}

void DotReader::processLineEdge(string line)
{
    string nodeID = "";
    string nodeID2 = "";
    string edgeLabel = "";
//        q_0 [label ="Q0"];
    unsigned i = 0;
    // skip untill the first space
    while (i < line.size() && line.at(i) != ';' && line.at(i) == ' ')
        ++i;

    if (i >= line.size())
        return;
    // read the id of the node
    while (i < line.size() && line.at(i) != ';' && line.at(i) != ' ' && line.at(i) != '-')
    {
        nodeID += line.at(i);
        ++i;
    }
    while (i < line.size() && line.at(i) != ';' && line.at(i) != '>')
        ++i;
    ++i;
    // skip spaces
    while (i < line.size() && line.at(i) != ';' && line.at(i) == ' ')
        ++i;

    // read the id of the node
    while (i < line.size() && line.at(i) != ';' && line.at(i) != ' ')
    {
        nodeID2 += line.at(i);
        ++i;
    }
    while (i < line.size() && line.at(i) != ';' && line.at(i) != '"')
        ++i;
    ++i;

    while (i < line.size() && line.at(i) != ';' && line.at(i) != '"')
    {
        edgeLabel += line.at(i);
        ++i;
    }
    _graphPointer->addEdge(Edge(_nodeIDMap.at(nodeID), _nodeIDMap.at(nodeID2), edgeLabel));
}

void DotReader::processLineNode(string line)
{
    string nodeID = "";
    string nodeLabel = "";
    unsigned i = 0;
    // skip untill the first space
    while (i < line.size() && line.at(i) != ';' && line.at(i) == ' ')
        ++i;

    if (i >= line.size())
        return;
    // read the id of the node
    while (i < line.size() && line.at(i) != ';' && line.at(i) != ' ')
    {
        nodeID += line.at(i);
        ++i;
    }
    while (i < line.size() && line.at(i) != ';' && line.at(i) != '"')
        ++i;
    ++i;
    // read the node label
    while (i < line.size() && line.at(i) != ';' && line.at(i) != '"')
    {
        nodeLabel += line.at(i);
        ++i;
    }
    pair<string,Node*> newNodeMap;
    _graphPointer->addNode(Node(nodeLabel));
    newNodeMap.first = nodeID;
    newNodeMap.second = _graphPointer->getNodes().back();
    _nodeIDMap.insert(newNodeMap);
}

bool DotReader::parseName(string line)
{
    string graphName = "";
    unsigned i = 0;
    // skip untill the first space
    while (i < line.size() && line.at(i) != ' ')
            ++i;
    if (i >= line.size())
        return false;
    ++i; // skip of the space
    while (i < line.size() && line.at(i) != ' ')
    {
        graphName += line.at(i);
        ++i;
    }
    _graphPointer->setName(graphName);
    return true;
}


void DotReader::readFile()
{
    ifstream fileStream(_fileName.c_str());

    // if fileStream isn't set, the reading of the file failed
    if(!fileStream)
        throw FileIOEx(_fileName, "Can't read file");

    // buffer for the read line
    char str[255];

    // while the file isn't at EOF
    while(fileStream)
    {
       fileStream.getline(str, 255);
       _fileLines.push_back(str);
    }
    // close the file
    fileStream.close();
}
