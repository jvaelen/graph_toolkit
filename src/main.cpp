#include <iostream>
#include <QDebug>
#include <string>
#include <vector>

#include "graphtoolkit.h"
#include "graph/matrixgraph.h"
#include "graph/listgraph.h"
#include "graph/hybridgraph.h"
#include "graph/graphComp/node.h"
#include "exception/invalidformatex.h"
#include "observer/commandline/commandline.h"
#include "exception/uniqueedgeex.h"
#include "exception/uniquenodeex.h"
#include "fileIO/formats/graphmlreader.h"
#include "fileIO/formats/graphmlwriter.h"
#include "fileIO/formatprototypemanager.h"
#include "fileIO/formathandler.h"
#include "fileIO/bitvector.h"
#include "graph/integermatrix.h"
#include "fileIO/formats/graph6writer.h"
#include "fileIO/formats/graph6reader.h"
#include "fileIO/formats/graphmlreader.h"
#include "fileIO/formats/tsplibreader.h"
#include "visitor/graphtheoryvisitors/breadthfirstsearchvisitor.h"
#include "visitor/graphtheoryvisitors/depthfirstsearchvisitor.h"
#include "visitor/graphtheoryvisitors/stronglyconnectedcomponentsvisitor.h"

#include <QApplication>

#include "observer/GUI/graphtoolkitwindow.h"
#include "graphtoolkit.h"

using namespace std;

//#define BALDEBUG 1
//#define JERDEBUG 1

int main(int argc, char* argv[])
{
#ifdef JERDEBUG

    Graph* test = new ListGraph("http://www.youtube.com/watch?v=or9xlA3YYzo");
    test->addNode(string("A"));
    test->addNode(string("B"));
    test->addNode(string("C"));
    test->addNode(string("D"));
    test->addNode(string("E"));
    test->addNode(string("F"));
    test->addNode(string("G"));
    test->addNode(string("H"));
    // A-edges
    test->addEdge((unsigned int)0,(unsigned int)1, Label(""));
    test->addEdge((unsigned int)1,(unsigned int)0, Label(""));
    test->addEdge((unsigned int)0,(unsigned int)3, Label(""));
    test->addEdge((unsigned int)3,(unsigned int)0, Label(""));
    test->addEdge((unsigned int)0,(unsigned int)6, Label(""));
    test->addEdge((unsigned int)6,(unsigned int)0, Label(""));
    // B-edges
    test->addEdge((unsigned int)5,(unsigned int)1, Label(""));
    test->addEdge((unsigned int)1,(unsigned int)5, Label(""));
    test->addEdge((unsigned int)4,(unsigned int)1, Label(""));
    test->addEdge((unsigned int)1,(unsigned int)4, Label(""));
    // C-edges
    test->addEdge((unsigned int)2,(unsigned int)5, Label(""));
    test->addEdge((unsigned int)5,(unsigned int)2, Label(""));
    test->addEdge((unsigned int)2,(unsigned int)7, Label(""));
    test->addEdge((unsigned int)7,(unsigned int)2, Label(""));
    // D-edges
    test->addEdge((unsigned int)3,(unsigned int)5, Label(""));
    test->addEdge((unsigned int)5,(unsigned int)3, Label(""));
    // G-edges
    test->addEdge((unsigned int)4,(unsigned int)6, Label(""));
    test->addEdge((unsigned int)6,(unsigned int)4, Label(""));

    StronglyConnectedComponentsVisitor bfs;
    test->accept(bfs);
    test->accept(bfs);
    test->accept(bfs);
    qDebug() << "schill";

#endif

#ifdef BALDEBUG
#endif

    vector<string> arguments;
    // first we copy all the arguments in a vector of Strings to be able to easely get the size and compare to commands
    for (int i = 0; i < argc; ++i)
        arguments.push_back(string(argv[i]));
    if ((argc == 2 && arguments[1] == string("-cmd")))
    {
        CommandLine c;
        c.start();
    }
    else if(argc == 4 && arguments[1] == string("-c"))
    {
        GraphToolKit graphToolKit;
        try
        {
        graphToolKit.openGraph(arguments[2]);
        graphToolKit.saveGraph(arguments[3]);
        }
        catch(InvalidFormatEx e)
        {
            cout << e.getMessage() << "\n";
        }
    }
    else
    {
        // pass Qt the arguments
        QApplication a(argc, argv);
        // create the first window that the user sees
        GraphToolKitWindow graphToolKitWindow;
        // before we show that window, register it as an observer of GraphToolKit
        GraphToolKit graphToolKit;
        graphToolKit.registerObserver(&graphToolKitWindow);
        graphToolKit.notifyObservers();
        graphToolKitWindow.show();
        // if there is a second parameter that looks like a file
        if (argc == 2 && (arguments[1].at(0) == '.' || arguments[1].at(0) == '/' || (arguments[1].size() > 3)))
            graphToolKit.openGraph(argv[1]);
        return a.exec(); // a.exec() will start the gui application
    }
    return 0;
}
