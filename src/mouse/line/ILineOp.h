/**********************************************************************************************
    Copyright (C) 2014-2015 Oliver Eichler oliver.eichler@gmx.de

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

**********************************************************************************************/

#ifndef ILINEOP_H
#define ILINEOP_H

#include "gis/IGisLine.h"
#include <QBrush>
#include <QCursor>
#include <QObject>
#include <QPen>
#include <QRect>

class QMouseEvent;
class CCanvas;
class QPainter;
class IMouseEditLine;

class ILineOp : public QObject
{
    Q_OBJECT
public:
    ILineOp(SGisLine &points, CGisDraw * gis, CCanvas * canvas, IMouseEditLine * parent);
    virtual ~ILineOp();

    virtual void mousePressEvent(QMouseEvent * e);
    virtual void mouseMoveEvent(QMouseEvent * e);
    virtual void mouseReleaseEvent(QMouseEvent *e);

    virtual void mousePressEventEx(QMouseEvent * e) = 0;
    virtual void mouseMoveEventEx(QMouseEvent * e) = 0;
    virtual void mouseReleaseEventEx(QMouseEvent *e) = 0;

    virtual void drawFg(QPainter& p) = 0;
    virtual void drawBg(QPainter& p);

    virtual void needsRedraw();

    const QCursor& getCursor()
    {
        return cursor;
    }

    virtual void canvasPanned(QPointF pos)
    {
    }

protected slots:
    void slotTimeoutRouting();

protected:
    virtual void finalizeOperation(qint32 idx);
    qint32 isCloseTo(const QPoint& pos);
    qint32 isCloseToLine(const QPoint& pos);

    void drawSinglePoint(const QPointF& pt, QPainter& p);
    void drawLeadLine(const QPolygonF& line, QPainter& p);

    IMouseEditLine * parentHandler;
    SGisLine& points;
    CCanvas * canvas;
    CGisDraw * gis;
    QTimer * timerRouting;

    QCursor cursor;

    qint32 idxFocus;
    bool mapMove;
    bool mapDidMove;

    QPoint lastPos;

    QRect rectPoint;
    const QPen penBgPoint;
    const QPen penFgPoint;
    const QBrush brushBgPoint;
    const QBrush brushFgPoint;

    QPolygonF leadLineCoord1;
    QPolygonF leadLineCoord2;
    QPolygonF leadLinePixel1;
    QPolygonF leadLinePixel2;

    QPolygonF subLineCoord1;
    QPolygonF subLineCoord2;
    QPolygonF subLinePixel1;
    QPolygonF subLinePixel2;
};

#endif //ILINEOP_H
