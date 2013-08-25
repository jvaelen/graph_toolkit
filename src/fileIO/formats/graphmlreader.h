/* Jeroen Vaelen*/

#ifndef GRAPHMLREADER_H
#define GRAPHMLREADER_H

#include "formathandlerstate.h"
#include <QHash>
#include <QtXml>


class GraphMLReader : public FormatHandlerState
{
public:
    GraphMLReader();
    void doIO();
    string getDescription() const { return description(); }
    string getExtension() const { return extention(); }
    static string extention() {return "xml";}
    static string description() { return "XML-based file format";}


private:
    // xml doc we will load in
    QDomDocument _doc;
    // maps node id to label name
    QHash<QString, int> _map;

    void initFile();
    void addNodes();
    void addEdges();

};

#endif // GRAPHMLREADER_H
