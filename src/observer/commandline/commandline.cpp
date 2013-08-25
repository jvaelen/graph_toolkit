#include "commandline.h"
#include <iostream>
#include "graph/listgraph.h"
#include "graph/matrixgraph.h"
#include "graph/hybridgraph.h"
#include "exception/unexistingedgeex.h"
#include "exception/unexistingnodeex.h"
#include "exception/uniqueedgeex.h"
#include "exception/uniquenodeex.h"

CommandLine::CommandLine()
{
    _workingGraph = NULL;
}

CommandLine::~CommandLine()
{
    delete _workingGraph;
}

void CommandLine::start()
{
    // what graph do you want to create?
    int graphType = determineGraphType();
    createGraph(graphType);
    while (1) {
        int operation = determineOperation();
        doOperation(operation);
    }
    // determineOperation()
    // doOperation() ->>> add notifyObservers() aan alle functies die de structuur van subject (Grafen, matrix en list) veranderen
    // dus bv addNode() moet nu op het einde een notifyObservers krijgen zodat alle observers van die graaf weten dat er een node
    // is toegevoegd |- notify() { } van een observer zou dan zeggen van tt teken mij helemaal opnieuw

}

int CommandLine::determineOperation()
{
    int operation;
    showOperationMenu();
    operation = getInput(0,6);
    while (operation == -1)
    {
        clear();
        cout << "\nInvalid choice, please try again...\n";
        showOperationMenu();
        operation = getInput(0,6);
    }
    return operation;
}

void CommandLine::showOperationMenu()
{
    cout << "\n\nBaloen GraphToolKit";
    cout << "\n-------------------\n\n";
    cout << "What operation would you like to do?\n\n";
    cout << "1. Add a node\n";
    cout << "2. Remove a node\n";
    cout << "3. Add an edge\n";
    cout << "4. Remove an edge\n";
    cout << "5. Print graph\n";
    cout << "6. Print graph with node ID's instead of labels\n";
    cout << "0. Exit\n";
    cout << "\nChoose one of the previous options by inserting the corresponding number.\n";
    cout << "\nChoice: ";
}

int CommandLine::determineGraphType()
{
    int type;
    showGraphMenu();
    type = getInput(1,3);
    while (type == -1)
    {
        clear();
        cout << "\nInvalid choice, please try again...\n";
        showGraphMenu();
        type = getInput(1,3);
    }
    return type;
}

int CommandLine::getInput(int lowerbound, int upperbound)
{
    string in;
    cin >> in;
    int inputInt = toInt(in);
    // if (our input wasn't an integer OR it does not lay in our bounds) return -1, else return the integer
    if (inputInt == -1 || inputInt < lowerbound || inputInt > upperbound)
        return -1;
    else
        return inputInt;
}

int CommandLine::toInt(string str)
{
    bool stop = false;

    // run through string and check if all chars are integers
    for (int i = 0; i < (int)str.size() && !stop; ++i)
    {
        if (str[i] < '0' || str[i] > '9')
            stop = true;
    }

    // we did not have to stop -> string is an integer
    if (!stop)
        return atoi(str.c_str());

    // failure
    return -1;
}

void CommandLine::showGraphMenu()
{
    cout << "Baloen GraphToolKit";
    cout << "\n-------------------\n\n";
    cout << "What type of graph would you like to create?\n\n";
    cout << "1. Adjacency list implementation\n";
    cout << "2. Adjacency matrix implementation\n";
    cout << "3. Hybrid implementation\n";
    cout << "\nChoose one of the previous options by inserting the corresponding number.\n";
    cout << "\nChoice: ";
}

void CommandLine::createGraph(int type)
{
    switch (type)
    {
    // adj list
    case 1:
        _workingGraph = new ListGraph();
        _workingGraph->registerObserver(this);
        cout << "\nGraph (list implementation) was created!\n";
        break;

        // adj matrix
    case 2:
        _workingGraph = new MatrixGraph();
        _workingGraph->registerObserver(this);
        cout << "\nGraph (matrix implementation) was created!\n";
        break;

        // hybrid
    case 3:
        _workingGraph = new HybridGraph();
        _workingGraph->registerObserver(this);
        break;

        // invalid, should never get here because of getInput()
    default:
        cout << "Invalid graph type!\n Exiting program...\n";
        exit(0);
        break;
    }

}

void CommandLine::doOperation(int operation)
{
    switch (operation)
    {
    // exit
    case 0:
        cout << "\nExiting program...\n";
        exit(0);
        break;

        // add node
    case 1:
        addNodeOperation();
        break;

        // remove node
    case 2:
        removeNodeOperation();
        break;

        // add edge
    case 3:
        addEdgeOperation();
        break;

        // remove edge
    case 4:
        removeEdgeOperation();
        break;

        // print
    case 5:
        printGraph();
        break;

        // print by id
    case 6:
        printGraphID();
        break;

        // invalid, should never get here because of getInput()
    default:
        cout << "Invalid operation!\n Exiting program...\n";
        exit(0);
        break;
    }
}

void CommandLine::addNodeOperation()
{
    string label;
    cout << "\nInsert the node's label: ";
    cin.ignore(); // buffer flush
    getline(cin, label);
    try {
        _workingGraph->addNode(Node(label));
    }
    catch (UniqueNodeEx e) {
        cout << endl << e.getMessage() << endl;
    }
}

void CommandLine::removeNodeOperation()
{
    string input;
    int id;
    cout << "\nInsert the node's id: ";
    cin.ignore(); // buffer flush
    getline(cin, input);
    id = toInt(input);
    while (id == -1)
    {
        cout << "\nInvalid input, please insert an integer greater than or equal to zero.";
        cout << "\nInsert the node's id: ";
        getline(cin, input);
        id = toInt(input);
    }
    try {
        _workingGraph->removeNode((unsigned int)id);
    }
    catch (UnexistingNodeEx e) {
        cout << endl << e.getMessage() << endl;
    }
}


void CommandLine::addEdgeOperation()
{
    string nodeFrom, nodeTo, edgeLabel;
    int nodeFromID, nodeToID;

    cout << "\nFrom node (ID): ";
    cin.ignore(); // buffer flush
    getline(cin, nodeFrom);
    nodeFromID = toInt(nodeFrom);
    while (nodeFromID == -1)
    {
        cout << "\nInvalid input, please insert an integer greater than or equal to zero.";
        cout << "\nFrom node (ID): ";
        getline(cin, nodeFrom);
        nodeFromID = toInt(nodeFrom);
    }

    cout << "\nTo node (ID): ";
    getline(cin, nodeTo);
    nodeToID = toInt(nodeTo);
    while (nodeToID == -1)
    {
        cout << "\nInvalid input, please insert an integer greater than or equal to zero.";
        cout << "\nTo node (ID): ";
        getline(cin, nodeTo);
        nodeToID = toInt(nodeTo);
    }

    cout << "\nEdge label: ";
    getline(cin, edgeLabel);
    try {
        _workingGraph->addEdge((unsigned int)nodeFromID, (unsigned int)nodeToID, edgeLabel);
    }
    catch (UnexistingEdgeEx e) {
        cout << endl << e.getMessage() << endl;
    }
    catch (UniqueEdgeEx ue) {
        cout << endl << ue.getMessage() << endl;
    }
}

void CommandLine::removeEdgeOperation()
{
    string nodeFrom, nodeTo, edgeLabel;
    int nodeFromID, nodeToID;

    cout << "\nFrom node (ID): ";
    cin.ignore(); // buffer flush
    getline(cin, nodeFrom);
    nodeFromID = toInt(nodeFrom);
    while (nodeFromID == -1)
    {
        cout << "\nInvalid input, please insert an integer greater than or equal to zero.";
        cout << "\nFrom node (ID): ";
        getline(cin, nodeFrom);
        nodeFromID = toInt(nodeFrom);
    }

    cout << "\nTo node (ID): ";
    getline(cin, nodeTo);
    nodeToID = toInt(nodeTo);
    while (nodeToID == -1)
    {
        cout << "\nInvalid input, please insert an integer greater than or equal to zero.";
        cout << "\nTo node (ID): ";
        getline(cin, nodeTo);
        nodeToID = toInt(nodeTo);
    }

    cout << "\nEdge label: ";
    getline(cin, edgeLabel);
    try {
        _workingGraph->removeEdge((unsigned int)nodeFromID, (unsigned int)nodeToID, edgeLabel);
    }
    catch (UnexistingEdgeEx e) {
        cout << endl << e.getMessage() << endl;
    }
}

void CommandLine::printGraph()
{
    // functie aan List en Matrix print toevoegen zoda we kunne polychille?
    // heb da ff gdn
    cout << endl;
    cout << _workingGraph->toString();
}

void CommandLine::printGraphID()
{
    cout << endl;
    cout << _workingGraph->toStringID();
}

void CommandLine::clear() const
{
    for (unsigned i = 0; i < 100; ++i)
        cout << endl;
}
