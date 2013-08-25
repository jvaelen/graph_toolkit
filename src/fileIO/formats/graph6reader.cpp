#include "graph6reader.h"
#include <assert.h>
#include "graph/graphComp/node.h"
#include "exception/fileioex.h"

Graph6Reader::Graph6Reader()
{
    resetMembers();
}

void Graph6Reader::doIO()
{
    // reset the members, cleaning any leftovers from the last read
    resetMembers();
    unsigned numberOfNodes;
    // filename must be set
    assert(!_fileName.empty());
    // the graph in which the reading will happen has to be set, in other words, it can't be zero
    assert(_graphPointer);
    // prepare the characterstring, preparing the string will read the file, if the file can't be opened, an exception will be thrown in this function
    prepareCharStream();
    // if the header was invalid, we throw an exception
    if(!validateHeader())
        throw FileIOEx(_fileName, "the header in the file was invalid");
    numberOfNodes = readNumberOfNodes();
    // create the bitvector that can be easely interpreted by constructIntegerMatrix
    BitVector bitVector = prepareBitVector();
    // next we construct the integerMatrix
    IntegerMatrix integerMatrix = constructIntegerMatrix(numberOfNodes, bitVector);
    _graphPointer->recreateFrom(integerMatrix);
    _graphPointer->setName(getFileName(_fileName));
}

void Graph6Reader::resetMembers()
{
    _charStream.clear();
    _header = ">>graph6<<";
    _index = 0;
}

IntegerMatrix Graph6Reader::constructIntegerMatrix(unsigned NumberOfNodes, BitVector bitVector)
{
    // tell the bitVector we will now start reading (this will switch from the linked list to a vector)
    bitVector.setReadMode();
    IntegerMatrix result;
    for (unsigned i = 0; i < NumberOfNodes; ++i)
        result.addNode(Node(i));
    // used to keep track where we are in the bitvector
    unsigned bitCounter = 0;
    for (unsigned i = 0; i < NumberOfNodes; ++i)
        for(unsigned j = 0 ; j < i; ++j)
        {
            if(bitVector.bitAt(bitCounter))
            {
                result.addEdge(Node(i), Node(j));
                result.addEdge(Node(j), Node(i));
            }
            ++bitCounter;
        }

    return result;
}

bool Graph6Reader::validateHeader()
{
    // if the first charachter isn't a '>', then there is no header included, which is also valid
    if (_charStream.front() != '>')
        return true;
    // if the size of the file that has been read, is smaller than the minimum headersize, there can't be a valid header
    if(_charStream.size() < _header.size())
        return false;
    // we will check if the first string of characters in the _charStream equals to the header
    for (unsigned i = 0; i < _header.size(); ++i)
    {
        // if there is a charactermismatch, cancel and return false
        if(_charStream[i] != _header.at(i))
            return false;
    }
    vector<char> newCharStream;
    // at this point the header was valid
    // now we remove the header from the _charStream to reduce complication
    for(unsigned i = _header.size() ; i < _charStream.size(); ++i)
            newCharStream.push_back(_charStream[i]);
    _charStream = newCharStream;
    return true;
}

void Graph6Reader::prepareCharStream()
{
    char rc;
    FILE *fp = fopen(_fileName.c_str(), "rb");
    if (fp == NULL)
       throw FileIOEx(_fileName, "disk IO error, can't open file to read"); // TOOD: replace with exception
    while ((rc = getc(fp)) != EOF)
        _charStream.push_back(rc);
    fclose(fp);
}

unsigned Graph6Reader::readNumberOfNodes()
{
    // if the first character is 126, we know that the numberOfnodes is stored in the following 3 bytes
    if (_charStream[0] == 126)
    {
        unsigned temp[3];
        // the next 3 bytes are encoded in big endian form
        for (unsigned i = 0; i < 3; ++i)
        {
            temp[i] += _charStream[i];
            // shift the integer
            temp[i] <<= 6*i;
        }
        // update the index after reading the number of nodes
        _index += 3;
        return (temp[0] + temp[1] + temp[2]);
    }
    else
    {
        // update the index after reading the number of nodes
        _index++;
        return _charStream[0] - 63;
    }
}

BitVector Graph6Reader::prepareBitVector()
{
    BitVector bitVector;
    while(_index < _charStream.size() && _charStream[_index] != '\n')
    {
        bitVector.appendByte(_charStream[_index] - 63, 6);
        ++_index;
    }
    return bitVector;
}
