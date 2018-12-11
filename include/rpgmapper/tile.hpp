/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_HPP
#define RPGMAPPER_MODEL_TILE_HPP

#include <map>

#include <QPainter>
#include <QString>


namespace rpgmapper {
namespace model {


// fwd
class LayerStack;


/**
 * A single tile on a field holds key-value pairs and knows how to draw itself.
 *
 * A tile may be:
 *  - "river" - "south-west"
 *  - "wall" - "east"
 *  - "special" - "trapdoor"
 */
class Tile {

public:
    
    using Attributes = std::map<QString, QString>;
    
private:
    
     Attributes attributes;

public:
    
    /**
     * Constructor.
     */
    Tile() = default;
    
    /**
     * Copy Constructor.
     */
    Tile(Tile const &) = default;
    
    /**
     * Constructor.
     */
    explicit Tile(Attributes & attributes);
    
    /**
     * Returns the tile attributes.
     *
     * @return  the tile attributes.
     */
    Attributes & getAttributes() {
        return attributes;
    }
    
    /**
     * Returns the tile attributes (const version).
     *
     * @return  the tile attributes.
     */
    Attributes const & getAttributes() const {
        return attributes;
    }
    
    /**
     * Draws the tile.
     *
     * @param   painter     the painter used to draw the tile.
     * @param   tileSize    size of the tile.
     */
    virtual void draw(QPainter & painter, int tileSize) = 0;

    /**
     * Places this tile within the layer stack of a map.
     *
     * @param   x               X position to place the tile.
     * @param   y               Y position to place the tile.
     * @param   layerStack      the stack of layers of the map.
     */
    virtual void place(int x, int y, LayerStack * layerStack) = 0;
};


}
}


#endif
