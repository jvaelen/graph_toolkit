/* Jeroen Vaelen */

#ifndef GRAPHMLWRITER_H
#define GRAPHMLWRITER_H

#include "formathandlerstate.h"
#include <QtXml>

class GraphMLWriter : public FormatHandlerState
{
public:
    GraphMLWriter();
    void doIO();
    string getDescription() const { return description(); }
    string getExtension() const { return extention(); }
    static string extention() {return "xml";}
    static string description() { return "XML-based file format";}


private:
    // working dom document
    QDomDocument _doc;

    void initDomDocument();

    void addNodes();

    void addEdges();

    void writeToFile();

    // returns node id for the write away, -1 if given node is not a node of _graphPointer
    int getNodeID(Node* node) const;
};

#endif // GRAPHMLWRITER_H
