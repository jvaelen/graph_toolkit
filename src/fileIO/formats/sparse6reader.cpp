#include "sparse6reader.h"
#include "graph/integermatrix.h"
#include "fileIO/bitvector.h"
#include <cmath>

Sparse6Reader::Sparse6Reader()
{

}

void Sparse6Reader::reset()
{
    _header = ">>sparse6<<";
    _index = 0;
}

void Sparse6Reader::doIO()
{
    reset();
    // this is the matrix that we will use to read the sparse6 format into
    IntegerMatrix integerMatrix;
    // read the characters from the file into the charstream
    prepareCharStream();
    // will remove the header from the front of the file if there is any
    if (!removeHeader())
        throw FileIOEx(_fileName, "invalid fileheader");
    if (!removeFrontChar())
        throw FileIOEx(_fileName, "missing ':', this is required as Brendan McKay states");

    // bitvector now holds the bit's that are read from the file
    BitVector bitVector = prepareBitVector();
    // we can active readMode from here on as we will only be reading from the bitvector
    bitVector.setReadMode();
    unsigned numberOfNodes = readNumberOfNodes();

    // if the number of nodes is 0, cancel reading any further
    if (numberOfNodes == 0)
        return ;

    vector<pair<unsigned, unsigned> > groups = getGroups(ceil(log2(numberOfNodes - 1)), bitVector, numberOfNodes);
    // create the nodes
    for (unsigned i = 0; i < numberOfNodes; ++i)
        integerMatrix.addNode(Node("node" + Label(integerMatrix.getNumberOfNodes()).getLabelString()));
    parseGroups(groups, integerMatrix);
    _graphPointer->recreateFrom(integerMatrix);
    _graphPointer->setName(getFileName(_fileName));
}

void Sparse6Reader::parseGroups(const vector<pair<unsigned, unsigned> >& groups, IntegerMatrix& integerMatrix)
{
    unsigned v = 0;
    for (unsigned i = 0; i < groups.size(); ++i)
    {
        if (groups[i].first != 0)
            v++;

        if  (groups[i].second > v)
            v = groups[i].second;
        else
        {
            integerMatrix.addEdge(Node("node" + Label(groups[i].second).getLabelString()), Node("node" + Label(v).getLabelString()));
        }
    }
}

BitVector Sparse6Reader::prepareBitVector()
{
    BitVector bitVector;
    while(_index < _charStream.size() && _charStream[_index] != '\n')
    {
        bitVector.appendByte(_charStream[_index] - 63, 6);
        ++_index;
    }
    return bitVector;
}

bool Sparse6Reader::removeFrontChar()
{
    if (_charStream[0] != ':')
        return false;

    vector<char> newCharStream;
    // remove the : at the begining of the _charStream
    for(unsigned i = 1; i < _charStream.size(); ++i)
        newCharStream.push_back(_charStream[i]);
    _charStream = newCharStream;
    return true;
}

vector<pair< unsigned, unsigned> > Sparse6Reader::getGroups(unsigned groupSize, const BitVector& bitVector, unsigned numberOfNodes)
{
    vector<pair <unsigned, unsigned> > result;
    pair<unsigned, unsigned> tempPair;
    tempPair.first = 0;
    tempPair.second = 0;
    bool started = false;

    unsigned startIndex = false;
    for (unsigned i = _index; i < bitVector.size(); ++i)
    {
        // if this condition holds, we need to read 1 byte, basicly the body of the iftest is executed before every group
        if ((i - _index)% (groupSize + 1) == 0)
        {
            tempPair.first = (bitVector.bitAt(i))? 1 : 0;
            result.push_back(tempPair);
        }
        else
        {
            if (!started)
            {
                started = true;
                startIndex = i;
            }
            // if this is the last bit in the group
            if ((i + 1 - _index) % (groupSize +1) == 0)
            {
                result[result.size()-1].second = bitVector.getIntBit(startIndex, i - startIndex + 1);
                started = false;
            }
        }
    }

    // clean any invalid edges at the end that may have been caused by padding
    for (unsigned i = result.size() - 1; i != 0; --i)
    {
        if (result[i].second >= numberOfNodes)
            result.pop_back();
    }
    return result;
}

bool Sparse6Reader::removeHeader()
{
    if (_charStream[0] != '>')
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
    for(unsigned i = _header.size(); i < _charStream.size(); ++i)
        newCharStream.push_back(_charStream[i]);
    _charStream = newCharStream;
    return true;
}

void Sparse6Reader::prepareCharStream()
{
    _charStream.clear();
    char rc;
    FILE *fp = fopen(_fileName.c_str(), "rb");
    if (fp == NULL)
        throw FileIOEx(_fileName, "disk IO error, can't open file to read"); // TOOD: replace with exception
    while ((rc = getc(fp)) != EOF)
        _charStream.push_back(rc);
    fclose(fp);
}

unsigned Sparse6Reader::readNumberOfNodes()
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

string Sparse6Reader::printGroups(const vector<pair<unsigned, unsigned> >& groups)
{
    string temp = "";
    for (unsigned i = 0; i < groups.size(); ++i)
        temp += "(" + Label(groups[i].first).getLabelString() + ", " + Label(groups[i].second).getLabelString() + ") ";
    return temp;
}
