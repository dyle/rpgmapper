/*
 * map.hpp
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


#ifndef MODEL_MAP_HPP
#define MODEL_MAP_HPP


// ------------------------------------------------------------
// incs


#include <map>
#include <memory>

#include <QPoint>
#include <QSharedPointer>
#include <QSize>

// rpgmapper
#include <rpgmapper/nameable.hpp>
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A single RPG Map.
 */
class Map : public Nameable {


    Q_OBJECT


public:


    /**
     * These are the layers on a map.
     */
    enum class map_layer {
        background = 0,             /**< Background layer. */
        base = 1,                   /**< A layer for all base tiles (e.g. floor, rock, ...). */
        walls = 2,                  /**< A layer for all walls. */
        grid = 3,                   /**< The layer responsible for the map grid. */
        specials = 4,               /**< A layer rendering some special stuff. */
        text = 5                    /**< A layer for positioning text. */
    };


    /**
     * Create a new map (factory method).
     *
     * @param   cAtlas      parent object
     * @return  a new map
     */
    static MapPointer create(Atlas * cAtlas);


    /**
     * Return the id of the map.
     *
     * @return  the id of the map
     */
    mapid_t id() const { return m_nId; }


    /**
     * Get a layer of this map.
     *
     * @param   eLayer      the layer requested
     * @return  the layers of this map
     */
    LayerPointer const & layer(map_layer eLayer) const;


    /**
     * Get the layers of this map.
     *
     * @return  the layers of this map
     */
    Layers const & layers() const;


    /**
     * Load the map from json.
     *
     * @param   cJSON       the json instance to load from
     * @param   cAtlas      parent object
     * @return  the loaded map instance
     */
    static MapPointer load(QJsonObject const & cJSON, Atlas * cAtlas);


    /**
     * Means sto order this map among other maps.
     *
     * @return  a value indicating the position of this map among others
     */
    int orderValue() const;


    /**
     * The offest of the origin coordinate.
     *
     * Map coordinates are relative to this offset value.
     *
     * @return  the offset of the origin coordinate on this map
     */
    QPoint const & originOffset() const;


    /**
     * Return the region to which this map belongs to.
     *
     * @return  the region of this map
     */
    RegionPointer const region() const;


    /**
     * Save the map to json.
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


    /**
     * Set the means to order this map among other maps.
     *
     * Map coordinates are relative to this offset value.
     *
     * @param   nOrderValue     a value indicating the position of this maps among others
     */
    void setOrderValue(int nOrderValue);


    /**
     * Adjust the offest of the origin coordinate.
     *
     * @param   cOffset         offset of the origin
     */
    void setOriginOffset(QPoint cOffset);


    /**
     * Set the region this map belongs.
     *
     * @param   cRegion     the new region of this map
     */
    void setRegion(RegionPointer & cRegion);


    /**
     * Sets a new size of the map.
     *
     * @param   cSize       the new size of the map
     */
    void setSize(QSize cSize);


    /**
     * Returns the size of the map.
     *
     * @return  the size of the map
     */
    QSize size() const;


    /**
     * Translate the X coordinate to the user value.
     *
     * @param   x       x on the map
     * @return  value shown to the user
     */
    QString translateX(int x) const;


    /**
     * Translate the Y coordinate to the user value.
     *
     * @param   y       y on the map
     * @return  value shown to the user
     */
    QString translateY(int y) const;


public slots:


    /**
     * Reset the map to an empty state.
     */
    void clear();


protected:


    /**
     * Load the map from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


signals:


    /**
     * The map changed its region.
     */
    void changedRegion();


    /**
     * The map changed its order value.
     */
    void changedOrderValue();


    /**
     * The map origin offset has changed.
     */
    void changedOriginOffset();


    /**
     * The size of the map has changed.
     */
    void changedSize();


private:


    /**
     * Ctor.
     *
     * @param   cAtlas      parent object
     * @param   nId         id of the map
     */
    explicit Map(Atlas * cAtlas, mapid_t nId);


    /**
     * Adds the standard default layers to the map.
     */
    void createDefaultLayers();


    /**
     * Creates a nice initial state.
     */
    void init();


    mapid_t m_nId;                              /**< Map id. */

    class Map_data;                             /**< Internal data type. */
    std::shared_ptr<Map::Map_data> d;           /**< Internal data instance. */
};


}
}


#endif
