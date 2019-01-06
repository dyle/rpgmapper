/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_CURRENTTILEWIDGET_HPP
#define RPGMAPPER_VIEW_CURRENTTILEWIDGET_HPP

#include <QWidget>

#include <rpgmapper/tile/tile_pointer.hpp>


namespace rpgmapper {
namespace view {


/**
 * The CurrentTileWidget displays a selected tile.
 */
class CurrentTileWidget : public QWidget {

    Q_OBJECT
    
    rpgmapper::model::tile::TilePointer currentTile;        /**< The current tile. */
    
public:
    
    /**
     * Constructor
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit CurrentTileWidget(QWidget * parent = nullptr);
    
    /**
     * Returns the current tile.
     *
     * @return  the current tile.
     */
    rpgmapper::model::tile::TilePointer getCurrentTile() {
        return currentTile;
    }
    
    /**
     * Returns the current tile.
     *
     * @return  the current tile.
     */
    rpgmapper::model::tile::TilePointer const getCurrentTile() const {
        return currentTile;
    }
    
    /**
     * Sets a new current tile.
     *
     * @param   tile        the new current tile.
     */
    void setCurrentTile(rpgmapper::model::tile::TilePointer tile);

protected:
    
    /**
     * Draws this widget.
     *
     * @param   event       the paint event involved.
     */
    void paintEvent(QPaintEvent * event) override;
};


}
}


#endif
