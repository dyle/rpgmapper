/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/exclusive_tile_placer.hpp>
#include <rpgmapper/layer/layer_stack.hpp>

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


bool ColorTile::isPlaceable(float x, float y, rpgmapper::model::layer::LayerStack const * layerStack) const {
    
    if (!layerStack) {
        return false;
    }
    
    // ColorTiles always add to the lowest base layer.
    auto layer = layerStack->getBaseLayers()[0];
    if (!layer->isFieldPresent(static_cast<int>(x), static_cast<int>(y))) {
        return true;
    }
    auto field = layer->getField(static_cast<int>(x), static_cast<int>(y));
    if (field->isTilePresent(this)) {
        return false;
    }
    
    return true;
}


bool ColorTile::place(float x, float y, LayerStack * layerStack) {
    
    if (!isPlaceable(x, y, layerStack)) {
        throw std::runtime_error{"Tile is not placeable on this position on the given layer stack."};
    }
    
    // ColorTiles always add to the lowest base layer.
    auto layer = layerStack->getBaseLayers()[0];
    if (!layer->isFieldPresent(static_cast<int>(x), static_cast<int>(y))) {
        layer->addField(Field{static_cast<int>(x), static_cast<int>(y)});
    }
    auto field = layer->getField(static_cast<int>(x), static_cast<int>(y));
    
    // placing a color tile removes all other tiles on the same layer.
    field->getTiles().clear();
    field->getTiles().push_back(QSharedPointer<Tile>(new ColorTile{*this}));
    return true;
}
