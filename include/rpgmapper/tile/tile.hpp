/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_TILE_TILE_HPP
#define RPGMAPPER_MODEL_TILE_TILE_HPP

#include <map>

#include <QPainter>
#include <QString>

#include <rpgmapper/layer/layer_stack.hpp>
#include <rpgmapper/map_pointer.hpp>


namespace rpgmapper {
namespace model {
namespace layer {


// fwd
class LayerStack;


}
}
}


namespace rpgmapper {
namespace model {
namespace tile {


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
     * Constructor.
     */
    explicit Tile(Attributes &attributes);
    
    /**
     * Copy Constructor.
     */
    Tile(Tile const &) = default;
    
    /**
     * Equality operator.
     */
    virtual bool operator==(Tile const &) const = 0;
    
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
     * Gets the type of the tile.
     *
     * @return  a string describing the type of tile.
     */
    QString getType() const;
    
    /**
     * Draws the tile.
     *
     * @param   painter     the painter used to draw the tile.
     * @param   tileSize    size of the tile.
     */
    virtual void draw(QPainter &painter, int tileSize) = 0;
    
    /**
     * Determines if the current tile is able to be placed at the map at the given position.
     *
     * @param   x               X position to place the tile.
     * @param   y               Y position to place the tile.
     * @param   layerStack      the stack of layers of the map.
     * @return  true, if the current tile can be placed at this position.
     */
    virtual bool isPlaceable(float x, float y, rpgmapper::model::layer::LayerStack const * layerStack) const = 0;
    
    /**
     * Determines if the current tile is able to be placed at the map at the given position.
     *
     * @param   position        position to place the tile.
     * @param   layerStack      the stack of layer of the map.
     * @return  true, if the current tile can be placed at this position.
     */
    bool isPlaceable(QPointF position, rpgmapper::model::layer::LayerStack const * layerStack) const {
        return isPlaceable(static_cast<float>(position.x()), static_cast<float>(position.y()), layerStack);
    }
    
    /**
     * Places this tile within the layer stack of a map.
     *
     * The method returns true, if the map has been changed.
     * Mostly tiles are added and the method returns true.
     * However, placing the very same tile twice might yield false
     * the second time (depends on the type if tile).
     *
     * @param   x               X position to place the tile.
     * @param   y               Y position to place the tile.
     * @param   layerStack      the stack of layers of the map.
     * @return  true, if the element has been newly placed.
     */
    virtual bool place(float x, float y, rpgmapper::model::layer::LayerStack * layerStack) = 0;
};


}
}
}


#endif
