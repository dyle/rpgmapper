/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/layer/text_layer.hpp>

using namespace rpgmapper::model;

// TODO: remove when done.
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


TextLayer::TextLayer(Map * map, QObject * parent) : Layer{map, parent} {
}


void TextLayer::draw(UNUSED QPainter & painter, UNUSED int tileSize) const {

}


QJsonObject TextLayer::getJSON(rpgmapper::model::io::Content & content) const {
    QJsonObject jsonObject = Layer::getJSON(content);
    return jsonObject;
}
