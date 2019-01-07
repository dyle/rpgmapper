/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_field.hpp>
#include <rpgmapper/layer/tile_layer.hpp>
#include <rpgmapper/tile/tile.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/field.hpp>
#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::layer;


TileLayer::TileLayer(Map * map) : Layer{map} {
}


void TileLayer::addField(rpgmapper::model::FieldPointer field) {
    
    if (!field) {
        throw rpgmapper::model::exception::invalid_field{};
    }
    
    int index = field->getIndex();
    removeField(index);
    
    fields[index] = field;
    emit fieldAdded(field->getPosition());
}


rpgmapper::model::FieldPointer const TileLayer::getField(int index) const {
    static QSharedPointer<Field> invalidField{new InvalidField};
    auto iter = fields.find(index);
    if (iter == fields.end()) {
        return invalidField;
    }
    return (*iter).second;
}


rpgmapper::model::FieldPointer const TileLayer::getField(int x, int y) const {
    return getField(Field::getIndex(x, y));
}


void TileLayer::draw(QPainter & painter, int tileSize) const {
    
    painter.save();
    
    auto innerRect = getMap()->getCoordinateSystem()->getInnerRect(tileSize);
    for (auto const & pair : getFields()) {
        
        auto field = pair.second;
        auto position = field->getPosition();
        QPoint moveBy{innerRect.left() + position.x() * tileSize, innerRect.top() + position.y() * tileSize};
        painter.translate(moveBy);
        for (auto const & tile : field->getTiles()) {
            tile->draw(painter, tileSize);
        }
        painter.resetTransform();
    }
    
    painter.restore();
}


QJsonObject TileLayer::getJSON() const {
    QJsonObject jsonObject = Layer::getJSON();
    return jsonObject;
}


bool TileLayer::isFieldPresent(int x, int y) const {
    return getField(Field::getIndex(x, y))->isValid();
}


void TileLayer::removeField(int index) {
    
    auto iter = fields.find(index);
    if (iter != fields.end()) {
        fields.erase(iter);
        emit fieldRemoved(Field::getPositionFromIndex(index));
    }
}


void TileLayer::removeField(int x, int y) {
    removeField(Field::getIndex(x, y));
}
