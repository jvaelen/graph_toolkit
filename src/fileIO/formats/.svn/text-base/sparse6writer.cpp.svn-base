#include <QDebug>
#include <fstream>
#include <cmath>

#include "fileIO/bitvector.h"
#include "sparse6writer.h"

Sparse6Writer::Sparse6Writer()
{
    reset();
}

void Sparse6Writer::reset()
{
    _header = ">>sparse6<<";
}

void Sparse6Writer::doIO()
{
    IntegerMatrix integerMatrix = _graphPointer->getIntegerMatrix();
    // need the undirectedVersion
    integerMatrix.toUndirected();
    vector<pair<unsigned, unsigned> > groups = constructGroups(integerMatrix);

    unsigned numberOfNodes = integerMatrix.getNumberOfNodes();
    unsigned k = ceil(log2(numberOfNodes - 1));

    BitVector bitVector = constructBitvector(groups, k);

    bool last = false;
    bool beforeLast = false;

    if (numberOfNodes >= 2)
    {
        last = integerMatrix.nodeHasEdge(numberOfNodes - 1);
        beforeLast =  integerMatrix.nodeHasEdge(numberOfNodes - 2);
    }
    padUp(bitVector, numberOfNodes, k, last, beforeLast);

    string encodedGraph =  prepareString(bitVector, numberOfNodes);

    // open a filestream
    fstream fileStream(_fileName.c_str(), ios::out);
    // the format is defined so that after the header there is no linebreak
    fileStream << _header << ":"; // need the ':' character to identify s6 format
    fileStream << encodedGraph;
    fileStream.close();
}

string Sparse6Writer::prepareString(BitVector bitVector, unsigned numberOfnodes)
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

void Sparse6Writer::padUp(BitVector& bitVector, unsigned numberOfNodes, unsigned k, bool last, bool beforeLast)
{

    unsigned numberOfBitsToPad = 0;
    while ((bitVector.size() + numberOfBitsToPad) % 6 != 0)
        numberOfBitsToPad++;
    if ((numberOfNodes >= k + 1) && last && !beforeLast && isMutipleOfTwo(numberOfNodes))
        bitVector.appendBit(0);

    // pad to multiples of 6 with one's
    bitVector.padR(6, true);
}

bool Sparse6Writer::isMutipleOfTwo(unsigned numberOfNodes)
{
    unsigned counter = 2;
    while (counter < numberOfNodes)
        counter *= 2;
    return counter == numberOfNodes;
}

BitVector Sparse6Writer::constructBitvector(vector<pair<unsigned, unsigned> >& groups, unsigned sizeOfGroups)
{
    BitVector result;
    for (unsigned i = 0; i < groups.size(); ++i)
    {
        // append the b[i]
        result.appendBit(groups[i].first);
        // append sizeOfGroup bits of the integer groups[i].second
        result.appendByte(groups[i].second, sizeOfGroups);
    }
    return result;
}

vector<pair<unsigned, unsigned> > Sparse6Writer::constructGroups(const IntegerMatrix& integerMatrix)
{
    vector<pair<unsigned, unsigned> > group;
    vector< vector< unsigned> > matrix = integerMatrix.getMatrix();
    pair<unsigned, unsigned> lastEdge;
    unsigned multiEdgecounter;
    for (unsigned col = 0; col < matrix.size(); ++col)
        for (unsigned row = 0; row <= col; ++row)
        {
            // if there is at least one edge
            if (matrix[col][row])
            {
                // if we are dealing with the first edge
                if (group.empty())
                {
                    // if the first edge is from the first node to the first node
                    if (row == 0 && col == 0)
                    {
                        addToGroup(0, 0, group);
                    }
                    else
                    {
                        addToGroup(0, col, group);
                        addToGroup(0, row, group);
                    }
                }
                // 2 choices, we stay in the same col
                else if (lastEdge.second == col)
                {
                    addToGroup(0, row, group);
                    // printing happens implicitly because row is always smaller than col
                }
                // we change from colom
                else
                {
                    addToGroup(0, col, group);
                    addToGroup(0, row, group);
                }
                multiEdgecounter = matrix[col][row];
                // save all the edges
                while (multiEdgecounter > 1)
                {
                    multiEdgecounter--;
                    addToGroup(0, row, group);
                }
                lastEdge.first = row;
                lastEdge.second = col;
            }
        }

    return group;
}
void Sparse6Writer::addToGroup(unsigned firstNumber, unsigned secondnumber, vector<pair<unsigned, unsigned> >& group)
{
    pair<unsigned, unsigned> newTuple;
    newTuple.first = firstNumber;
    newTuple.second = secondnumber;
    group.push_back(newTuple);
}

vector<char> Sparse6Writer::encodeNumberOfNodes(unsigned number)
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

string Sparse6Writer::printGroups(const vector<pair<unsigned, unsigned> >& groups)
{
    string temp = "";
    for (unsigned i = 0; i < groups.size(); ++i)
        temp += "(" + Label(groups[i].first).getLabelString() + ", " + Label(groups[i].second).getLabelString() + ") ";
    return temp;
}
