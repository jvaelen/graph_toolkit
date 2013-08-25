#include <fstream>
#include <string>

#include "dotwriter.h"

DotWriter::DotWriter()
{
}

void DotWriter::doIO()
{
    string edgeDeclerationPart = edgesToDot();
    string nodeDeclerationPart = nodesToDot();
    // open a filestream
    fstream fileStream(_fileName.c_str(), ios::out);
    string resultString = "digraph " + clearString(_graphPointer->getName()) + "{";
    resultString += nodeDeclerationPart;
    resultString += edgeDeclerationPart;
    resultString += "\n}";
    fileStream << resultString;
    fileStream.close();
}

string DotWriter::clearString(const string& name)
{
    string result = "";
    for (unsigned i = 0; i < name.size(); ++i)
        if ((name.at(i) >= 'a' && name.at(i) <= 'z') ||
            (name.at(i) >= 'A' && name.at(i) <= 'Z') ||
            (name.at(i) >= '0' && name.at(i) <= '9') )
            result += name.at(i);
    return result;
}

string DotWriter::nodesToDot()
{
    string nodeString = "";
    const vector<Node*>& nodes = _graphPointer->getNodes();
    for (unsigned i = 0; i < nodes.size(); ++i)
        nodeString += "n" + Label(nodes[i]->getID()).getLabelString() + " [label=\"" + nodes[i]->getLabel().getLabelString() + "\"];\n";
    return nodeString;
}

string DotWriter::edgesToDot()
{
    string edgeString = "";
    const vector<Node*>& nodes = _graphPointer->getNodes();
    list<Edge*> edges;
    for (unsigned i = 0; i < nodes.size(); ++i)
    {
        edges = _graphPointer->getOutgoingEdges(nodes[i]);
         for (list<Edge*>::iterator e = edges.begin(); e != edges.end(); ++e)
            edgeString += "n" + Label((*e)->getSource()->getID()).getLabelString() + "->" + "n" +
                    Label((*e)->getTarget()->getID()).getLabelString() + "\n" + " [label=\"" + (*e)->getLabel().getLabelString() + "\"];\n";
    }
    return edgeString;
}

