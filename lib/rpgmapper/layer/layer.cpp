/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/layer/layer.hpp>
#include "layer_impl.hpp"

using namespace rpgmapper::model;


Layer::Layer(Map * map, QObject * parent) : QObject{parent} {
    impl = std::make_shared<Layer::Impl>(map);
}


Layer::Attributes & Layer::getAttributes() {
    return impl->getAttributes();
}


Layer::Attributes const & Layer::getAttributes() const {
    return impl->getAttributes();
}


Map * Layer::getMap() {
    return impl->getMap();
}


Map const * Layer::getMap() const {
    return impl->getMap();
}


void Layer::hide() {
    if (impl->isVisible()) {
        impl->hide();
        emit visibilityChanged();
    }
}


bool Layer::isVisible() const {
    return impl->isVisible();
}


void Layer::show() {
    if (!impl->isVisible()) {
        impl->show();
        emit visibilityChanged();
    }
}
