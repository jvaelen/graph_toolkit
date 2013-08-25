#ifndef SPARSE6READER_H
#define SPARSE6READER_H

#include "formathandlerstate.h"
#include "exception/fileioex.h"

#include <vector>

class BitVector;
class Sparse6Reader : public FormatHandlerState
{
public:
    Sparse6Reader();
    string getDescription() const {return description();}
    string getExtension() const {return extention();}
    static string extention() {return "s6";}
    static string description() { return "Sparse 6 fileformat as defined by Brendan McKay";}
    void doIO();
    // resets the membervariables
    void reset();
private:
    // will parse the groups in the integerMatrix
    void parseGroups(const vector<pair<unsigned, unsigned> >& groups, IntegerMatrix& integerMatrix);
    // help function for debugging that returns a string with the groups in
    string printGroups(const vector<pair<unsigned, unsigned> >& groups);
    /* returns a set of 1,groupSize pairs read from the bitVector,
        every pair that has it's second equal or bigger than numberOfEdges are trimmed */
    vector<pair< unsigned, unsigned> > getGroups(unsigned groupSize, const BitVector& bitVector, unsigned numberOfNodes);
    // read the number of nodes from the bitvector
    unsigned readNumberOfNodes();
    // returns a bitvector that holds the bytes from the _charStream
    BitVector prepareBitVector();
    // removes the header from the charStream if there is any
    bool removeHeader();
    // checks and remove the ':' character at the beginning of the line
    bool removeFrontChar();
    // will read the file as a vector of characters in the _charStream
    void prepareCharStream();
    unsigned _index;
    vector<char> _charStream;
    string _header;
};

#endif // SPARSE6READER_H
