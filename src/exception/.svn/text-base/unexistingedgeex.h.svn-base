/*
 Author: Balazs Nemeth
 Description: this exception class is used when the user tries to remove an unexisting edge
     */
#ifndef UNEXISTINGEDGEEX_H
#define UNEXISTINGEDGEEX_H
#include "baseex.h"
#include "graph/graphComp/edge.h"

class UnexistingEdgeEx : public BaseEx
{
public:
    // in most cases the constructor would only be called with one parameter, the topic
    UnexistingEdgeEx(Edge topic, string extraInfo = "", int priority = 2) : BaseEx(extraInfo, priority), _topic(topic) {;}
    // get message that will be shown to the user
    string getMessage() const;
    // getter and setter for the topic
    void setTopic(const Edge& topic) {_topic = topic; }
    Edge getTopic() const { return _topic; }
private:
    Edge _topic;
};

#endif // UNEXISTINGEDGEEX_H
