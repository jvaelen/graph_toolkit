#include "graph6writer.h"
#include <assert.h>
#include <fstream>

Graph6Writer::Graph6Writer()
{
    _header = ">>graph6<<";
}

void Graph6Writer::doIO()
{
    // if the graphPointer has not been set, this can only occur by programming error
    assert(_graphPointer);
    // filename can't be empty
    assert(!_fileName.empty());
    // the graph
    IntegerMatrix integerMatrix = _graphPointer->getIntegerMatrix();
    vector<vector<unsigned> > matrix = integerMatrix.getMatrix();
    integerMatrix.toUndirected();
    // from this point we can work with the toptriangular part of matrix to construct the bitvector that will eventually be written out
    BitVector bitVector = constructBitvector(matrix);
    // pad up to multiples of 6
    bitVector.padR();
    string graph = prepareString(bitVector, integerMatrix.getNumberOfNodes());
    // open a filestream
    fstream fileStream(_fileName.c_str(), ios::out);
    // the format is defined so that after the header there is no linebreak
    fileStream << _header;
    fileStream << graph;
    fileStream.close();
}

string Graph6Writer::prepareString(BitVector bitVector, unsigned numberOfnodes)
{
    // the graph is saved as a string starting with the number of nodes
    string result;
    vector<char> encodeN = encodeNumberOfNodes(numberOfnodes);
    // add the first sequence of bytes that encode the numberOfNodes (this can be more than one byte)
    for (unsigned i = 0; i < encodeN.size(); ++i)
        result += encodeN[i];
    // add the edges
    for (unsigned i = 0; i < bitVector.size(); i += 6)
       result += (char)(bitVector.getIntBit(i, 6) + 63);
    return result;
}

BitVector Graph6Writer::constructBitvector(vector<vector<unsigned> >& matrix)
{
    BitVector bitVector;
    for (unsigned i = 0; i < matrix.size(); ++i)
        for (unsigned j = 0; j < matrix[0].size() && j < i; ++j)
            // we can just use the integers  as booleans, this is so because graph6 doesn't support multiple edges
             bitVector.appendBit(matrix[j][i]);
    return bitVector;
}

vector<char> Graph6Writer::encodeNumberOfNodes(unsigned number)
{
    vector<char> result;
    // three cases
    if (number <= 62)
        result.push_back(number+63);
    else /* if(number <= 258047) */
    {
        // the first characer is 126
        result.push_back(126);
        BitVector tempVector(number);
        tempVector.padL(18);
        result.push_back(tempVector.getIntBit(0, 6));
        result.push_back(tempVector.getIntBit(6, 6));
        result.push_back(tempVector.getIntBit(12, 6));
    }
    return result;
}
