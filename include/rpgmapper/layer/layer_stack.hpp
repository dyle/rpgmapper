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

class LayerStack {

public:

    std::list<rpgmapper::model::Layer const *> collectVisibleLayers() const;

    virtual AxisLayerPointer const & getAxisLayer() const = 0;

    virtual BackgroundLayerPointer const & getBackgroundLayer() const = 0;

    virtual TileLayers const & getBaseLayers() const  = 0;

    virtual GridLayerPointer const & getGridLayer() const  = 0;

    virtual TileLayers const & getTileLayers() const  = 0;

    virtual TextLayerPointer const & getTextLayer() const  = 0;
};


}
}

#endif
