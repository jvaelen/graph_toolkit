/* Author: Jeroen Vaelen and Balazs Nemeth
   Description: Master class that delegates our entire Graph Tool Kit*/

#ifndef GRAPHTOOLKIT_H
#define GRAPHTOOLKIT_H

#include <vector>
#include <string>

#include "graph/graph.h"
#include "tools/toolhandler.h"
#include "fileIO/formathandler.h"
#include "fileIO/formatprototypemanager.h"
#include "fileIO/formats/formathandlerstate.h"
#include "tools/toolstate.h"
#include "tools/toolpm.h"
#include "observer/subject.h"
#include "visitor/algorithmvisitor.h"
#include "visitor/algorithmvisitorpm.h"
#include "visitor/propertyvisitorpm.h"

using namespace std;

/* GraphType enumeration used to determin the type of the graph,
    this information is only used to show to the user, interaction happens with a _graphpointer, no casting to actual graphs happens*/
enum GraphType { HYBRID, LIST, MATRIX, INVALIDGRAPHTYPE };

class GraphToolKit : public Subject
{
public:
    GraphToolKit();
    ~GraphToolKit();
    // starts the application
    void start();
    // add a new graph to the workin graphs database and set focus to it
    Graph* addGraph(GraphType type, string name); // moet mss gerefactored worden
    // change the graph we are currently working on
    void setFocusGraph(unsigned id);
    // returns the vector of working graphs making it possible to print all the graphs or show them in a gui outside this class, keeping model/view seperate
    vector<Graph*> getWorkingGraphs() const {return _workingGraphs;}
    // removeGraph
    void removeGraph(unsigned id);
    // returns the graph that has focus
    Graph* getFocusGraph() const;
    // returns the id of the graph that has focus in the vector of graphs
    int getFocusID() const;
    // opens the file in a new graph, it sets the right state for the format handler
    void openGraph(string fileName);
    ToolPM& getToolPM() {return _tools;}
    // returns a pointer to the ToolHandler so that it can be linked with the right observer
    ToolHandler* getToolHandler() { return &_tool; }
    // returns the type of the focus graph
    GraphType getFocusGraphType() const;
    // changes the structure of the graph that has focus
    void changeFocusGraphStructure(GraphType type);
    // the next two functions aren't const because they also clear the list
    vector<Graph*> getLastRemovedGraphs();
    vector<Graph*> getLastAddedGraphs();
    // function purly for testing
    void startRandomTest(int width, int height, double relation, unsigned actions);
    // function purly for testing
    void makeComplete(Graph* graph);
    // writes the focusGraph to the file given by fileName, the extention determines the encoding type
    void saveGraph(string fileName);
    // returns a string that is the substring starting from the last dot (.) in the string
    static string getExt(string inputString);
    // executes the algorithm with the type given by the name
    void doDrawingNormal(int algorithm);
    // will delegate one iteration call to the algorithms
    AlgorithmVisitor* doDrawingIterative(int algorithm);
    // run the graph theory algorithm entirely
    // seperate function because of the GUI seperation
    void doTheoryNormal(int algorithm);
    // run the graph theory algorithm iteratively
    AlgorithmVisitor* doTheoryIterative(int algorithm);
    // check for a property
    void checkProperty(int property);
    // returns a pointer to the propertyvistor
    const PropertyVisitorPM* getPropertyVisitorPM() const {return &_propertyPrototypeManager;}
    // returns a pointer to the algorithmvisitor
    AlgorithmVisitorPM* getAlgorithmVisitorPM() {return &_graphTheoryPrototypeManager;}
    void resetGraphDrawingAlgorithms();
    // delegates to the prototypemanager
    vector<string> getWriterExtensions() const { return _formatPrototypeManager.getWriterExtensions();}
    vector<string> getReaderExtensions() const { return _formatPrototypeManager.getReaderExtensions();}
    vector<string> getWriterDescriptions() const {return _formatPrototypeManager.getWriterDescriptions();}
    vector<string> getReaderDescriptions() const {return _formatPrototypeManager.getReaderDescriptions();}
    list<string> getGraphDrawingAlgoritmNames() const {return _graphDrawingPrototypeManger.getNames();}
    list<string> getGraphTheoryAlgorithmNames() const { return _graphTheoryPrototypeManager.getNames(); }
    list<string> getPropertyNames() const { return _propertyPrototypeManager.getNames(); }

private:
    // help functions
    /* returns a graphpointer to a graph that has the structure defined by type,
        if the Graph* is set (ie not NULL), it is used to pass to to the graph when creation happens */
    Graph* createGraph(GraphType type, string name, Graph* other = NULL);
    // sets up the fileFormats
    void setupFileFormats();
    // prototypemanager that manages the graphdrawing algorithms
    void setupGraphDrawingVisitors();
    // prototypemanager that manages the graphtheory algorithms
    void setupGraphTheoryVisitors();
    // prototypemanager that manages all the property visitors
    void setupPropertyVisitors();
    // sets up the nodes
    void setUpTools();
private:
    vector<Graph*> _workingGraphs;
    // the graphTypes are saved in a seperate vector because we wan't to prevent typechecking, we can this way tell the user what structure the graph is using
    vector<GraphType> _workingGraphTypes;
    Graph* _focusGraph;
    ToolHandler _tool;
    FormatHandler _fileHandler;
    // keep track of what graphs have been removed last, when getLastRemovedGraphs is called, this list is cleared
    vector<Graph*> _lastRemovedGraphs;
    // keep track of what graphs have been added last, when getLastAddedGraphs is called, this list is cleared
    vector<Graph*> _lastAddedGraphs;
    // this prototype manager manages all instances of fileformats
    FormatPrototypeManager _formatPrototypeManager;
    AlgorithmVisitorPM _graphDrawingPrototypeManger;
    AlgorithmVisitorPM _graphTheoryPrototypeManager;
    PropertyVisitorPM _propertyPrototypeManager;
    // keeps all the tools
    ToolPM _tools;
};

#endif // GRAPHTOOLKIT_H
