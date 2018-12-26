/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_COLOR_TILE_HPP
#define RPGMAPPER_MODEL_TILE_COLOR_TILE_HPP

#include <rpgmapper/layer/layer_stack.hpp>
#include <rpgmapper/tile/tile.hpp>


namespace rpgmapper {
namespace model {
namespace tile {

/**
 * A ColorTile is a base tile, which draws a plain color.
 *
 * Attributes:
 *
 *      "color"     - The color value used for this tile.
 */
class ColorTile : public Tile {

public:
    
    /**
     * Constructor.
     */
    explicit ColorTile();
    
    /**
     * Constructor.
     */
    explicit ColorTile(Attributes & attributes);
    
    /**
     * Equality operator
     *
     * @param   rhs     right hand side
     * @return  true if (*this) == rhs.
     */
    bool operator==(Tile const & rhs) const override;
    
    /**
     * Draws the tile.
     *
     * @param   painter         painter used for drawing
     * @param   tileSize        the tile size.
     */
    void draw(QPainter & painter, int tileSize) override;
    
    /**
     * Retrieves the color in this color tile.
     *
     * @return  the color within this color tile.
     */
    QColor getColor() const;
    
    /**
     * Returns the insert mode of this particular tile when placed on a field.
     *
     * @return  the insert mode enum value of this tile.
     */
    TileInsertMode getInsertMode() const override {
        return TileInsertMode::exclusive;
    }
    
    /**
     * Determines if the current tile is able to be placed at the map at the given position.
     *
     * @param   x               X position to place the tile.
     * @param   y               Y position to place the tile.
     * @param   layerStack      the stack of layers of the map.
     * @return  true, if the current tile can be placed at this position.
     */
    bool isPlaceable(float x, float y, rpgmapper::model::layer::LayerStack const * layerStack) const override;
    
    /**
     * Places this tile within the layer stack of a map.
     *
     * @param   x               X position to place the tile.
     * @param   y               Y position to place the tile.
     * @param   layerStack      the stack of layers of the map.
     * @return  true, if the element has been newly placed.
     */
    bool place(float x, float y, rpgmapper::model::layer::LayerStack * layerStack) override;
};


}
}
}


#endif
