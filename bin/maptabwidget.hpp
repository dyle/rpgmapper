/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_MAPTABWIDGET_HPP
#define RPGMAPPER_VIEW_MAPTABWIDGET_HPP

#include <memory>

#include <QTabWidget>

#include "mapscrollarea.hpp"


namespace rpgmapper {
namespace view {


/**
 * The Tabs of rendered maps.
 */
class MapTabWidget : public QTabWidget {

    Q_OBJECT

    /**
     * All current rendered maps referenced by map name.
     */
    std::map<QString, MapScrollArea *> mapScrollAreas;

public:

    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit MapTabWidget(QWidget * parent = nullptr);
    
public slots:

    /**
     * Closes (hides) the current map.
     */
    void closeCurrentMap();
    
    /**
     * A maps name has changed.
     *
     * @param   oldName     old name of the map.
     * @param   newName     new name of the map.
     */
    void mapNameChanged(QString oldName, QString newName);
    
    /**
     * Redraws the current selected map.
     */
    void redrawCurrentMap();

    /**
     * Removes (Hides) all maps of this tab widget.
     */
    void removeAllMaps();

    /**
     * Removes a map from the tab widgets.
     *
     * @param   mapName     the map to remove.
     */
    void removeMap(QString mapName);
    
    /**
     * Select a map to display.
     *
     * @param   mapName     the map to display.
     */
    void selectMap(QString mapName);

private slots:
    
    /**
     * The current map index changed.
     *
     * @param   index       index of the current map.
     */
    void currentChanged(int index);
    
    /**
     * The user wants to close a tab widget.
     *
     * @param   index       number of the widget to close.
     */
    void mapCloseRequested(int index);

signals:
    
    /**
     * Requests to decrease the map zoom level.
     */
    void decreaseZoom();
    
    /**
     * The user hovers with the mouse over coordinates.
     *
     * @param   x       map x-coordinate.
     * @param   y       map y-coordinate.
     */
    void hoverCoordinates(int x, int y);
    
    /**
     * Requests to increase the map zoom level.
     */
    void increaseZoom();
    
    /**
     * Request to rotate the current tile left.
     */
    void rotateTileLeft();
    
    /**
     * Request to rotate the current tile right.
     */
    void rotateTileRight();
};


}
}


#endif
