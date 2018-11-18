/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_MAPWIDGET_HPP
#define RPGMAPPER_VIEW_MAPWIDGET_HPP

#include <memory>

#include <QString>
#include <QWidget>

#include <rpgmapper/average.hpp>


namespace rpgmapper {
namespace view {


/**
 * This widget renders a map.
 */
class MapWidget : public QWidget {

    Q_OBJECT

    QString mapName;                /**< The name of the map displayed. */
    
    /**
     * This holds the average time of the time durations in milliseconds.
     */
    rpgmapper::model::AverageOverSize<float> averagePaintDuration;

public:

    /**
     * Constructor
     * @param   parent      Parent QWidget instance.
     */
    explicit MapWidget(QWidget * parent);
    
    /**
     * Gets the name of the map this widget displays.
     *
     * @return  the name of the map displayed.
     */
    QString getMapName() const {
        return mapName;
    }

    /**
     * Sets the map to display.
     *
     * @param   mapName     the map to render.
     */
    void setMap(QString mapName);

public slots:
    
    /**
     * The size of the map changed.
     *
     * @param   size        the new size of the map.
     */
    void mapSizeChanged(QSize size);
    
protected:

    /**
     * Special handling of mouse move events.
     *
     * @param   event       the mouse move event.
     */
    void mouseMoveEvent(QMouseEvent * event) override;

    /**
     * Special painting.
     *
     * @param   event       the paint event.
     */
    void paintEvent(QPaintEvent * event) override;

signals:

    /**
     * The user hovers with the mouse over a field.
     *
     * @param   mapX        map X-coordinate the user currently hovers with the mouse.
     * @param   mapY        map Y-coordinate the user currently hovers with the mouse.
     */
    void hoverCoordinates(int mapX, int mapY);
};


}
}


#endif
