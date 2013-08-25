#include "graphmlreader.h"
#include <iostream>
#include <QDebug>
#include <QFile>
#include "graph/hybridgraph.h"
#include "graph/graphComp/node.h"
#include "graph/graphComp/rgb.h"

GraphMLReader::GraphMLReader()
{
    _graphPointer = NULL;
}

void GraphMLReader::initFile()
{
    // open and read file - document init
    QFile file(QString::fromStdString(_fileName));
    if (!file.open(QIODevice::ReadOnly))
        return;
    if (!_doc.setContent(&file)) {
        file.close();
        return;
    }
    // rename graph correctly
    _graphPointer->setName(_doc.documentElement().firstChildElement("graph").attribute("id").toStdString());
}

void GraphMLReader::addNodes()
{
    // id used for map
    int id = 0;

    // fetch all "node" elements
    QDomNodeList nodeList = _doc.elementsByTagName("node");
    for (int i = 0; i < nodeList.size(); ++i)
    {
        QString label = "";
        int x=0, y=0, r=0 ,g=0, b=0;
        // run through all children (key nodes) and fill in the correct key variables
        QDomNode n = nodeList.item(i).firstChild();
        while (!n.isNull())
        {
            if (n.isElement())
            {
                QDomElement e = n.toElement();

                if (e.attribute("key") == "x")
                    x = e.text().toInt();

                else if (e.attribute("key") == "y")
                    y = e.text().toInt();

                else if (e.attribute("key") == "r")
                    r = e.text().toInt();

                else if (e.attribute("key") == "g")
                    g = e.text().toInt();

                else if (e.attribute("key") == "b")
                    b = e.text().toInt();

                else if (e.attribute("key") == "label")
                    label = e.text();

            }
            n = n.nextSibling();
        }

        // add the node
        _graphPointer->addNode(Node(label.toStdString(), Point(x, y), RGB(r,g,b)));
        _map.insert(nodeList.item(i).toElement().attribute("id"), id);
        id++;

    }
}

void GraphMLReader::addEdges()
{
    // target, source and label used for adding edges
    QString tar, source, label;
    // current edge
    QDomNode current;

    // fetch all edge elements
    QDomNodeList edgeList = _doc.elementsByTagName("edge");

    // rgb values
    int r=0 ,g=0, b=0;

    // add edges one by one using the id map
    for (int i = 0; i < edgeList.size(); ++i)
    {
        current = edgeList.item(i);

        // run through all children (key nodes) and fill in the correct key variables
        QDomNode n = current.firstChild();
        while (!n.isNull())
        {

            if (n.isElement())
            {
                QDomElement e = n.toElement();
                if (e.attribute("key") == "label")
                    label = e.text();

                else if (e.attribute("key") == "r")
                    r = e.text().toInt();

                else if (e.attribute("key") == "g")
                    g = e.text().toInt();

                else if (e.attribute("key") == "b")
                    b = e.text().toInt();
            }

            n = n.nextSibling();

        }

        // fetch target and source for current edge element
        tar = current.toElement().attribute("target");
        source = current.toElement().attribute("source");
        // add edge
        const vector<Node*>& nodes = _graphPointer->getNodes();
        _graphPointer->addEdge(Edge(nodes[(unsigned int)_map.value(source)], nodes[(unsigned int)_map.value(tar)], label.toStdString(), RGB(r,g,b)));

    }

}

void GraphMLReader::doIO()
{
    // STEP 1: load the file and initialize the dom document
    initFile();

    // STEP 2: add all nodes, initialize the map so we can properly add the edges
    addNodes();

    // STEP 3: add all the edges using the map for the proper id's
    addEdges();
}
