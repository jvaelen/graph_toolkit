/*
 Author: Jeroen Vaelen and Balazs Nemeth
 Description: An edge knows the source and target node. These are saved as pointers which are by definition of an edge never NULL
     */

#ifndef EDGE_H
#define EDGE_H

#include <QDebug>

#include "label.h"
#include "observer/subject.h"
#include "rgb.h"
#include "graphcomp.h"

// onyl pointers to nodes are used
class Node;

class Edge : public GraphComp
{
public:
    Edge(Node* source, Node* target, const Label& label = Label(), const RGB& rgb = RGB());
    Edge(const Edge& other);
    // destructor sets _willBeDeleted and notifies the observers telling them that the object will be deleted
    ~Edge();
    const Label& getLabel() const { return _label;}
    void setTarget(Node* target);
    void setSource(Node* source);
    Node* getSource() const {return _source;}
    Node* getTarget() const {return _target;}
    // returns true if the edge that needs to be checked would be the same if it were seen as if were undirected
    bool isUndirected(Edge* edge) const;
    // returns true if the edge is a selfedge
    bool isSelfEdge() const;
    // friends
    friend QDebug operator<<(QDebug dbg, const Edge& other);

private:
    Node* _source;
    Node* _target;
};

#endif // EDGE_H
