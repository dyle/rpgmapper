/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_STACK_HPP
#define RPGMAPPER_MODEL_LAYER_STACK_HPP

#include <list>

#include <rpgmapper/layer/axis_layer.hpp>
#include <rpgmapper/layer/background_layer.hpp>
#include <rpgmapper/layer/grid_layer.hpp>
#include <rpgmapper/layer/text_layer.hpp>
#include <rpgmapper/layer/tile_layer.hpp>


namespace rpgmapper {
namespace model {


/**
 * This class aggregates all known layers into a single object.
 *
 * With respect to the collectVisibleLayers method this class is
 * an interface for a stack of named layers. This serves as the base
 * class for the Map class later on.
 */
class LayerStack {

public:

    /**
     * Collects all layers, which are currently visible, in proper order.
     *
     * The order is:
     *      [0] - background
     *      [1] - base layers (maybe more than 1)
     *      [2] - grid
     *      [3] - axis
     *      [4] - tile layers (maybe more than 1)
     *      [5] - text
     */
    std::list<rpgmapper::model::Layer const *> collectVisibleLayers() const;

    /**
     * Gets the axis layer.
     *
     * @return  the Layer used for the axis on a map.
     */
    virtual AxisLayerPointer const & getAxisLayer() const = 0;

    /**
     * Gets the background layer.
     *
     * @return  the Layer object holding the background data.
     */
    virtual BackgroundLayerPointer const & getBackgroundLayer() const = 0;

    /**
     * Gets the layers holding the bases.
     *
     * @return  layers (maybe more than 1) holding tiles of the bases.
     */
    virtual TileLayers const & getBaseLayers() const  = 0;

    /**
     * Gets the grid layer.
     *
     * @return  the layer holding the grid information.
     */
    virtual GridLayerPointer const & getGridLayer() const  = 0;

    /**
     * Gets the layers holding the tiles of a map.
     *
     * @return  the layers (maybe more than 1) of the tiles on the map.
     */

    virtual TileLayers const & getTileLayers() const  = 0;

    /**
     * Gets the layer holding any texts on the map.
     *
     * @return  a layer with text information on the map.
     */
    virtual TextLayerPointer const & getTextLayer() const  = 0;
};


}
}

#endif
