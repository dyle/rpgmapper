/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/layer/layer.hpp>

using namespace rpgmapper::model;


Layer::Layer(Map * map) : map{map} {
}


bool Layer::applyJSON(QJsonObject const & json) {

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


QJsonObject Layer::getJSON() const {
    QJsonObject jsonObject;
    jsonObject["visible"] = isVisible();
    return jsonObject;
}


void Layer::hide() {
    if (isVisible()) {
        visible = false;
        emit visibilityChanged();
    }
}


void Layer::setMap(Map * map) {
    this->map = map;
}


void Layer::show() {
    if (!isVisible()) {
        visible = true;
        emit visibilityChanged();
    }
}
