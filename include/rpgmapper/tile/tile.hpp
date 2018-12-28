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

#include <rpgmapper/command/command_pointer.hpp>
#include <rpgmapper/layer/layer_stack.hpp>
#include <rpgmapper/tile/tile_insert_modes.hpp>
#include <rpgmapper/tile/tiles.hpp>
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
 * There are color tiles and shape tiles. A TileFactory is used to produce the tile
 * of desired type.
 */
class Tile {

public:
    
    /**
     * The key-value map type.
     */
    using Attributes = std::map<QString, QString>;

private:
    
    /**
     * All key-value pairs of the tile instance.
     */
    Attributes attributes;

public:
    
    /**
     * Constructor.
     */
    explicit Tile();
    
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
     * Creates the placer command to place this tile on a map.
     *
     * @param   mapName         the map name to place the tile.
     * @param   position        the position where to place the tile.
     * @return  a placer command which can be executed to place this tile.
     */
    virtual rpgmapper::model::command::CommandPointer createPlacerCommand(QString mapName, QPointF position) const = 0;
    
    /**
     * Draws the tile.
     *
     * @param   painter     the painter used to draw the tile.
     * @param   tileSize    size of the tile.
     */
    virtual void draw(QPainter &painter, int tileSize) = 0;
    
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
     * Returns the insert mode of this particular tile when placed on a field.
     *
     * @return  the insert mode enum value of this tile.
     */
    virtual TileInsertMode getInsertMode() const = 0;
    
    /**
     * Gets the type of the tile.
     *
     * @return  a string describing the type of tile.
     */
    QString getType() const;
    
    /**
     * Returns the tile rotation value.
     *
     * @return  the tile rotation value in degrees.
     */
    double getRotation() const;
    
    /**
     * Returns the tile stretch factor.
     *
     * @return  the tile stretch factor.
     */
    double getStretch() const;
    
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
     * @param   placed          will be set to true, if the tile has been placed.
     * @param   x               X position to place the tile.
     * @param   y               Y position to place the tile.
     * @param   layerStack      the stack of layers of the map.
     * @return  The list of tiles replaced.
     */
    virtual Tiles place(bool & placed, float x, float y, rpgmapper::model::layer::LayerStack * layerStack) = 0;
    
    /**
     * Removes exactly this tile from a map.
     *
     * @param   mapName     the map name.
     * @param   x           the x position of the tile.
     * @param   y           the y position of the tile.
     */
    virtual void remove(QString mapName, float x, float y) const = 0;
    
    /**
     * Removes exactly this tile from a map.
     *
     * @param   mapName     the map name.
     * @param   position        position to place the tile.
     */
    virtual void remove(QString mapName, QPointF position) const {
        remove(std::move(mapName), static_cast<float>(position.x()), static_cast<float>(position.y()));
    }
    
    /**
     * Rotates the tile counter clockwise.
     */
    void rotateLeft();
    
    /**
     * Rotates the tile clockwise.
     */
    void rotateRight();
    
private:
    
    /**
     * Inits the attributes.
     */
    void initAttributes();
};


}
}
}


#endif
