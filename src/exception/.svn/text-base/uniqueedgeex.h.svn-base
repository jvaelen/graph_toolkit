/*
 Author: Balazs Nemeth
 Description: this exception class is used when an edge is trying to be added to a graph while it already exists
     */
#ifndef UNIQUEEDGEEX_H
#define UNIQUEEDGEEX_H

#include "baseex.h"
#include "graph/graphComp/edge.h"

class UniqueEdgeEx : public BaseEx
{
public:
    // in most cases the constructor would only be called with one parameter, the topic
    UniqueEdgeEx(Edge topic, string extraInfo = "", int priority = 1) : BaseEx(extraInfo, priority), _topic(topic) {;}
    // get message that will be shown to the user
    string getMessage() const;
    // getter and setter for the topic
    void setTopic(const Edge& topic) {_topic = topic; }
    Edge getTopic() const { return _topic; }
private:
    Edge _topic;
};

#endif // UNIQUEEDGEEX_H
