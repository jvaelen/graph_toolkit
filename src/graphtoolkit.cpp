#include <assert.h>

#include "graphtoolkit.h"

// graph structures
#include "graph/listgraph.h"
#include "graph/matrixgraph.h"
#include "graph/hybridgraph.h"

// tools
#include "tools/addedgetool.h"
#include "tools/addnodetool.h"
#include "tools/removeedgetool.h"
#include "tools/removenodetool.h"
#include "tools/selectandmovetool.h"

// supported file formats
#include "fileIO/formats/graph6reader.h"
#include "fileIO/formats/graph6writer.h"
#include "fileIO/formats/graphmlreader.h"
#include "fileIO/formats/graphmlwriter.h"
#include "fileIO/formats/tsplibreader.h"
#include "fileIO/formats/sparse6reader.h"
#include "fileIO/formats/sparse6writer.h"
#include "fileIO/formats/dotwriter.h"
#include "fileIO/formats/dotreader.h"

// graph drawing algorithms
#include "visitor/graphdrawingvisitors/standardlayoutvisitor.h"
#include "visitor/graphdrawingvisitors/forcedirectedvisitor.h"
#include "visitor/graphdrawingvisitors/barycentricdrawer.h"

// graph theory algorithms
#include "visitor/graphtheoryvisitors/breadthfirstsearchvisitor.h"
#include "visitor/graphtheoryvisitors/depthfirstsearchvisitor.h"
#include "visitor/graphtheoryvisitors/stronglyconnectedcomponentsvisitor.h"
#include "visitor/graphtheoryvisitors/hamcyclevisitor.h"
#include "visitor/graphtheoryvisitors/hampathvisitor.h"
#include "visitor/graphtheoryvisitors/kruskalvisitor.h"

// property visitors
#include "visitor/propertyvisitors/connectedvisitor.h"
#include "visitor/propertyvisitors/undirectedvisitor.h"
#include "visitor/propertyvisitors/cyclevisitor.h"
#include "visitor/propertyvisitors/weightedvisitor.h"
#include "visitor/propertyvisitors/completevisitor.h"


#ifdef WIN32
 #define WINDOWS
#elif WIN64
 #define WINDOWS
#endif
#ifdef WINDOWS
#include <windows.h>
#include <time.h>
#endif


GraphToolKit::GraphToolKit()
{
    // prevent dangling pointers
    _focusGraph = NULL;
    // seed the random generator
    srand(time(NULL));
    // create all the tools
    setUpTools();
    // adds all the supported file format readers and writers
    setupFileFormats();
    // setup all the algorithmes that can be used on graphs
    setupGraphDrawingVisitors();
    setupGraphTheoryVisitors();
    setupPropertyVisitors();
}

GraphToolKit::~GraphToolKit()
{
    // delete the working graphs, by doing this in the reverse order, we only need to ask the size once.
    for (int i = _workingGraphs.size() - 1; i >= 0; --i)
    {
        delete _workingGraphs[i];
    }
    // clear on the vectors would be mandetory
}

void GraphToolKit::setUpTools()
{
    // create the toolset, this set will hold instances of all the tools that the user can use to manipulate graphs
    _tools.addTool(new SelectAndMoveTool("Select Tool", "selection tool to select, move and edit nodes and edges", ":/tools/resources/select.png"));
    _tools.addTool(new AddNodeTool("Add Node", "use this tool to add nodes to the graph", ":/tools/resources/addNode.png"));
    _tools.addTool(new RemoveNodeTool("Remove Node", "use this tool to remove nodes from the graph", ":/tools/resources/removeNode.png"));
    _tools.addTool(new RemoveEdgeTool("Remove Edge", "use this tool to remove edges from the graph", ":/tools/resources/removeEdge.png"));
    _tools.addTool(new AddEdgeTool("Add Edge", "use this tool to add edges to the graph", ":/tools/resources/addEdge.png"));
    // the default tool is the selectiontool
    _tool.setState(_tools.getTool(SELECTTOOL));
}

void GraphToolKit::changeFocusGraphStructure(GraphType type)
{
    // if the assertion doesn't fail, getFocusID() will work correctly
    assert(_focusGraph);
    int focusID = getFocusID();
    // set the new type
    _workingGraphTypes[focusID] = type;
    _workingGraphs[focusID] = createGraph(type, _focusGraph->getName(), _focusGraph);
    // delete the old graph that we had before
    delete _focusGraph;
    _lastRemovedGraphs.push_back(_focusGraph);
    // update the fucosGraph pointer
    _focusGraph =_workingGraphs[focusID];
    _lastAddedGraphs.push_back(_focusGraph);
    // update the tool with the new pointer
    _tool.setGraph(_focusGraph);
    // notify the observers that may need to update the display to reflect the selected focusGraph
    notifyObservers();
}

Graph* GraphToolKit::createGraph(GraphType type, string name, Graph* other)
{
    Graph* newGraph = NULL;
    switch(type)
    {
    case HYBRID:
        if(other) // if the other parameter has been set
            newGraph = new HybridGraph(*other);
        else
            newGraph = new HybridGraph(name);
        break;
    case LIST:
        if(other) // if the other parameter has been set
            newGraph = new ListGraph(*other);
        else
            newGraph = new ListGraph(name);
        break;
    case MATRIX:
        if(other) // if the other parameter has been set
            newGraph = new MatrixGraph(*other);
        else
            newGraph = new MatrixGraph(name);
        break;
    default:
        assert(NULL); // can never be this, and can only be caused by programming error
    }
    return newGraph;
}

void GraphToolKit::removeGraph(unsigned id)
{
    assert(id < _workingGraphs.size());
    /* add the pointer of the graph that will be removed to the _lastRemovedGraphs vector so that it
        can be used efficiently to remove the graphs from the view instead of checking all the graphs in a brute force manner */
    _lastRemovedGraphs.push_back(_workingGraphs[id]);
    _tool.clearActionsForGraph(_workingGraphs[id]);
    // notify propertyPM that the graph is removed
    _propertyPrototypeManager.notifyGraphRemoved(_workingGraphs[id]);
    // free up the memory allocated by the graph
    delete _workingGraphs[id];
    // erase that element from the working graphs
    _workingGraphs.erase(_workingGraphs.begin() + id);
    _workingGraphTypes.erase(_workingGraphTypes.begin() + id); // don't need to delete because its a value type
    if (!_workingGraphs.empty())
    {
        _focusGraph = _workingGraphs[id ? id - 1 : 0];
        _tool.setGraph(_focusGraph);
        _propertyPrototypeManager.setFocusGraph(_focusGraph);
    }
    else
        // we set this so we get N/A instead of false as property results
        _propertyPrototypeManager.setFocusGraph(NULL);
    notifyObservers();
}

Graph* GraphToolKit::addGraph(GraphType type, string name)
{
    Graph* newGraph = NULL;
    newGraph = createGraph(type, name);
    // add the newly created graph to the vector of graphs
    _workingGraphs.push_back(newGraph);
    _workingGraphTypes.push_back(type);
    // set that graph as the focus graph
    _focusGraph = newGraph;
    /* add the pointer of the new graph _lastAddedGraphs vector so that it
        can be used efficiently to add the graphs to the view instead of checking all the graphs in a brute force manner */
    _lastAddedGraphs.push_back(newGraph);
    // by setting a new focusGraph, the subjects get notified
    setFocusGraph(_workingGraphs.size()-1);
    return newGraph;
}

vector<Graph*> GraphToolKit::getLastRemovedGraphs()
{
    vector<Graph*> temp = _lastRemovedGraphs;
    _lastRemovedGraphs.clear();
    return temp;
}

vector<Graph*> GraphToolKit::getLastAddedGraphs()
{
    vector<Graph*> temp = _lastAddedGraphs;
    _lastAddedGraphs.clear();
    return temp;
}

void GraphToolKit::setFocusGraph(unsigned id)
{
    assert(id < _workingGraphs.size());
    _focusGraph = _workingGraphs[id];
    _tool.setGraph(_focusGraph);
    _propertyPrototypeManager.setFocusGraph(_focusGraph);
    notifyObservers();
}

Graph* GraphToolKit::getFocusGraph() const
{
    return _focusGraph;
}

GraphType GraphToolKit::getFocusGraphType() const
{
    int focusID = getFocusID();
    if (focusID != -1)
        return _workingGraphTypes[focusID];
    return INVALIDGRAPHTYPE;
}

int GraphToolKit::getFocusID() const
{
    for (unsigned i = 0; i < _workingGraphs.size(); ++i)
        if (_focusGraph == _workingGraphs[i])
            return i;
    // default value, shoudn't happen
    return -1;
}


void GraphToolKit::openGraph(string fileName)
{
    // set the right state (the reader to read the file
    _fileHandler.setState(_formatPrototypeManager.getReader(getExt(fileName) + "reader"));
    // this is the graph that will be loaded
    Graph* newGraph = new HybridGraph();
    // set the file that we want to read
    _fileHandler.setFileName(fileName);
    // we will load the graph in the newGraph pointer
    _fileHandler.setGraphPointer(newGraph);
    // start the load
    _fileHandler.doIO();
    // add it to the working graphs
    _workingGraphs.push_back(newGraph);
    _workingGraphTypes.push_back(HYBRID);
    // add it to the last added graphs
    _lastAddedGraphs.push_back(newGraph);
    // the forcusGraph is the last graph, we use this function to also update the _toolHandler
    setFocusGraph(_workingGraphs.size() - 1);
    _propertyPrototypeManager.setFocusGraph(_workingGraphs[_workingGraphs.size() - 1]);
    // don't have to notify the observers, setting the focus graph will do that
}

void GraphToolKit::saveGraph(string fileName)
{
    assert(_focusGraph);
    _fileHandler.setState(_formatPrototypeManager.getWriter(getExt(fileName) + "writer"));
    _fileHandler.setFileName(fileName);
    _fileHandler.setGraphPointer(_focusGraph);
    _fileHandler.doIO();
}

void GraphToolKit::makeComplete(Graph* graph)
{
    for (unsigned i = 0; i < graph->getNumberOfNodes(); ++i)
        for (unsigned j = 0; j < graph->getNumberOfNodes(); ++j)
        {
            if (i != j)
            {
                try
                {
                    graph->addEdge(i, j, Label(""));
                }
                catch(...)
                {
                }
            }
        }
}

void GraphToolKit::startRandomTest(int width, int height, double relation, unsigned actions)
{
    addGraph(HYBRID, "testgraph");
    // simulate actions
    unsigned numberOfNodes = rand() / static_cast<double>(RAND_MAX)*actions*relation;
    unsigned numberOfEdges = actions - numberOfNodes;

    for (unsigned i = 0; i < numberOfNodes; ++i)
    {
        Node newNode(_focusGraph->getNodeNameHint(), Point(width* (rand() / static_cast<double>(RAND_MAX)) - width/2, height*(rand() / static_cast<double>(RAND_MAX)) - height/2));
        _focusGraph->addNode(newNode);
    }

    for (unsigned i = 0; i < numberOfEdges; ++i)
    {
        try
        {
        _focusGraph->addEdge((unsigned int)(numberOfNodes*(rand() / static_cast<double>(RAND_MAX))),
                             (unsigned int)(numberOfNodes*(rand() / static_cast<double>(RAND_MAX))), Label());
        }
        catch(...)
        {

        }
    }
}

void GraphToolKit::setupGraphDrawingVisitors()
{
    _graphDrawingPrototypeManger.addVisitor(new StandardLayoutVisitor());
    _graphDrawingPrototypeManger.addVisitor(new ForceDirectedVisitor());
    _graphDrawingPrototypeManger.addVisitor(new BarycentricDrawer());
}

void GraphToolKit::setupGraphTheoryVisitors()
{
    _graphTheoryPrototypeManager.addVisitor(new BreadthFirstSearchVisitor);
    _graphTheoryPrototypeManager.addVisitor(new DepthFirstSearchVisitor);
    _graphTheoryPrototypeManager.addVisitor(new StronglyConnectedComponentsVisitor);
    _graphTheoryPrototypeManager.addVisitor(new HamCycleVisitor);
    _graphTheoryPrototypeManager.addVisitor(new HamPathVisitor);
    _graphTheoryPrototypeManager.addVisitor(new KruskalVisitor);
}

void GraphToolKit::setupFileFormats()
{
    // all the supported formats should be added here
    _formatPrototypeManager.addFormatReader(new GraphMLReader(), GraphMLReader::extention() + "reader");
    _formatPrototypeManager.addFormatWriter(new GraphMLWriter(), GraphMLWriter::extention() + "writer");
    _formatPrototypeManager.addFormatReader(new Graph6Reader(), Graph6Reader::extention() + "reader");
    _formatPrototypeManager.addFormatWriter(new Graph6Writer(), Graph6Writer::extention() + "writer");
    _formatPrototypeManager.addFormatReader(new TSPLibReader(), TSPLibReader::extention() + "reader");
    _formatPrototypeManager.addFormatWriter(new Sparse6Writer(), Sparse6Writer::extention() + "writer");
    _formatPrototypeManager.addFormatReader(new Sparse6Reader(), Sparse6Reader::extention() + "reader");
    _formatPrototypeManager.addFormatWriter(new DotWriter(), DotWriter::extention() + "writer");
    _formatPrototypeManager.addFormatReader(new DotReader(), DotReader::extention() + "reader");
}

void GraphToolKit::setupPropertyVisitors()
{
    _propertyPrototypeManager.addVisitor(new CompleteVisitor());
    _propertyPrototypeManager.addVisitor(new ConnectedVisitor());
    _propertyPrototypeManager.addVisitor(new UndirectedVisitor());
    _propertyPrototypeManager.addVisitor(new CycleVisitor());
    _propertyPrototypeManager.addVisitor(new WeightedVisitor());
}

void GraphToolKit::doDrawingNormal(int algorithm)
{
    // we need a graph that is being worked on
    assert(_focusGraph);
    // we then tell the graph to accept the visitor that had been saved in
    _focusGraph->accept(*(_graphDrawingPrototypeManger.getVisitor(algorithm)));
}

AlgorithmVisitor* GraphToolKit::doDrawingIterative(int algorithm)
{
    if (_focusGraph)
        _graphDrawingPrototypeManger.getVisitor(algorithm)->iterationStep(*_focusGraph);
    return _graphDrawingPrototypeManger.getVisitor(algorithm);
}

void GraphToolKit::doTheoryNormal(int algorithm)
{
    assert(_focusGraph);
    _focusGraph->accept(*(_graphTheoryPrototypeManager.getVisitor(algorithm)));
}

AlgorithmVisitor* GraphToolKit::doTheoryIterative(int algorithm)
{
    if (_focusGraph)
        _graphTheoryPrototypeManager.getVisitor(algorithm)->iterationStep(*_focusGraph);
    // this function returns an AlgorithmVisitor* because it is being used with a timer,
    // if (GTK->doTheoryIterative->getFinished()) stop; will first do an iteration and then return the visitor so getFinished() can be tested
    return _graphTheoryPrototypeManager.getVisitor(algorithm);
}

void GraphToolKit::checkProperty(int property)
{
    assert (_focusGraph);
    // sets _propertyResult to true / false
    _focusGraph->accept(*(_propertyPrototypeManager.getVisitor(property)));
}

void GraphToolKit::resetGraphDrawingAlgorithms()
{
    _graphDrawingPrototypeManger.resetAll();
}

string GraphToolKit::getExt(string inputString)
{
    string ext;
    unsigned i = 0;
    while (i < inputString.size())
    {
        if (inputString[i] == '.')
            ext = ""; // reset the extentionstring
        else
            ext += inputString[i];
        ++i;
    }
    return ext;
}
