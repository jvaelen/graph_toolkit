#include "hybridgraphstate.h"
#include "graph/hybridgraph.h"
#include <QDebug>

// this function will be called like so: changeState(context, new ListGraph(..))
void HybridGraphState::setState(HybridGraph* context, HybridGraphState* state)
{
    context->notifyObservers();
    // set the new state
    context->_state = state;
    // move the observers for from the old state to the new state
    moveNodeObservers(state);
    // now do the same for all the edges
    moveEdgeObservers(state);
    context->setOldState(this);
}

void HybridGraphState::moveNodeObservers(HybridGraphState* toState)
{
    // copy the observers, start by copying the node observers
    const vector<Node*>& nodes = getGraph()->getNodes();
    Node* correspondingNode = NULL;
    // for each node
    for (unsigned i = 0; i < nodes.size(); ++i)
    {

        /* get the copied node from the new state and register the observers of
            the old node from the old state to the new corresponding node*/
        correspondingNode = toState->idToNode(nodes[i]->getID());
        correspondingNode->registerObservers(nodes[i]->getObservers());
        correspondingNode->notifyObservers();
        nodes[i]->unregisterAllObservers();
    }
}

void HybridGraphState::moveEdgeObservers(HybridGraphState* toState)
{
    list<Edge*> oldEdges;
    collectEdges(this, oldEdges);
    list<Edge*> newEdges;
    collectEdges(toState, newEdges);
    bool skipRest;
    // the next part has complexity n^2, because for each edge, we have to seach for the corresponding edge
    for (list<Edge*>::iterator i = oldEdges.begin(); i != oldEdges.end(); ++i)
    {
        skipRest = false;
        for(list<Edge*>::iterator j = newEdges.begin(); !skipRest && j != newEdges.end(); ++j)
        {

           if ((*j)->getSource()->getID() == (*i)->getSource()->getID() &&
                   (*j)->getTarget()->getID() == (*i)->getTarget()->getID() && (*i)->getLabel() == (*j)->getLabel())
           {
               skipRest = true;
               (*j)->registerObservers((*i)->getObservers());
               (*j)->notifyObservers();
               (*i)->unregisterAllObservers();
           }
        }
    }
}

void HybridGraphState::collectEdges(HybridGraphState *state, list<Edge*>& edges)
{
    Graph* graph = state->getGraph();
    const vector<Node*>& nodes = graph->getNodes();
    for (unsigned i = 0; i < nodes.size(); ++i)
       concatLists(graph->getOutgoingEdges(nodes[i]), edges);
}

void HybridGraphState::concatLists(const list<Edge*>& from, list<Edge*>& to)
{
    for (list<Edge*>::const_iterator i = from.begin(); i != from.end(); ++i)
        to.push_back(*i);
}

//friend
QDebug operator<<(QDebug dbg, const HybridGraphState& other)
{
    dbg.nospace() << other.toString().c_str();
    return dbg.space();
}
