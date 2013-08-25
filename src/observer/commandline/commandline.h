/* Author: Jeroen Vaelen
   Description: CMD interface, made for testing purposes */


#ifndef COMMANDLINE_H
#define COMMANDLINE_H

#include "observer/observer.h"
#include <string>

#include <iostream>
using namespace std;

class Graph;

class CommandLine : public Observer
{
public:
    CommandLine();
    ~CommandLine();

    // start the interface
    void start();

    // in a GUI notify would redraw certain areas with the new information changed in the subject
    // but this is a CLI so do nothing
    void notify(Subject *subject) { subject = subject; cout << "\nNOTIFIED\n"; /* do nothing */ }

private:
    Graph* _workingGraph;

    // used to determine the graph type
    int determineGraphType();
    // used to create graph
    void createGraph(int type);
    // used to determine an operation (add a node, remove an edge, print graph, ...)
    int determineOperation();
    // do that operation
    void doOperation(int operation);

    // display menu's
    void showGraphMenu();
    void showOperationMenu();
    // simulating CMD clear/cls operation
    void clear() const;
    // return the input if it is between the bounds, if not return -1
    int getInput(int lowerbound, int upperbound);
    // returns the int value of the string or -1 if it's no int.
    int toInt(string str);

    // operations
    void addNodeOperation();
    void removeNodeOperation();
    void removeNodeByIDOperation();
    void addEdgeOperation();
    void removeEdgeOperation();
    void printGraph();
    void printGraphID();
};

#endif // COMMANDLINE_H
