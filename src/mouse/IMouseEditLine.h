/**********************************************************************************************
    Copyright (C) 2014 Oliver Eichler oliver.eichler@gmx.de

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

#ifndef IMOUSEEDITLINE_H
#define IMOUSEEDITLINE_H

#include "mouse/IMouse.h"
#include <QPointer>
#include <QPolygonF>

class CGisDraw;
class CCanvas;
class IGisLine;
class CScrOptPoint;
class CScrOptEditLine;
class CScrOptRange;

class IMouseEditLine : public IMouse
{
    Q_OBJECT
public:
    /**
       @brief Start to create a new track with given point as first track point
       @param point     the starting point
       @param gis       the draw context to use
       @param parent    the canvas to use
     */
    IMouseEditLine(const QPointF& point, CGisDraw * gis, CCanvas * parent);
    /**
       @brief Edit an existing track
       @param trk       the track to edit
       @param gis       the draw context to use
       @param parent    the canvas to use
     */
    IMouseEditLine(IGisLine &src, CGisDraw * gis, CCanvas * parent);
    virtual ~IMouseEditLine();

    void draw(QPainter& p,  bool needsRedraw, const QRect &rect);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent * e);

protected slots:
    /**
       @brief Delete the selected point
     */
    void slotDeletePoint();
    /**
       @brief Start to select a range of points
     */
    void slotSelectRange();
    /**
       @brief Delete selected range of points
     */
    void slotDeleteRange();
    /**
       @brief Move selected point
     */
    void slotMovePoint();
    /**
       @brief Add points in direction start of track (eStateAddPointBwd)
     */
    void slotAddPoint1();
    /**
       @brief Add points in direction end of track (eStateAddPointFwd)
     */
    void slotAddPoint2();


    virtual void slotAbort();
    virtual void slotCopyToOrig();
    virtual void slotCopyToNew() = 0;

protected:
    virtual void drawLine(const QPolygonF& l, QPainter& p);
    /**
       @brief Get access to the IGisLine object a subclass of IMouseEditLine is handling.
       @return A valid pointer or 0.
     */
    virtual IGisLine * getGisLine() = 0;
    /// shadow cursor needed to restore cursor after some actions providing their own cursor.
    QCursor cursor1;
    /// the line's coordinates in [rad]
    QPolygonF coords1;

private:
    void drawPointOfFocus(QPainter& p);
    void drawBullets(const QPolygonF& l, QPainter& p);
    void drawHighlight1(QPainter& p);
    void drawHighlight2(QPainter& p);
    void drawArrows(const QPolygonF &l, QPainter& p);
    void drawLeadLine(const QPolygonF &l, QPainter& p);
    int getPointCloseBy(const QPoint& screenPos);

    /// backup for coord1
    QPolygonF save;
    /// the line's coordinates in [pixel]
    QPolygonF line;

    /// the temporary line of new point to add [rad]
    QPolygonF newCoords;
    /// the temporary line of new point to add [pixel]
    QPolygonF newLine;

    enum state_e
    {
        eStateIdle
        ,eStatePointSelected
        ,eStateSelectRange
        ,eStateRangeSelected
        ,eStateMovePoint
        ,eStateAddPointBwd
        ,eStateAddPointFwd
        ,eStateMoveMap
    };

    state_e state;
    qint32 idxFocus;
    qint32 idxStart;
    qint32 idxStop;

    QPointer<CScrOptPoint> scrOptPoint;
    QPointer<CScrOptRange> scrOptRange;
    CScrOptEditLine * scrOptEditLine;

    QPoint lastPoint;

    QPolygonF leadLineCoord;
    QPolygonF leadLinePixel;
    QPolygonF subLineCoord;
    QPolygonF subLinePixel;
};

#endif //IMOUSEEDITLINE_H


