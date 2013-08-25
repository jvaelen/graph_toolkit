#include "integermatrix.h"
#include <assert.h>
#include <algorithm>

#include "graphComp/node.h"
#include "graphComp/edge.h"

IntegerMatrix::IntegerMatrix()
{
    // default constructor reserves minimum size
    reserveSize(1);
}

void IntegerMatrix::addNode(const Node& node)
{
    _nodes.push_back(node.getLabel());
    extendMatrix(1);
}

void IntegerMatrix::addEdge(const Node& source, const Node& target)
{
    int sourceIndex = labelToIndex(source.getLabel());
    int targetIndex = labelToIndex(target.getLabel());
    assert(sourceIndex != -1 && targetIndex != -1);
    ++(_matrix[sourceIndex][targetIndex]);
}

void IntegerMatrix::toUndirected()
{
    for (unsigned i = 0; i < _matrix.size(); ++i)
        for (unsigned j = 0; j < _matrix[i].size(); ++j)
        {
            if (_matrix[i][j] + _matrix[j][i] > 0)
            {
                _matrix[i][j] = (_matrix[i][j] > _matrix[j][i]) ? _matrix[i][j] : _matrix[j][i];
                _matrix[j][i] = (_matrix[i][j] > _matrix[j][i]) ? _matrix[i][j] : _matrix[j][i];
            }
        }
}

void IntegerMatrix::addEdge(const Edge& edge)
{
    int sourceIndex = labelToIndex(edge.getSource()->getLabel());
    int targetIndex = labelToIndex(edge.getTarget()->getLabel());
    assert(sourceIndex != -1 && targetIndex != -1);
    ++(_matrix[sourceIndex][targetIndex]);
}

void IntegerMatrix::removeNode(const Node& node)
{
    int indexOfNode = labelToIndex(node.getLabel());
    // erase from the matrix
    _matrix.erase(_matrix.begin() + indexOfNode);
    for (unsigned i = 0; i < _matrix.size(); ++i)
        _matrix[i].erase(_matrix[i].begin() + indexOfNode);
    // remove from the nodes
    _nodes.erase(_nodes.begin() + indexOfNode);
}

void IntegerMatrix::removeEdge(const Node& source, const Node& target)
{
    int sourceIndex = labelToIndex(source.getLabel());
    int targetIndex = labelToIndex(target.getLabel());
    assert(sourceIndex != -1 && targetIndex != -1);
    // if there are still edges to remove
    if (_matrix[sourceIndex][targetIndex])
        --_matrix[sourceIndex][targetIndex];
}

void IntegerMatrix::reserveSize(int n)
{
    _matrix.reserve(n); // vertically
    for (unsigned i = 0; i < _matrix.size(); ++i)
        _matrix.reserve(n); // horizontally
}

unsigned IntegerMatrix::labelToIndex(const Label& label) const
{
    if(find(_nodes.begin(), _nodes.end(), label) == _nodes.end())
        return -1;
    for (unsigned i = 0 ; i < _nodes.size(); ++i)
        if (_nodes[i] == label)
            return i; // will return because it contains the label
    assert(!NULL); // this should never happen
    return -1;
}

void IntegerMatrix::extendMatrix(int n)
{
    vector<unsigned> newLine;
    while(n > 0)
    {
        for (unsigned i = 0; i < _matrix.size(); ++i)
        {
            _matrix[i].push_back(0);
            newLine.push_back(0); // prepare the line to pushback at the end
        }
        // one more time to add the bottom right corner
        newLine.push_back(0);
        // finish by adding the
        _matrix.push_back(newLine);
        n--;
    }
}

bool IntegerMatrix::nodeHasEdge(unsigned id) const
{
    unsigned total = 0;
    for (unsigned i = id; i < _matrix.size(); ++i)
        for (unsigned j = 0; j < _matrix.size(); ++j)
            total += _matrix[i][j];
    return total;
}

unsigned IntegerMatrix::getNumberOfEdges() const
{
    // counter to keep track of the total number edges counted uptill now
    unsigned total = 0;
    for (unsigned i = 0; i < _matrix.size(); ++i)
        for (unsigned j = 0; j < _matrix[0].size(); ++j)
            total += _matrix[i][j];
    return total;
}

// friend
QDebug operator<<(QDebug dbg, const IntegerMatrix& other)
{
    dbg.nospace() << "integerMatrix:\n";
    for (unsigned i = 0 ; i < other._matrix.size(); ++i)
    {
        for (unsigned j = 0 ; j < other._matrix[i].size(); ++j)
            dbg.nospace() << other._matrix[i][j];
        dbg.nospace() << "\n";
    }
    return dbg.nospace();
}
