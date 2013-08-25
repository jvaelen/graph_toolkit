#include <QGraphicsScene>
#include <QPainter>
#include <assert.h>
#include <cmath>
#include <QPainterPathStroker>

#include "graphicsedge.h"
#include "graphdrawingscene.h"
#include "tools/toolhandler.h"

int GraphicsEdge::_GlobalzValue = -2;

GraphicsEdge::GraphicsEdge(QGraphicsItem *parent, QGraphicsScene *scene) : QGraphicsItem(parent)
{
    _isSelfEdge = false;
    _edge = NULL;
    _toolHandler = NULL;
    unSetColor();
    _zValue = _GlobalzValue--;
    setZValue(_zValue);
    _selfEdgeCircle = new QRect();
    _x1 = 0;
    _y1 = 0;
    _x2 = 0;
    _y2 = 0;
    _labelX = 0;
    _labelY = 0;
    _pen.setWidth(2);
    _brush.setColor(Qt::black);
    _brush.setStyle(Qt::SolidPattern);
    setAcceptHoverEvents(true);
}

GraphicsEdge::~GraphicsEdge()
{
    delete _selfEdgeCircle;
}

void GraphicsEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);
    // if the points are to close to eachother, optimized so that the edge isn't drawn
    if (!_isSelfEdge && ((_edge && Point(_x1, _y1).distance(Point(_x2, _y2)) < 60) || Point(_x1, _y1).distance(Point(_x2, _y2)) < 30))
        return ;

    if (_overrideColor && (!_edge || _edge->getColor() != RGB::colorSelection()))
    {
        _pen.setColor(_overriddenColor);
        _brush.setColor(_overriddenColor);
    }
    else
    {   _pen.setColor(_color);
        _brush.setColor(_color);
    }

    painter->setPen(_pen);
    if (_isSelfEdge)
    {
        painter->drawText(_x1 + 40 , _y1 - 50, 100, (_label.count(" ")+1)*20,  Qt::TextWordWrap, _label);
        painter->drawEllipse(_x1, _y1 - 40, 40, 40);
        painter->setBrush(_brush);
        painter->drawPolygon(_arrowHead.getPolygon());
    }
    else
    {
        // update the label positions
        painter->drawText(_labelX - 50, _labelY - (_label.count(" ")+1)*10, 100, (_label.count(" ")+1)*20,  Qt::AlignCenter |  Qt::AlignHCenter | Qt::TextWordWrap, _label);
        painter->setBrush(_brush);
        painter->drawLine(QPoint(_x1, _y1), QPoint(_x2, _y2));
        painter->drawPolygon(_arrowHead.getPolygon());
    }
}

void GraphicsEdge::calculateLabelPosition()
{
    QPoint temp = GraphicArrowHead::calcIntersection((_x1+_x2)/2.0f, (_y1+_y2)/2.0f, (_y2 - _y1) + (_x1+_x2)/2.0f, (_x1 - _x2) + (_y1+_y2)/2.0f, 20.0f);
    _labelX = temp.x();
    _labelY = temp.y();
}


void GraphicsEdge::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    assert(_toolHandler);
    switch(_toolHandler->getToolType())
    {
    case SELECTTOOL:
        setColor(RGB::colorHoverSelection());
        break;
    case REMOVEEDGETOOL:
        setColor(RGB::colorDelete());
        break;
    default: // addNode doesn't need to do anything
        ;
    }
    scene()->update(boundingRect());
}

void GraphicsEdge::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    Q_UNUSED(event);
    switch(_toolHandler->getToolType())
    {
    case SELECTTOOL: //without break, will also unset color
    case REMOVEEDGETOOL:
        unSetColor();
        break;
    default: // addNode doesn't need to do anything
        ;
    }
    scene()->update(boundingRect());
}

QPainterPath GraphicsEdge::shape() const
{
    QPainterPath path;
    if (_isSelfEdge)
    {
        path.addRect(QRect(_x1, _y1-40, 40, 40));
        path.addPolygon(_arrowHead.getPolygon());
    }
    else
    {
        path.moveTo(_x1, _y1);
        path.lineTo(_x2, _y2);
        path.addPolygon(_arrowHead.getPolygon());
    }
    QPainterPathStroker path2;
    path2.setWidth(10);
    return path2.createStroke(path);
}

void GraphicsEdge::setColor(const RGB &rgb)
{
    _overriddenColor.setRed(rgb.getRed());
    _overriddenColor.setGreen(rgb.getGreen());
    _overriddenColor.setBlue(rgb.getBlue());
    _overrideColor = true;
    setZValue(-1);
    scene()->update(boundingRect());
}

void GraphicsEdge::unSetColor()
{
    setZValue(_zValue);
    _overrideColor = false;
    scene()->update(boundingRect());
}

bool GraphicsEdge::setLine(int x1, int y1, int x2, int y2)
{
    scene()->update(boundingRect());
    // if the coords have not changed
    if (x1 == _x1 && y1 == _y1 && x2 == _x2 && y2 == _y2)
        return false;
    prepareGeometryChange();
    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;
    scene()->update(boundingRect());
    return true;
}

QRectF GraphicsEdge::boundingRect() const
{
    int xmin = (_x1< _x2)? _x1 : _x2;
    int ymin = (_y1< _y2)? _y1 : _y2;
    int width = (_x1 < _x2)? _x2 - _x1 : _x1 - _x2;
    int height = (_y1 < _y2)? _y2 - _y1 : _y1 - _y2;

    QRectF rect(xmin, ymin, width, height);
    rect = rect.united(_arrowHead.getPolygon().boundingRect());
    if (_isSelfEdge)
        return rect.united(QRect(_x1, _y1 - 40, 40, 40)).united(QRectF(_x1 + 40 , _y1 - 50, 100, (_label.count(" ")+1)*20));
    else
        return rect.united(QRectF(_labelX - 50, _labelY - (_label.count(" ")+1)*10, 100, (_label.count(" ")+1)*20));
}

void GraphicsEdge::forceCalcArrow()
{
    if (Point(_x1, _y1).distance(Point(_x2, _y2)) < 30)
    {
        _isSelfEdge = true;
        _arrowHead.setLine(Point(_x1+50, _y1-30), Point(_x1+30, _y1));
        _arrowHead.setValues(15, 10, 0);
    }
    else
    {
        _isSelfEdge = false;
        _arrowHead.setLine(Point(_x1, _y1), Point(_x2, _y2));
        _arrowHead.setValues(15, 10, 0);
    }
}

void GraphicsEdge::notify(Subject *subject)
{
    if (_edge != subject)
    {
        // first remove the old edge
        dynamic_cast<GraphDrawingScene*>(scene())->removeFromMap(_edge);
        _edge = (Edge*)subject;
        dynamic_cast<GraphDrawingScene*>(scene())->addToMap(_edge, this);
        dynamic_cast<GraphDrawingScene*>(scene())->uncashEdges();
    }

    // if the subject is deleted, tell the scene that this observer should be removed at the next update
    if(_edge->getWillBeDeleted())
    {
        _edge->unregisterObserver(this);
        // don't set _edge to NULL because we still need the old point to locate what should be removed
        assert(dynamic_cast<GraphDrawingScene*>(scene()));
        dynamic_cast<GraphDrawingScene*>(scene())->deleteMeAtNextUpdate(this);
        return ; // no need to update if we will delete next time
    }
    _isSelfEdge =  _edge->isSelfEdge();
    _label = QString::fromStdString(_edge->getLabel().getLabelString());
    _color.setRgb(_edge->getColor().getRed(), _edge->getColor().getGreen(), _edge->getColor().getBlue());
    if (_edge->getColor() == RGB::colorSelection())
        setZValue(-1);
    else
        setZValue(_zValue);
    _brush.setColor(_color);
    _pen.setColor(_color);
    // calculate how the arrowhead should look, now GraphicArrowHead::getPolygon() will return the polygon that represents the arrowhead
    setLine(_edge->getSource()->getCoords().getX(),
            _edge->getSource()->getCoords().getY(),
            _edge->getTarget()->getCoords().getX(),
            _edge->getTarget()->getCoords().getY()
            );
    calculateLabelPosition();
    updateArrowHead();
}

void GraphicsEdge::updateArrowHead()
{
    if(!_isSelfEdge)
    {
        _arrowHead.setLine(Point(_x1, _y1), Point(_x2, _y2));
        _arrowHead.setValues(15, 10, 30);
    }
    else
    {
        _arrowHead.setLine(Point(_x1+50, _y1-30), Point(_x1+30, _y1));
        _arrowHead.setValues(15, 10, 0);
    }

}
