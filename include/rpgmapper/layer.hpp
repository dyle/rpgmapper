/*
 * layer.hpp
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


#ifndef MODEL_LAYER_HPP
#define MODEL_LAYER_HPP


// ------------------------------------------------------------
// incs

#include <memory>

// rpgmapper
#include <rpgmapper/nameable.hpp>
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A layer on a map.
 */
class Layer  : public Nameable {


    Q_OBJECT

    friend class Map;


public:


    /**
     * These are the layer types supported.
     */
    enum class layer_t {
        background,                 /**< A layer rendering a full background image. */
        grid,                       /**< A layer rendering a grid. */
        tile,                       /**< A layer taking bases, walls, specials, ... */
        text                        /**< A layer positioning text. */
    };


    /**
     * Adds a tile to the layer.
     *
     * @param   cTile       the tile to add to the layer
     */
    void addTile(Field cTile);


    /**
     * Create a new layer (factory method) for a map.
     *
     * @param   cMap        parent object
     * @param   nId         the id of the new map layer
     * @param   eLayer      the layer type
     * @return  a new layer
     */
    static LayerPointer create(Map * cMap, layerid_t nId, layer_t eLayer);


    /**
     * Get all the map items of this layer.
     *
     * @return  all tiles on this layer
     */
    Fields const & fields() const;


    /**
     * Return the id of the layer.
     *
     * @return  the id of the layer
     */
    layerid_t id() const { return m_nId; }


    /**
     * Load the layer from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


    /**
     * Save the layer to json.
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


    /**
     * Checks if the tiles on this layer are stackable.
     *
     * Stackable tiles can be piled up on the very same field.
     * If the tiles are not stackable, then there can be only
     * one tile per field.
     *
     * @return  true, if there can be multiple tiles per field
     */
    bool stackable() const;


    /**
     * Get the type of the layer.
     *
     * @return  the layer type enum value.
     */
    layer_t type() const { return m_eLayer; }


    /**
     * Checks if this layer is visible.
     *
     * @return  visibility flag
     */
    bool visible() const;


    /**
     * Switches visibility of this layer.
     *
     * @param   bVisible        new visibility flag
     */
    void visible(bool bVisible);


public slots:


    /**
     * Reset the map to an empty state.
     */
    void clear();


private:


    /**
     * Ctor.
     *
     * @param   cMap        parent object
     * @param   nId         id of the layer
     * @param   eLayer      the layer type
     */
    explicit Layer(Map * cMap, layerid_t nId, layer_t eLayer);


    layerid_t m_nId;                            /**< Layer id. */
    layer_t m_eLayer;                           /**< Layer type enum value. */
    class Layer_data;                           /**< Internal data type. */
    std::shared_ptr<Layer::Layer_data> d;       /**< Internal data instance. */
};


}
}


#endif
