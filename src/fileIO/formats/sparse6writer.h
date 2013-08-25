#ifndef SPARSE6WRITER_H
#define SPARSE6WRITER_H

#include "formathandlerstate.h"
#include "fileIO/bitvector.h"


class Sparse6Writer : public FormatHandlerState
{
public:
    Sparse6Writer();
    string getDescription() const {return description();}
    string getExtension() const {return extention();}
    static string extention() {return "s6";}
    static string description() { return "Sparse 6 fileformat as defined by Brendan McKay";}
    void doIO();
private:
    // the function R as described by Brendan McKay
    string prepareString(BitVector bitVector, unsigned numberOfnodes);
    // returns true if the variable passed is a multiple of 2
    bool isMutipleOfTwo(unsigned numberOfNodes);
    // decides how to pad the bitvector
    void padUp(BitVector& bitVector, unsigned numberOfNodes, unsigned k, bool last, bool beforeLast);
    // helper funciton to easely add a pair the the vector
    void addToGroup(unsigned firstNumber, unsigned secondnumber, vector<pair<unsigned, unsigned> >& group);
    BitVector constructBitvector(vector<pair<unsigned, unsigned> >& groups, unsigned sizeOfGroups);
    // purly for debugging perpouse
    string printGroups(const vector<pair<unsigned, unsigned> >& groups);
    // creates the groups as described in the analysis report
    vector<pair<unsigned, unsigned> > constructGroups(const IntegerMatrix& integerMatrix);
    // encodes the number with the N function defined by Brendan McKay
    vector<char> encodeNumberOfNodes(unsigned number);
    // resets all the member variables, the doIO() function starts with this so that it can start cleanly
    void reset();
    // the string holds the header
    string _header;
};

#endif // SPARSE6WRITER_H
