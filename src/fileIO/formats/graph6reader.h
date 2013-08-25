/*
 Author: Balazs Nemeth
 Description: graph6 reader that reads a graph from a g6 file format defined by Brendan McKay
     */
#ifndef GRAPH6READER_H
#define GRAPH6READER_H

#include "formathandlerstate.h"
#include <vector>
#include "graph/integermatrix.h"
#include "fileIO/bitvector.h"

class Graph6Reader : public FormatHandlerState
{
public:
    Graph6Reader();
    // does the action IO, it uses graph6 format defined by Brendan McKay.
    void doIO();
    IntegerMatrix constructIntegerMatrix(unsigned numberOfNodes, BitVector bitVector);
    string getDescription() const {return description();}
    string getExtension() const {return extention();}
    static string extention() {return "g6";}
    static string description() { return "Graph 6 fileformat as defined by Brendan McKay";}
private:
    // returns true if the _charStream has a valid header
    bool validateHeader();
    // reads the file and puts the characters(bytes) into _charStream
    void prepareCharStream();
    // read the number of nodes
    unsigned readNumberOfNodes();
    // reads from _index to EOF or until '\n' is found and returns the bitvector read (taking only 6 bits of each byte)
    BitVector prepareBitVector();
    // reset membervariables so that when we want to reuse the class for loading another file, there will be no problems
    void resetMembers();
    // header, this is tested for when reading a graph6 file format
    string _header;
    // the string of characters(bytes) in the file is first read to the _charStream for later processing, note that the EOF character is not saved in the list
    vector<char> _charStream;
    // integer to keep track to where we have processed the _charStream
    unsigned _index;
};

#endif // GRAPH6READER_H
