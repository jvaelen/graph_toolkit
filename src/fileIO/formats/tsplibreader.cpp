#include "tsplibreader.h"
#include <QFile>
#include <QString>
#include "graph/graphComp/node.h"
#include <QDebug>


TSPLibReader::TSPLibReader()
{
    SUPPTYPES << "TSP" << "HAM" << "TOUR";
    SUPPWEIGHTTYPES << "EUC_2D" << "GEO";
    IGNORETYPES << "COMMENT" << "DIMENSION";
}


void TSPLibReader::doIO()
{
    // read file
    QFile file(QString::fromStdString(_fileName));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);

    /* STEP 1: Handle the specification part of TSPLib file.
       Every TSPLib file has a specification part and a data part.
       We read every line one by one and validate them as following:
       Every line looks like <keyword> : <value> where we support following pairs:
       NAME : <string> || name of file and also name of graph
       TYPE : <string> || with <string> TSP, HCP, TOUR
       COMMENT : <string> || random graph content that gets ignored
       DIMENSION : <int> || number of noes
       EDGE_WEIGHT_TYPE : <string> || with <string> EUC_2D
       NODE_COORD_TYPE : <string> || with <string> TWOD_COORDS, NO_COORDS
       DISPLAY_DATA_TYPE : <string> || with <string> COORD_DISPLAY [display graph with coords] TWOD_DISPLAY [explicit coords] NO_DISPLAY
       EOF
    */

    parseSpecification(in);

    /* STEP 2: Handle the data part of the TSPLib file.
       When we get here, we just have to add all nodes and edges to our graphs
    */

    parseData(in);

}


void TSPLibReader::parseSpecification(QTextStream& in)
{
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        list.replaceInStrings(":", "");
        list.removeAll("");
        if (!list.empty())
        {
            // check first argument to decide what to do
            if (list.at(0) == "NAME")
                _graphPointer->setName(list.at(1).toStdString());
            else if (list.at(0) == "TYPE")
                validate(list.at(1), SUPPTYPES);
            else if (list.at(0) == "EDGE_WEIGHT_TYPE")
                validate(list.at(1), SUPPWEIGHTTYPES);
            else if (list.at(0) == "NODE_COORD_SECTION")
                return;
                // proceed to the parsing of the data
            else
                // we can just ignore certain specifications, such as author comments, dimension (because we just add the nodes while parsin the file)
                validate(list.at(0), IGNORETYPES);
        }
    }
}

void TSPLibReader::parseData(QTextStream& in)
{
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line == "EOF")
            return;
        QStringList list = line.split(" ", QString::SkipEmptyParts);
        // we can only read node info now
        _graphPointer->addNode(Node(Label(list.at(0).toStdString()), Point(list.at(1).toFloat(), -list.at(2).toFloat())));
    }

}


void TSPLibReader::validate(QString par, QStringList list)
{
    // is the type supported?
    if (!list.contains(par))
    {
        qDebug() << "THE STRING " << par << " IS NOT IN THE LIST " << list;
        exit(0);
    }
    // replace with throw

}
