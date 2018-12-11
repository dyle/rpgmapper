/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/tile_layer.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/tile.hpp>

using namespace rpgmapper::model;

// TODO: remove, when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


TileLayer::TileLayer(Map * map) : Layer{map} {
}


void TileLayer::addField(Field const & field) {
    
    int index = field.getIndex();
    removeField(index);
    
    fields[field.getIndex()] = QSharedPointer<Field>{new Field{field}};
    emit fieldAdded(field.getPosition());
}


QSharedPointer<Field> const TileLayer::getField(int index) const {
    static QSharedPointer<Field> invalidField{new InvalidField};
    auto iter = fields.find(index);
    if (iter == fields.end()) {
        return invalidField;
    }
    return (*iter).second;
}


void TileLayer::draw(QPainter & painter, int tileSize) const {
    
    painter.save();
    
    auto rect = getMap()->getCoordinateSystem()->getInnerRect(tileSize);
    painter.setTransform(QTransform::fromTranslate(rect.right(), rect.top()));
    
    for (auto const & pair : getFields()) {
        
        painter.save();
        auto field = pair.second;
        auto position = field->getPosition();
        painter.setTransform(QTransform::fromTranslate(position.x() * tileSize, position.y() * tileSize));
        
        for (auto const & tile : field->getTiles()) {
            tile->draw(painter, tileSize);
        }
        
        painter.restore();
    }
    
    painter.restore();
}


QJsonObject TileLayer::getJSON() const {
    QJsonObject jsonObject = Layer::getJSON();
    return jsonObject;
}


void TileLayer::removeField(int index) {
    
    auto iter = fields.find(index);
    if (iter != fields.end()) {
        fields.erase(iter);
        emit fieldRemoved(Field::getPositionFromIndex(index));
    }
}
