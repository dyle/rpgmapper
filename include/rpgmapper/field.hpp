/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_FIELD_HPP
#define RPGMAPPER_MODEL_FIELD_HPP

#include <vector>

#include <QPoint>
#include <QString>

#include <rpgmapper/tile/tiles.hpp>


namespace rpgmapper {
namespace model {


/**
 * A Field class has a position and a list of tiles placed on it.
 */
class Field {

    QPoint position;                       /**< The fields position. */
    
    /**
     * All the tiles placed on the field.
     */
    rpgmapper::model::tile::Tiles tiles;

public:

    /**
     * Create a Field instance at the given position.
     *
     * @param   x   X coordinate measured from top/left.
     * @param   y   Y coordinate measured from top/left.
     */
    explicit Field(int x = 0, int y = 0);

    /**
     * Create a field at the given position.
     *
     * @param   position    Position of the field.
     */
    explicit Field(QPoint const & position);
    
    /**
     * Create a field at the given position.
     *
     * @param   position    Position of the field.
     */
    explicit Field(QPointF const & position);
    
    /**
     * Returns a single integer identifying the field.
     *
     * @return  an integer while uniquely identifies the field o(n a single map).
     */
    int getIndex() const {
        return getIndex(position);
    }

    /**
     * Converts a position to an integer index value.
     *
     * @param   x       X coordinate.
     * @param   y       Y coordinate.
     * @return  a unique integer to identify the field with a single value (on a single map).
     */
    static int getIndex(int x, int y);

    /**
     * Converts a position to an integer index value.
     *
     * @param   point       Position of the field on a map.
     * @return  the index integer value of the field on the map.
     */
    static int getIndex(QPoint const & point) {
        return getIndex(point.x(), point.y());
    }
    
    /**
     * Returns the position of the field measured from top/left.
     *
     * @return  the position of this field on a map measured from top/left.
     */
    QPoint getPosition() const {
        return position;
    }

    /**
     * Convert an index to a position.
     *
     * @param   index       a field index.
     * @return  the position representing this index.
     */
    static QPoint getPositionFromIndex(int index);
    
    /**
     * Gets the tiles attached to this field.
     *
     * @return  the tiles of this field.
     */
    rpgmapper::model::tile::Tiles & getTiles() {
        return tiles;
    }

    /**
     * Gets the tiles attached to this field (const version).
     *
     * @return  the tiles of this field.
     */
    rpgmapper::model::tile::Tiles const & getTiles() const {
        return tiles;
    }
    
    /**
     * Checks if a specific tile is already placed on the field.
     *
     * @return  true, if this tile is already placed there.
     */
    bool isTilePresent(rpgmapper::model::tile::Tile const * tile) const;

    /**
     * Returns true if this is a valid Field.
     *
     * @return  true, for valid fields.
     */
    virtual bool isValid() const {
        return true;
    }

    /**
     * Returns the invalid null Field ("Null object pattern")
     *
     * @return  the invalid null Field.
     */
    static Field const & nullField();
};


/**
 * This class represents the invalid null field ("Null object pattern").
 */
class InvalidField final : public Field {

public:

    /**
     * Constructs an invalid Field.
     */
    InvalidField() : Field(0, 0) {}

    /**
     * The invalid field always return false for isValid().
     *
     * @return  always false.
     */
    bool isValid() const override {
        return false;
    }
};


}
}


#endif
