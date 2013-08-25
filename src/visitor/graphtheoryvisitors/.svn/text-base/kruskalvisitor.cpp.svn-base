#include "kruskalvisitor.h"
#include "graph/graphComp/node.h"
#include "graph/graphComp/edge.h"
#include "exception/invalidgraph.h"

KruskalVisitor::KruskalVisitor()
{
    // seed
    initialised = false;
    rejected = NULL;
}

void KruskalVisitor::visit(Graph &graph)
{
    // check if graph is weighted and init _graph
    init (graph);

    // init cluster
    initCluster();

    // init prio queue with all weights
    initQueue(Q);

    initialised = true;

    while ( !isFinished() )
        iterationStep(*_graph);
}

void KruskalVisitor::iterationStep(Graph &graph)
{
    if (!initialised)
    {
        // check if graph is weighted and init _graph
        init (graph);

        // init cluster
        initCluster();

        // init prio queue with all weights
        initQueue(Q);

        initialised = true;
    }

    if (!isFinished())
    {
        if (rejected != NULL)
        {
            rejected->setColor(rejcolor);
            rejected = NULL;
        }
        // catch the edge that currently has the lowest weight
        Edge* current = Q.top();
        // remove that edge from the queue
        Q.pop();

        // value that sameCluster sets to the cluster the vertices are in
        unsigned cluster1, cluster2;
        if (!sameCluster(current->getSource(), current->getTarget(), cluster1, cluster2))
        {
            _forest.push_back(current);
            clusterUnion(cluster1, cluster2);
            current->setColor(RGB::colorGreen());
        }
        else
        {
            rejcolor = current->getColor();
            current->setColor(RGB::colorOrange());
            rejected = current;
        }
    }
    // re-init
    else
    {
        // check if graph is weighted and init _graph
        init (graph);

        // init cluster
        initCluster();

        // init prio queue with all weights
        initQueue(Q);

    }

}

bool KruskalVisitor::isFinished() const
{
    return (_forest.size() >= _graph->getNumberOfNodes()-1);
}

QString KruskalVisitor::printClusters()
{
    QString result = "{ ";
    for (unsigned i = 0; i < _cluster.size(); ++i)
    {
        result += "{ ";
        for (unsigned j = 0; j < _cluster[i].size(); ++j)
        {
            result.append(_cluster[i][j]->getLabel().getLabelString().c_str()).append(" ");

        }
        result += "} ";

    }
    result += "}";
    return result;

}

bool KruskalVisitor::sameCluster(Node* v1, Node* v2, unsigned & cluster1, unsigned & cluster2)
{
    bool seenv1 = false;
    bool seenv2 = false;
    // run through all clusters and check if the two nodes are in the same one
    for (unsigned i = 0; i < _cluster.size(); ++i)
    {
        for (unsigned j = 0; j < _cluster[i].size(); ++j)
        {
            if (_cluster[i][j] == v1)
            {
                // v1 is in cluster i
                cluster1 = i;
                seenv1 = true;
            }
            else if (_cluster[i][j] == v2)
            {
                // v2 is in cluster i
                cluster2 = i;
                seenv2 = true;
            }
            // if we see both v1 and v2 in one cluster, return true
            if (seenv1 && seenv2)
                return true;
        }
        // reset bool values
        seenv1 = seenv2 = false;
    }
    // if we get here, the nodes are not in the same cluster
    return false;
}

void KruskalVisitor::clusterUnion(unsigned cluster1, unsigned cluster2)
{
    vector<Node*> newCluster;
    // add contents of cluster1 and cluster2 to new vector
    newCluster.insert(newCluster.end(), _cluster[cluster1].begin(), _cluster[cluster1].end());
    newCluster.insert(newCluster.end(), _cluster[cluster2].begin(), _cluster[cluster2].end());
    // add the new vector
    _cluster.push_back(newCluster);
    // remove the old clusters
    _cluster.erase(_cluster.begin() + cluster1);
    if (cluster1 < cluster2)
        _cluster.erase(_cluster.begin() + (cluster2-1));
    else
        _cluster.erase(_cluster.begin() + cluster2);
}

void KruskalVisitor::initQueue(priority_queue<Edge*, vector<Edge*>, compare>& Q)
{
    // run through all edges and add labels
    vector<Node*> nodes = _graph->getNodes();
    unsigned size = nodes.size();
    for (unsigned i = 0; i < size; ++i)
    {
        Node* current = nodes[i];
        list<Edge*> outgoing = _graph->getOutgoingEdges(current);
        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
            Q.push(*it);
    }

}

void KruskalVisitor::initCluster()
{
    vector<Node*> nodes = _graph->getNodes();
    unsigned size = nodes.size();
    for (unsigned i = 0; i < size; ++i)
    {
        vector<Node*> currCluster;
        currCluster.push_back(nodes[i]);
        _cluster.push_back(currCluster);
    }
}

void KruskalVisitor::init(Graph &graph)
{
    // graph has to be weighted
    if (!isWeighted(graph))
        throw (InvalidGraph("Graph is not weighted",2));
    // graph has to have nodes
    if (graph.getNumberOfNodes() < 1)
        return;

    clearQueue();
    _cluster.clear();
    _forest.clear();
    _graph = &graph;

}

void KruskalVisitor::clearQueue()
{
    while (!Q.empty())
        Q.pop();
}

bool KruskalVisitor::isWeighted(Graph &graph)
{
    // visit all nodes from the graph and check if their outgoing edges all have number labels
    vector<Node*> nodes = graph.getNodes();
    unsigned size = nodes.size();
    for (unsigned i = 0; i < size; ++i)
    {
        list<Edge*> outgoing = graph.getOutgoingEdges(nodes[i]);
        for (list<Edge*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it)
        {
            // if this edge is no cost, the property is false
            if (!(*it)->getLabel().isCost())
                return false;
        }
    }
    return true;
}
