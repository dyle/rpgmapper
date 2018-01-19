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

/**
 * A single element on a map.
 */
struct Tile {
    QPoint cPosition;                                       /**< Position of this element on the map. */
    std::map<QString, QString> cAttributes;                 /**< Attributes of the item (mainly "uri"). */
};
typedef std::map<int, Tile> Tiles;                          /**< Multiple map items. */


}
}


#endif
