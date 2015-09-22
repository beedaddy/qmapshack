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

#ifndef CACTIVITYTRK_H
#define CACTIVITYTRK_H

#include <QIcon>
#include <QPointer>
#include <QVector>
class CGisItemTrk;

class CActivityTrk
{
public:
    virtual ~CActivityTrk();

    struct summary_t
    {
        summary_t() : distance(0), ascend(0), descend(0), ellapsedSeconds(0), ellapsedSecondsMoving(0)
        {
        }

        void reset()
        {
            distance = 0;
            ascend = 0;
            descend = 0;
            ellapsedSeconds = 0;
            ellapsedSecondsMoving = 0;
        }

        qreal distance;
        qreal ascend;
        qreal descend;
        qreal ellapsedSeconds;
        qreal ellapsedSecondsMoving;
    };

    /**
       @brief Update internal summary array
    */
    void update();

    /**
       @brief Get sum of all flags seen in the track
       @return A 32 bit field with all available activity falgs set.
    */
    quint32 getAllFlags() const
    {
        return allFlags;
    }

    /**
       @brief Convert internal summary to HTML table
       @param str   string to receive HTML
    */
    void printSummary(QString& str) const;

    /**
       @brief Convert array of summaries to HTML table
       @param smry  The array of summaries
       @param str   string to receive HTML
    */
    static void printSummary(const QVector<summary_t> &smry, quint32 flags, QString& str);

    /**
       @brief Add internal summary to given array of summaries
       @param smry  an array of summaries to hold the sum
    */
    void sumUp(QVector<summary_t> &smry) const;


    struct desc_t
    {
        QString objName;
        quint32 flag;
        QString name;
        QString iconLarge;
        QString iconSmall;
    };

    static const desc_t actDescriptor[];

private:
    friend class CGisItemTrk;
    CActivityTrk(CGisItemTrk* trk);

    static summary_t& getSummary(QVector<summary_t> &smry, quint32 flag);
    static const summary_t& getSummary(const QVector<summary_t> &smry, quint32 flag);


    CGisItemTrk * trk;

    struct activity_t
    {
        qint32 idx1;
        qint32 idx2;
        QIcon icon;
        QString name;
    };


    quint32 allFlags;
    QList<activity_t>   activities;
    QVector<summary_t>  summaries;
};

#endif //CACTIVITYTRK_H

