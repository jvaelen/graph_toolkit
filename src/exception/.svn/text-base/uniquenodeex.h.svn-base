/*
 Author: Balazs Nemeth
 Description: this exception class is used when an node is trying to be added to a graph while it already exists
     */
#ifndef UNIQUENODEEX_H
#define UNIQUENODEEX_H

#include "baseex.h"
#include "graph/graphComp/node.h"

class UniqueNodeEx : public BaseEx
{
public:
    // in most cases the constructor would only be called with one parameter, the topic
    UniqueNodeEx(Node topic, string extraInfo = "", int priority = 0) : BaseEx(extraInfo, priority), _topic(topic) {;}
    // get message that will be shown to the user
    string getMessage() const;
    // getter and setter for the topic
    void setTopic(const Node& topic) { _topic = topic; }
    Node getTopic() const { return _topic; }
private:
    Node _topic;
};

#endif // UNIQUENODEEX_H
