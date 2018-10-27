/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_LAYER_IMPL_HPP
#define RPGMAPPER_MODEL_LAYER_IMPL_HPP

#include <rpgmapper/map.hpp>
#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {


/**
 * The is the Layer data implementation class.
 *
 * [Pimpl C++ idiom]
 */
class Layer::Impl final {

    Map * map = nullptr;            /**< The map this layer belongs to TOOD: user smart pointer here. */
    Attributes attributes;          /**< The attributes of the current Layer. */
    bool visible = true;            /**< Visbility flag of the layer. */

public:

    /**
     * Constructor.
     *
     * @param   map     The parent, owning map of the Layer.
     */
    explicit Impl(Map * map);

    /**
     * Copy constructor.
     */
    Impl(Impl const & ) = delete;

    /**
     * Gets all attributes of the layer.
     *
     * @return  all attributes associated with this layer.
     */
    Attributes & getAttributes() {
        return attributes;
    }
    
    /**
     * Gets all attributes of the layer (const version).
     *
     * @return  all attributes associated with this layer.
     */
    Attributes const & getAttributes() const {
        return attributes;
    }

    /**
     * Returns the parent map of this layer.
     *
     * @return  The parent map.
     */
    Map * getMap() {
        return map;
    }
    
    /**
     * Returns the parent map of this layer (const version).
     *
     * @return  The parent map.
     */
    Map const * getMap() const {
        return map;
    }

    /**
     * Hides this layer.
     */
    void hide();

    /**
     * Checks if this layer is visible on the map.
     *
     * @return  true, if this layer will be drawn.
     */
    bool isVisible() const {
        return visible;
    }
    
    /**
     * Shows this layer.
     */
    void show();
};


}
}


#endif
