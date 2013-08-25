/*
 Author: Balazs Nemeth
 Description: graph6 reader that reads a graph from a g6 file format defined by Brendan McKay
     */
#ifndef GRAPH6WRITER_H
#define GRAPH6WRITER_H

#include "formathandlerstate.h"
#include "fileIO/bitvector.h"
#include "fileIO/bitvector.h"

class Graph6Writer : public FormatHandlerState
{
public:
    Graph6Writer();
    // this function will actually handle all the IO and writes the graph out, using the graph6 format defined by Brendan McKay, it accomplishes it's task by using the helpfunctions
    void doIO();
    string getDescription() const {return description();}
    string getExtension() const {return extention();}
    static string extention() {return "g6";}
    static string description() { return "Graph 6 fileformat as defined by Brendan McKay";}
private:
    // helpfunction
    BitVector constructBitvector(vector<vector<unsigned> >& matrix);
    vector<char> encodeNumberOfNodes(unsigned number);
    string prepareString(BitVector bitVector, unsigned numberOfnodes);
    string _header;
};

#endif // GRAPH6WRITER_H
