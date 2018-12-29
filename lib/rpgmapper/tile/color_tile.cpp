/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/layer/layer_stack.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

#include "color_tile.hpp"

using namespace rpgmapper::model::command;
using namespace rpgmapper::model::layer;
using namespace rpgmapper::model::tile;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


ColorTile::ColorTile() : Tile() {
    getAttributes()["type"] = "color";
}


ColorTile::ColorTile(Tile::Attributes & attributes) : Tile{attributes} {
    getAttributes()["type"] = "color";
}


bool ColorTile::operator==(const Tile & rhs) const {
    return getAttributes() == rhs.getAttributes();
}


void ColorTile::draw(QPainter & painter, int tileSize) {
    QRect rect{0, 0, tileSize, tileSize};
    painter.fillRect(rect, getColor());
}


QColor ColorTile::getColor() const {
    
    auto const & attributes = getAttributes();
    auto iter = attributes.find("color");
    if (iter == attributes.end()) {
        return QColor{Qt::black};
    }
    return QColor{(*iter).second};
}


bool ColorTile::isPlaceable(rpgmapper::model::Map const * map, QPointF position) const {
    
    if (!map) {
        return false;
    }
    
    // ColorTiles always add to the lowest base layer.
    auto layer = map->getLayers().getBaseLayers()[0];
    if (!layer->isFieldPresent(position)) {
        return true;
    }
    auto field = layer->getField(position);
    
    return !field->isTilePresent(this);
}


TilePointer ColorTile::place(Tiles & replaced, rpgmapper::model::Map * map, QPointF position) {
    
    if (!isPlaceable(map, position)) {
        throw std::runtime_error{"Tile is not placeable on this position on the given layer stack."};
    }
    
    // ColorTiles always add to the lowest base layer.
    auto layer = map->getLayers().getBaseLayers()[0];
    if (!layer->isFieldPresent(position)) {
        layer->addField(Field{position});
    }
    auto field = layer->getField(position);
    
    // placing a color tile removes all other tiles on the same layer.
    replaced = field->getTiles();
    field->getTiles().clear();
    
    auto placedTile = new ColorTile{*this};
    placedTile->setMap(map);
    placedTile->setPosition(position);
    
    auto tile = QSharedPointer<Tile>{placedTile};
    field->getTiles().push_back(tile);
    return tile;
}


void ColorTile::remove() const {

    auto map = getMap();
    if (!map) {
        throw rpgmapper::model::exception::invalid_map{};
    }
    
    auto layer = map->getLayers().getBaseLayers()[0];
    if (!layer->isFieldPresent(getPosition())) {
        return;
    }
    
    auto field = layer->getField(getPosition());
    field->getTiles().clear();
}
