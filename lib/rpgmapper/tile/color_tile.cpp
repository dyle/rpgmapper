/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/exclusive_tile_placer.hpp>
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


rpgmapper::model::command::CommandPointer ColorTile::createPlacerCommand(QString mapName, QPointF position) const {
    auto tile = TilePointer{new ColorTile{*this}};
    auto command = CommandPointer{new ExclusiveTilePlacer{mapName, tile, position}};
    return command;
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


bool ColorTile::isPlaceable(rpgmapper::model::MapPointer map, QPointF position) const {
    
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


Tiles ColorTile::place(bool & placed, rpgmapper::model::MapPointer map, QPointF position) {
    
    placed = false;
    
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
    auto tiles = field->getTiles();
    field->getTiles().clear();
    
    auto placedTile = new ColorTile{*this};
    placedTile->setMap(map);
    placedTile->setPosition(position);
    field->getTiles().push_back(QSharedPointer<Tile>{placedTile});
    
    placed = true;
    
    return tiles;
}


void ColorTile::remove() const {
}
