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


public:


    /**
     * These are the layer default ids.
     *
     * The layer id also serves as Z-order, meaning the lower the id
     * the more the layer is rendered on the bottom.
     */
    enum class default_ids : layerid_t {

        background = 0,                 /**< Default layer id for background. */
        base = 1,                       /**< Default layer id for base tiles (like walls, rocks, ...). */
        walls = 2,                      /**< Default layer id for dungeon walls. */
        effects = 3,                    /**< Default layer id for tile effects stuff. */
        text = 4                        /**< Default layer id for text annotations. */
    };


    /**
     * Create a new layer (factory method) for a map.
     *
     * @param   cMap        parent object
     * @param   nId         the id of the new map layer
     * @return  a new layer
     */
    static LayerPointer create(Map * cMap, layerid_t nId);


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
     */
    explicit Layer(Map * cMap, layerid_t nId);



    layerid_t m_nId;                            /**< Map id. */
    class Layer_data;                           /**< Internal data type. */
    std::shared_ptr<Layer::Layer_data> d;       /**< Internal data instance. */
};


}
}


#endif
