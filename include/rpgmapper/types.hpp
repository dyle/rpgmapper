/*
 * types.hpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef MODEL_TYPES_HPP
#define MODEL_TYPES_HPP


// ------------------------------------------------------------
// incs

#include <QPoint>
#include <QSharedPointer>
#include <QVariant>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


int const MAXIMUM_MAP_HEIGHT = 1000;                        /**< Maximum fields in y-axis on a map. */
int const MAXIMUM_MAP_WIDTH = 1000;                         /**< Maximum fields in x-axis on a map. */
int const MINIMUM_MAP_HEIGHT = 1;                           /**< Minimum fields in y-axis on a map. */
int const MINIMUM_MAP_WIDTH = 1;                            /**< Minimum fields in x-axis on a map. */


class Atlas;                                                /**< An atlas. */
typedef QSharedPointer<Atlas> AtlasPointer;                 /**< Atlas smart pointer. */

class Changeable;                                           /**< An object capable of recording changes */
typedef QSharedPointer<Changeable> ChangeablePointer;       /**< Changeable smart pointer. */

class Layer;                                                /**< A layer on a map. */
typedef QSharedPointer<Layer> LayerPointer;                 /**< Layer smart pointer. */
typedef int layerid_t;                                      /**< Id of a layer == serves as Z order value. */
typedef std::map<layerid_t, LayerPointer> Layers;           /**< Multiple layers. */

class Map;                                                  /**< A map. */
typedef QSharedPointer<Map> MapPointer;                     /**< Map smart pointer. */
typedef int mapid_t;                                        /**< Id of a map. */
typedef std::map<mapid_t, MapPointer> Maps;                 /**< Multiple maps. */

class Region;                                               /**< A region. */
typedef QSharedPointer<Region> RegionPointer;               /**< Map smart pointer. */
typedef int regionid_t;                                     /**< Id of a region */
typedef std::map<regionid_t, RegionPointer> Regions;        /**< Multiple regions. */

typedef std::map<QString, QString> Tile;                    /**< A title is a set of key-value pairs (mainly "uri"). */
typedef std::vector<Tile> Tiles;                            /**< Multiple tiles in a list/vector. */

typedef int coordinate_t;                                   /**< A coordinate value used for indexing fields. */


/**
 * A field on a map.
 */
struct Field {


    QPoint cPosition;           /**< Position of this field. */
    Tiles cTiles;               /**< All the tiles on this field. */


    /**
     * Get the coordinate value of this field.
     *
     * @return  the coordinate value of this field
     */
    coordinate_t coordinate() const {
        return coordinate(cPosition);
    }


    /**
     * Get the coordinate value of a position.
     *
     * @param   cPosition       the position to convert
     * @return  the coordinate value of this position
     */
    static coordinate_t coordinate(QPoint const & cPosition) {
        return (cPosition.y() * MAXIMUM_MAP_WIDTH) + cPosition.x();
    }


    /**
     * Check if this field does hold some information.
     *
     * @return  true, if there is something placed on this field
     */
    bool isEmpty() const { return cTiles.empty(); }


    /**
     * Get the position of a coordinate value.
     *
     * @param   nCoordinate     the coordinate value
     * @return  the converted position
     */
    static QPoint position(coordinate_t nCoordinate) {
        return QPoint{nCoordinate % MAXIMUM_MAP_WIDTH, nCoordinate / MAXIMUM_MAP_WIDTH};
    }

};

typedef std::map<coordinate_t, Field> Fields;               /**< Multiple fields, indexed by a coordinate value. */


}
}


#endif
