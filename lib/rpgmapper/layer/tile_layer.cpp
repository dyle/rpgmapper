/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/tile_layer.hpp>

using namespace rpgmapper::model;

// TODO: remove, when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


TileLayer::TileLayer(Map * map, QObject * parent) : Layer{map, parent} {
}


void TileLayer::addField(Field const & field) {
    fields[field.getIndex()] = QSharedPointer<Field>{new Field{field}};
}


QSharedPointer<Field> const TileLayer::getField(int index) const {
    static QSharedPointer<Field> invalidField{new InvalidField};
    auto iter = fields.find(index);
    if (iter == fields.end()) {
        return invalidField;
    }
    return (*iter).second;
}


void TileLayer::draw(UNUSED QPainter & painter, UNUSED int tileSize) const {
}


QJsonObject TileLayer::getJSON() const {
    QJsonObject jsonObject = Layer::getJSON();
    return jsonObject;
}
