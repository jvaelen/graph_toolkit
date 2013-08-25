/*
 Author: Balazs Nemeth
 Description: is used as the observer for an edge
     */

#ifndef GRAPHICSEDGE_H
#define GRAPHICSEDGE_H

#include <QGraphicsItem>
#include "observer/observer.h"
#include "graph/graphComp/edge.h"
#include "graph/graphComp/node.h"
#include "observer/GUI/graphicarrowhead.h"
class ToolHandler;

class GraphicsEdge : public QGraphicsItem, public Observer
{
public:
    enum ObserverType {EDGEOBSERVER = UserType + 1};
    explicit GraphicsEdge(QGraphicsItem* parent, QGraphicsScene* scene);
    ~GraphicsEdge();
    // redifine paint, this will draw the edge
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void notify(Subject *subject);
    /* sets the color of the edge, this isn't the actual color it is only used when
        the user hovers over the edge, but this color will be shown instead of the real color */
    void setColor(const RGB& rgb);
    // restores the original color
    void unSetColor();
    // sets the toolhandler
    void setToolHandler(ToolHandler* toolHandler) { _toolHandler = toolHandler;}
    // redefine the type of the object
    int type() const {return EDGEOBSERVER;}
    // returns the edge that is being observed
    Edge* getEdge() {return _edge;}
    // returns the if the line coords have changed
    bool setLine(int x1, int y1, int x2, int y2);
    QPainterPath shape() const;
    // calculates the arrow whatever happens, can be used to create an edge wit hout nodes
    void forceCalcArrow();
    // we need to add the boundingrect of the arrow to the boundingrect of the line
    QRectF boundingRect() const;
protected:
    // for fancy effects when the user mouses over the node, these functions are overloaded
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
private:
    // help funciton to calculate the position of the label
    void calculateLabelPosition();
    // helpfunction that will call the appropeate functions of the arrowhead class to update the arrowhead polygon
    void updateArrowHead();
    Edge* _edge;
    ToolHandler* _toolHandler;
    QString _label;
    GraphicArrowHead _arrowHead;
    // keep a local copy of the values to reduce getting the information that is got from the subject
    int _x1, _y1, _x2, _y2;
    // brush used to draw the arrowhead
    QBrush _brush;
    bool _isSelfEdge;
    QRect* _selfEdgeCircle;
    QPen _pen;
    QColor _overriddenColor;
    QColor _color;
    float _labelX;
    float _labelY;
    bool _overrideColor;
    int _zValue;
    static int _GlobalzValue;
};

#endif // GRAPHICSEDGE_H
