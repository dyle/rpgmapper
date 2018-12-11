/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_COLOR_TILE_HPP
#define RPGMAPPER_MODEL_TILE_COLOR_TILE_HPP

#include <rpgmapper/tile.hpp>


namespace rpgmapper {
namespace model {
namespace tiles {

/**
 * A ColorTile is a base tile, which draws a plain color.
 */
class ColorTile : public rpgmapper::model::Tile {

public:
    
    /**
     * Constructor.
     */
    explicit ColorTile() : Tile() {}
    
    /**
     * Constructor.
     */
    explicit ColorTile(Attributes & attributes) : Tile{attributes} {}
    
    /**
     * Retrieves the color in this color tile.
     *
     * @return  the color within this color tile.
     */
    QColor getColor() const;
    
    /**
     * Draws the tile.
     *
     * @param   painter         painter used for drawing
     * @param   tileSize        the tile size.
     */
    void draw(QPainter & painter, int tileSize) override;
    
    /**
     * Places this tile within the layer stack of a map.
     *
     * @param   x               X position to place the tile.
     * @param   y               Y position to place the tile.
     * @param   layerStack      the stack of layers of the map.
     */
    void place(int x, int y, LayerStack * layerStack) override;
};


}
}
}


#endif
