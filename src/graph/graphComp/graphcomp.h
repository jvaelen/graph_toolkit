/*
 Author: Balazs Nemeth
 Description: Abstract class for a graphcomponent. this class is the baseclass that edges
              and node have so that selections can happen abstractly
     */

#ifndef GRAPHCOMP_H
#define GRAPHCOMP_H

#include "label.h"
#include "rgb.h"
#include "observer/subject.h"

class GraphComp : public Subject
{
public:
    GraphComp();
    // setter and getter
    const RGB& getColor() const {return _rgbColor;}
    const Label& getLabel() const {return _label;}
    void setColor(const RGB& rgb);

    void setLabel(const Label& label);
    // this makes it possible to tell the observers that the object will be deleted right before deletion
    bool getWillBeDeleted() const {return _willBeDeleted;}
    // can be called directly on a node to check if the label in the node has a cost, this method is delegated to the label class.
    // this is used to add efficiency, instead of using the copyconstructor of Label to check if all labels have a cost
    bool hasLabelWithCost() {return _label.isCost();}
protected:
    bool _willBeDeleted;
    // every graphcomp has a label
    Label _label;
    RGB _rgbColor;
};

#endif // GRAPHCOMP_H
