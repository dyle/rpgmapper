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
    
    QSharedPointer<AxisLayer> axisLayer;                    /**< The axis layer */
    QSharedPointer<BackgroundLayer> backgroundLayer;        /**< The background layer. */
    std::list<QSharedPointer<TileLayer>> baseLayers;        /**< The base layers. */
    QSharedPointer<GridLayer> gridLayer;                    /**< The grid layer. */
    QSharedPointer<TextLayer> textLayer;                    /**< the text layer. */
    std::list<QSharedPointer<TileLayer>> tileLayers;        /**< the tile layers. */

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
    QSharedPointer<AxisLayer> & getAxisLayer() {
        return axisLayer;
    }
    
    /**
     * Gets the axis layer.
     *
     * @return  the Layer used for the axis on a map.
     */
    QSharedPointer<AxisLayer> const & getAxisLayer() const {
        return axisLayer;
    }
    
    /**
     * Gets the background layer.
     *
     * @return  the Layer object holding the background data.
     */
    QSharedPointer<BackgroundLayer> & getBackgroundLayer() {
        return backgroundLayer;
    }
    
    /**
     * Gets the background layer.
     *
     * @return  the Layer object holding the background data.
     */
    QSharedPointer<BackgroundLayer> const & getBackgroundLayer() const {
        return backgroundLayer;
    }
    
    /**
     * Gets the layers holding the bases.
     *
     * @return  layers (maybe more than 1) holding tiles of the bases.
     */
    std::list<QSharedPointer<TileLayer>> & getBaseLayers() {
        return baseLayers;
    }
    
    /**
     * Gets the layers holding the bases.
     *
     * @return  layers (maybe more than 1) holding tiles of the bases.
     */
    std::list<QSharedPointer<TileLayer>> const & getBaseLayers() const {
        return baseLayers;
    }
    
    /**
     * Gets the grid layer.
     *
     * @return  the layer holding the grid information.
     */
    QSharedPointer<GridLayer> & getGridLayer() {
        return gridLayer;
    }
    
    /**
     * Gets the grid layer.
     *
     * @return  the layer holding the grid information.
     */
    QSharedPointer<GridLayer> const & getGridLayer() const {
        return gridLayer;
    }
    
    /**
     * Gets the layer holding any texts on the map.
     *
     * @return  a layer with text information on the map.
     */
    QSharedPointer<TextLayer> & getTextLayer() {
        return textLayer;
    }
    
    
    /**
     * Gets the layer holding any texts on the map.
     *
     * @return  a layer with text information on the map.
     */
    QSharedPointer<TextLayer> const & getTextLayer() const {
        return textLayer;
    }
    
    /**
     * Gets the layers holding the tiles of a map.
     *
     * @return  the layers (maybe more than 1) of the tiles on the map.
     */

    std::list<QSharedPointer<TileLayer>> & getTileLayers() {
        return tileLayers;
    }
    
    /**
     * Gets the layers holding the tiles of a map.
     *
     * @return  the layers (maybe more than 1) of the tiles on the map.
     */

    std::list<QSharedPointer<TileLayer>> const & getTileLayers() const {
        return tileLayers;
    }
};


}
}

#endif
