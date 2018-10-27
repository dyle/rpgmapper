/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/layer_stack.hpp>

using namespace rpgmapper::model;


std::list<rpgmapper::model::Layer const *> LayerStack::collectVisibleLayers() const {

    std::list<Layer const *> layers;

    if (getBackgroundLayer()->isVisible()) {
        layers.push_back(getBackgroundLayer().data());
    }

    for (auto & baseLayer : getBaseLayers()) {
        if (baseLayer->isVisible()) {
            layers.push_back(baseLayer.data());
        }
    }

    if (getGridLayer()->isVisible()) {
        layers.push_back(getGridLayer().data());
    }

    if (getAxisLayer()->isVisible()) {
        layers.push_back(getAxisLayer().data());
    }

    for (auto & tileLayer : getTileLayers()) {
        if (tileLayer->isVisible()) {
            layers.push_back(tileLayer.data());
        }
    }

    if (getTextLayer()->isVisible()) {
        layers.push_back(getTextLayer().data());
    }

    return layers;
}
