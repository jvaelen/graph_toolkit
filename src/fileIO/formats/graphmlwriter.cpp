#include "graphmlwriter.h"
#include <QTextStream>
#include <iostream>
#include <vector>
#include <assert.h>
#include "graph/graphComp/node.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/point.h"

GraphMLWriter::GraphMLWriter()
{
    _graphPointer = NULL;
}

int GraphMLWriter::getNodeID(Node *node) const
{
    vector<Node*> nodes = _graphPointer->getNodes();
    for (unsigned i = 0; i < nodes.size(); ++i)
    {
        if (nodes[i] == node)
            return i;
    }
    return -1;
}

void GraphMLWriter::initDomDocument()
{
    // clear the _doc, needed when we save two times (or more) in one run
    _doc.clear();
    // create dom document and create the key values
    // root element
    QDomElement root = _doc.createElement("graphml");
    // set namespace
    root.setAttribute("xmlns", "http://graphml.graphdrawing.org/xmlns");
    _doc.appendChild(root);

    // key elements: defining special properties for our graphs
    // node and edge labels
    QDomElement keyLabel = _doc.createElement("key");
    keyLabel.setAttribute("id", "label");
    keyLabel.setAttribute("for", "all");
    keyLabel.setAttribute("attr.name", "label");
    keyLabel.setAttribute("attr.type", "string");
    root.appendChild(keyLabel);
    // node x coord
    QDomElement keyX = _doc.createElement("key");
    keyX.setAttribute("id", "x");
    keyX.setAttribute("for", "node");
    keyX.setAttribute("attr.name", "x");
    keyX.setAttribute("attr.type", "float");
    root.appendChild(keyX);
    // node y coord
    QDomElement keyY = _doc.createElement("key");
    keyY.setAttribute("id", "y");
    keyY.setAttribute("for", "node");
    keyY.setAttribute("attr.name", "y");
    keyY.setAttribute("attr.type", "float");
    root.appendChild(keyY);
    // node color
    // r
    QDomElement keyR = _doc.createElement("key");
    keyR.setAttribute("id", "r");
    keyR.setAttribute("for", "node");
    keyR.setAttribute("attr.name", "r");
    keyR.setAttribute("attr.type", "int");
    root.appendChild(keyR);
    // g
    QDomElement keyG = _doc.createElement("key");
    keyG.setAttribute("id", "g");
    keyG.setAttribute("for", "node");
    keyG.setAttribute("attr.name", "g");
    keyG.setAttribute("attr.type", "int");
    root.appendChild(keyG);
    // b
    QDomElement keyB = _doc.createElement("key");
    keyB.setAttribute("id", "b");
    keyB.setAttribute("for", "node");
    keyB.setAttribute("attr.name", "b");
    keyB.setAttribute("attr.type", "int");
    root.appendChild(keyB);

    // graph element
    QDomElement graph = _doc.createElement("graph");
    // root attribute edgedefault: our graphs are always directed
    graph.setAttribute("edgedefault", "directed");
    // root attribute id: name of graph
    graph.setAttribute("id", QString::fromStdString(_graphPointer->getName()));
    root.appendChild(graph);


}

void GraphMLWriter::addNodes()
{
    // fetch graph element
    QDomElement graph = _doc.documentElement().firstChildElement("graph");

    vector<Node*> nodes = _graphPointer->getNodes();
    unsigned bound = _graphPointer->getNumberOfNodes();
    // add all nodes
    for (unsigned i = 0; i < bound; ++i)
    {
        QDomElement n = _doc.createElement("node");
        n.setAttribute("id", getNodeID(nodes[i]));

        // add key data: node label
        QDomElement nodeLabel = _doc.createElement("data");
        nodeLabel.setAttribute("key", "label");
        QDomText labelt = _doc.createTextNode(QString::fromStdString(nodes[i]->getLabel().getLabelString()));
        nodeLabel.appendChild(labelt);
        n.appendChild(nodeLabel);

        // add key data: node position - x
        QDomElement nodeX = _doc.createElement("data");
        nodeX.setAttribute("key", "x");
        QDomText xt = _doc.createTextNode(QString::number(nodes[i]->getCoords().getX()));
        nodeX.appendChild(xt);
        n.appendChild(nodeX);
        // add key data: node position - y
        QDomElement nodeY = _doc.createElement("data");
        nodeY.setAttribute("key", "y");
        QDomText yt = _doc.createTextNode(QString::number(nodes[i]->getCoords().getY()));
        nodeY.appendChild(yt);
        n.appendChild(nodeY);

        // add key data: node color
        // r
        QDomElement nodeR = _doc.createElement("data");
        nodeR.setAttribute("key", "r");
        QDomText rt = _doc.createTextNode(QString::number(nodes[i]->getColor().getRed()));
        nodeR.appendChild(rt);
        n.appendChild(nodeR);
        // g
        QDomElement nodeG = _doc.createElement("data");
        nodeG.setAttribute("key", "g");
        QDomText gt = _doc.createTextNode(QString::number(nodes[i]->getColor().getGreen()));
        nodeG.appendChild(gt);
        n.appendChild(nodeG);
        // b
        QDomElement nodeB = _doc.createElement("data");
        nodeB.setAttribute("key", "b");
        QDomText bt = _doc.createTextNode(QString::number(nodes[i]->getColor().getBlue()));
        nodeB.appendChild(bt);
        n.appendChild(nodeB);

        // add final node to xml
        graph.appendChild(n);
    }

}

void GraphMLWriter::addEdges()
{
    // fetch graph element
    QDomElement graph = _doc.documentElement().firstChildElement("graph");

    vector<Node*> nodes = _graphPointer->getNodes();
    unsigned bound = _graphPointer->getNumberOfNodes();

    // add all edges
    for (unsigned i = 0; i < bound; ++i)
    {
        list<Edge*> edges = _graphPointer->getOutgoingEdges(nodes[i]);
        for (list<Edge*>::const_iterator j = edges.begin(); j != edges.end(); ++j)
        {
            QDomElement e = _doc.createElement("edge");
            e.setAttribute("source", getNodeID((*j)->getSource()));
            e.setAttribute("target", getNodeID((*j)->getTarget()));

            // add key data: edge color
            // r
            QDomElement edgeR = _doc.createElement("data");
            edgeR.setAttribute("key", "r");
            QDomText rt = _doc.createTextNode(QString::number((*j)->getColor().getRed()));
            edgeR.appendChild(rt);
            e.appendChild(edgeR);
            // g
            QDomElement edgeG = _doc.createElement("data");
            edgeG.setAttribute("key", "g");
            QDomText gt = _doc.createTextNode(QString::number((*j)->getColor().getGreen()));
            edgeG.appendChild(gt);
            e.appendChild(edgeG);
            // b
            QDomElement edgeB = _doc.createElement("data");
            edgeB.setAttribute("key", "b");
            QDomText bt = _doc.createTextNode(QString::number((*j)->getColor().getBlue()));
            edgeB.appendChild(bt);
            e.appendChild(edgeB);

            // add key data: edge label
            QDomElement edgeLabel = _doc.createElement("data");
            edgeLabel.setAttribute("key", "label");
            QDomText t = _doc.createTextNode(QString::fromStdString((*j)->getLabel().getLabelString()));
            edgeLabel.appendChild(t);
            e.appendChild(edgeLabel);
            graph.appendChild(e);
        }
    }

}

void GraphMLWriter::writeToFile()
{
    QString xml = _doc.toString();

    QFile data(QString::fromStdString(_fileName));
    QTextStream out(&data);
    if (data.open(QFile::WriteOnly | QFile::Truncate)) {
        out << "<?xml version=\"1.0\"?>" << endl;
        out << xml;
    }

}

void GraphMLWriter::doIO()
{
    // make sure _graphPointer is set
    assert(_graphPointer != NULL);

    // STEP 1: init XML doc: (namespace and key values)
    initDomDocument();

    // STEP 2: add the nodes (with matching key values)
    addNodes();

    // STEP 3: add the edges (with matching key values)
    addEdges();

    // STEP 4: write the XML document to a file
    writeToFile();
}
