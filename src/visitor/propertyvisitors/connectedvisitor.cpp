#include <stack>
#include <list>
#include <algorithm>

#include "connectedvisitor.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"
#include "graph/graph.h"

ConnectedVisitor::ConnectedVisitor() : PropertyVisitor()
{
}

ConnectedVisitor::~ConnectedVisitor()
{
}

void ConnectedVisitor::visit(Graph &graph)
{
    // add to open graph map if it does not exist yet
    addToOpenGraphs(graph);

    // we set the bool _propertyResult to be true, in the algorithm we will only set this to false when we encounter a failure,
    // so if after all for loops the bool is still true, we know the property is true
    _openGraphs[&graph] = TRUEVAL;

    bool stop = false;

    // for every node, check if there is a path from it to all other nodes
    const vector<Node*>& nodes = graph.getNodes();
    int size = nodes.size();
    for (int i = 0; !stop && i < size; ++i)
    {
        vector<Node*> p = path(nodes[i], graph);
        bool *table = new bool[size];
        for (int j = 0; j < size; ++j)
            table[j] = false;
        // check if all other nodes are in path
        for (int j = 0; j < static_cast<int>(p.size()); ++j)
        {
            table[graph.nodeToIndex(p[j])] = true;
        }
        // check if the entire table (except for the node itself) is true
        bool ok = validate(table, size, i);
        delete table;
        if (!ok)
        {
            _openGraphs[&graph] = FALSEVAL;
            stop = true;
        }
    }

    notifyObservers();

}

bool ConnectedVisitor::validate(bool* table, int n, int exclude)
{
    for (int j = 0; j < n; ++j)
        if (j != exclude && table[j] == false)
            return false;
    return true;

}

vector<Node*> ConnectedVisitor::path(Node* n, Graph& g)
{
    stack<Node*> s;
    s.push(n);
    vector<Node*> result;
    result.push_back(n);

    while (!s.empty())
    {
        Node* current = s.top();
        s.pop();
        list<Edge*> outgoing = g.getOutgoingEdges(current);
        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
        {
            Node* target = (*it)->getTarget();
            // if target node is not in the result yet
            if ( std::find(result.begin(), result.end(), target) == result.end())
            {
                result.push_back(target);
                s.push(target);
            }
        }
    }

    return result;
}

