/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/layer.hpp>

using namespace rpgmapper::model::layer;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   ifndef UNUSED
#       define UNUSED   __attribute__((unused))
#   endif
#else
#   define UNUSED
#endif


Layer::Layer(Map * map) : map{map} {
}


bool Layer::applyJSON(UNUSED QJsonObject const & json) {
    return true;
}


QJsonObject Layer::getJSON() const {
    QJsonObject jsonObject;
    return jsonObject;
}


void Layer::setMap(Map * map) {
    this->map = map;
}
