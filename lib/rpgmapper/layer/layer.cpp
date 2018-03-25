/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/layer/layer.hpp>
#include "layer_impl.hpp"

using namespace rpgmapper::model;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


Layer::Layer(Map * map, QObject * parent) : QObject{parent} {
    impl = std::make_shared<Layer::Impl>(map);
}


bool Layer::applyJsonObject(QJsonObject const & json) {

    if (json.contains("visible") && json["visible"].isBool()) {
        if (json["visible"].toBool()) {
            show();
        }
        else {
            hide();
        }
    }
    return true;
}


Layer::Attributes & Layer::getAttributes() {
    return impl->getAttributes();
}


Layer::Attributes const & Layer::getAttributes() const {
    return impl->getAttributes();
}


QJsonObject Layer::getJsonObject(UNUSED rpgmapper::model::io::Content & content) const {
    QJsonObject jsonObject;
    jsonObject["visible"] = isVisible();
    return jsonObject;
}


Map * Layer::getMap() {
    return impl->getMap();
}


Map const * Layer::getMap() const {
    return impl->getMap();
}


ResourceDBPointer & Layer::getResourceDB() {
    return getMap()->getResourceDB();
}


ResourceDBPointer const & Layer::getResourceDB() const {
    return getMap()->getResourceDB();
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
