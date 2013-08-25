/*
 Author: Balazs Nemeth
 Description: represents a node graphically in a QGraphicsScene, it consists of a circle and some text
     */

#ifndef GRAPHICSNODE_H
#define GRAPHICSNODE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include "observer/observer.h"
#include "graph/graphComp/point.h"
#include "graph/graphComp/rgb.h"

class Node;
class ToolHandler;
class RGB;

class GraphicsNode : public QGraphicsItem, public Observer
{
public:
    enum ObserverType {NODEOBSERVER = UserType};
    GraphicsNode(QGraphicsItem* parent, QGraphicsScene* scene, int radius);
    // destructor cleans up the circle and the text inside the circle
    ~GraphicsNode();
    // returns the bounding rectangle of the node, this is the size of the node
    QRectF boundingRect() const;
    // implement the paint function that paints a node
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // if the underlying node changes, this function is called
    void notify(Subject *subject);
    /* sets the color of the node, this isn't the actual color it is only used when
        the user hovers over the node, but this color will be shown instead of the real color */
    void setColor(const RGB& rgb);
    // restores the original color
    void unSetColor();
    // returns the node that is being observerd
    Node* getNode() const {return _node;}
    // returns the radius so when a line is drawn, it can have an arrow
    int getRadius() const {return _radius; }
    // override updatePosition will set the position of the observed node to the position
    void updatePosition(const Point& newPosition);
    void setPen(const QPen& pen) {_drawingPen = pen; sceneUpdateMinimalRect();}
    // sets the toolhandler
    void setToolHandler(ToolHandler* toolHandler) { _toolHandler = toolHandler;}
    // redefine the type of the object
    int type() const {return NODEOBSERVER;}
    /* returns the shape of the node, this is a circle fit in the bounding rectangle,
        using this function will allow us to get the nodes focus only when the mouse enters the circle of the node */
    QPainterPath shape() const;
    // change the fillcolor
    void setFillColor(const RGB& rgb);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private:
    // helpfunctions
    void sceneUpdateMinimalRect();
    // returns a pen that has the color set and other stuff
    QPen createPen() const;
    // the circle used to represent the node
    QGraphicsEllipseItem* _circle;
    // radius of the node
    int _radius;
    // the text in the circle that shows the label of a node and is updated whenever the label of a node changes
    QString _nodeLabel;
    Node* _node;
    QPen _drawingPen;
    ToolHandler* _toolHandler;
    QColor _color;
    QPen _pen;
    QColor _overriddenColor;
    bool _overrideColor;
    RGB _fillColor;
};

#endif // GRAPHICSNODE_H
