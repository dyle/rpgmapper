/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/additive_tile_placer.hpp>
#include <rpgmapper/command/exclusive_tile_placer.hpp>
#include <rpgmapper/layer/tile_layer.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/shape.hpp>
#include <rpgmapper/tile/tile_insert_modes.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

#include "shape_tile.hpp"

using namespace rpgmapper::model::command;
using namespace rpgmapper::model::layer;
using namespace rpgmapper::model::resource;
using namespace rpgmapper::model::tile;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


ShapeTile::ShapeTile() : Tile() {
    getAttributes()["type"] = "shape";
}


ShapeTile::ShapeTile(Tile::Attributes & attributes) : Tile{attributes} {
    getAttributes()["type"] = "shape";
}


bool ShapeTile::operator==(const Tile & rhs) const {
    return getAttributes() == rhs.getAttributes();
}


rpgmapper::model::command::CommandPointer ShapeTile::createPlacerCommand(QString mapName, QPointF position) const {
    
    auto tile = TilePointer{new ShapeTile{*this}};
    auto command = CommandPointer{new AdditiveTilePlacer{mapName, tile, position}};
    return command;
}


void ShapeTile::draw(QPainter & painter, int tileSize) {
    
    QRect rect{0, 0, tileSize, tileSize};
    
    auto resource = getShape();
    auto shape = dynamic_cast<Shape const *>(resource.data());
    if (!shape) {
        return;
    }
    
    auto pixmap = shape->getPixmap(tileSize, getRotation(), getStretch());
    painter.drawPixmap(0, 0, pixmap);
}


QSharedPointer<rpgmapper::model::layer::TileLayer> & ShapeTile::getLayer(rpgmapper::model::MapPointer map) const {
    
    static QSharedPointer<rpgmapper::model::layer::TileLayer> nullLayer;
    
    if (!map) {
        return nullLayer;
    }
    auto resource = getShape();
    auto shape = dynamic_cast<Shape const *>(resource.data());
    if (!shape) {
        return nullLayer;
    }
    
    auto layerIndex = shape->getZOrdering();
    switch (shape->getTargetLayer()) {
    
        case Shape::TargetLayer::unknown:
            return nullLayer;
            break;
    
        case Shape::TargetLayer::base:
            prepareLayers(map->getLayers().getBaseLayers(), layerIndex);
            return map->getLayers().getBaseLayers()[layerIndex];
    
        case Shape::TargetLayer::tile:
            prepareLayers(map->getLayers().getTileLayers(), layerIndex);
            return map->getLayers().getTileLayers()[layerIndex];
    }
    
    return nullLayer;
}


QString ShapeTile::getPath() const {
    
    auto const & attributes = getAttributes();
    
    auto pair = attributes.find("path");
    if (pair == attributes.end()) {
        return QString::null;
    }
    
    return (*pair).second;
}


rpgmapper::model::resource::ResourcePointer ShapeTile::getShape() const {
    
    auto path = getPath();
    if (path.isEmpty()) {
        return ResourcePointer{};
    }
    return ResourceDB::getResource(path);
}


bool ShapeTile::isPlaceable(rpgmapper::model::MapPointer map, QPointF position) const {
    
    auto & layer = getLayer(map);
    if (!layer) {
        return false;
    }
    
    if (!layer->isFieldPresent(position)) {
        return true;
    }
    
    auto field = layer->getField(position);
    if (field->isTilePresent(this)) {
        return false;
    }
    
    return true;
}


Tiles ShapeTile::place(bool & placed, rpgmapper::model::MapPointer map, QPointF position) {
    
    placed = false;
    if (!isPlaceable(map, position)) {
        throw std::runtime_error{"Tile is not placeable on this position on the given layer stack."};
    }
    
    auto resource = getShape();
    auto shape = dynamic_cast<Shape const *>(resource.data());
    if (!shape) {
        throw std::runtime_error{"Failed to lookup shape for tile."};
    }
    
    auto & layer = getLayer(map);
    if (!layer) {
        throw std::runtime_error{"Got a NULL layer though tile thinks it is placeable."};
    }
    
    if (!layer->isFieldPresent(position)) {
        layer->addField(Field{position});
    }
    auto field = layer->getField(position);
    
    Tiles tiles;
    switch (shape->getInsertMode()) {
        
        case TileInsertMode::additive:
            break;
        
        case TileInsertMode::exclusive:
            tiles = field->getTiles();
            field->getTiles().clear();
            break;
    }
    
    auto placedTile = new ShapeTile{*this};
    placedTile->setMap(map);
    placedTile->setPosition(position);
    field->getTiles().push_back(QSharedPointer<Tile>{placedTile});
    
    placed = true;
    
    return tiles;
}


void ShapeTile::prepareLayers(std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> & layers,
        unsigned int index) const {

    if (layers.empty()) {
        return;
    }
    
    auto map = layers[0]->getMap();
    while (layers.size() <= index) {
        layers.push_back(QSharedPointer<TileLayer>{new TileLayer{map}});
    }
}


void ShapeTile::remove() const {
}
