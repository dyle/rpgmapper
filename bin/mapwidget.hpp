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

    QString mapName;               /**< The name of the map displayed. */
    int tileSize;                  /**< The current size of a single tile. */
    
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
     * Returns the current tile size in pixels.
     *
     * @return  the current size of a single tile.
     */
    int getTileSize() const {
        return tileSize;
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
     */
    void mapSizeChanged();
    
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

private slots:
    
    /**
     * The name of the map has changed.
     *
     * @param   oldName     the old name
     * param    newName     the new name
     */
    void mapNameChanged(QString oldName, QString newName);

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
