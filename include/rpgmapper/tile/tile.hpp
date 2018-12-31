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
#include <rpgmapper/tile/tile_insert_modes.hpp>
#include <rpgmapper/tile/tiles.hpp>


namespace rpgmapper {
namespace model {


// fwd
class Map;


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
    
    rpgmapper::model::Map * map = nullptr;        /**< Where the tile has been placed. */
    QPointF position;                             /**< Position of the tile placed. */

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
     * Returns the map the tile is placed.
     *
     * @return  the map the tile is placed.
     */
    rpgmapper::model::Map * getMap() {
        return map;
    }
    
    /**
     * Returns the map the tile is placed (const version).
     *
     * @return  the map the tile is placed.
     */
    rpgmapper::model::Map const * getMap() const {
        return map;
    }
    
    /**
     * Returns the position the tile is placed on the map.
     *
     * @return  the position of the tile.
     */
    QPointF getPosition() const {
        return position;
    }
    
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
     * @param   map             the map to place the tile on.
     * @param   position        the position to place the tile on the map.
     * @return  true, if the current tile can be placed at this position.
     */
    virtual bool isPlaceable(rpgmapper::model::Map const * map, QPointF position) const = 0;
    
    /**
     * Places this tile within the layer stack of a map.
     *
     * @param   replaced        will receive the list of replaced tiles.
     * @param   map             the map to place the tile on.
     * @param   position        the position to place the tile on the map.
     * @return  The tile placed (maybe nullptr if failed to placed the tile).
     */
    virtual TilePointer place(Tiles & replaced, rpgmapper::model::Map * map, QPointF position) = 0;
    
    /**
     * Removes exactly this tile from a map.
     */
    virtual void remove() = 0;
    
    /**
     * Rotates the tile counter clockwise.
     */
    void rotateLeft();
    
    /**
     * Rotates the tile clockwise.
     */
    void rotateRight();
    
protected:
    
    /**
     * Sets the map the tile is placed.
     *
     * @param map       the map the tile is placed.
     */
    void setMap(rpgmapper::model::Map * map);
    
    /**
     * Sets the position the tile is placed on the map.
     *
     * @param   position        the position of the tile.
     */
    void setPosition(QPointF position);
    
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
