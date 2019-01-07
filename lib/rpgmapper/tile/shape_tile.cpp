/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/layer/tile_layer.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/resource/shape.hpp>
#include <rpgmapper/tile/tile_insert_modes.hpp>
#include <rpgmapper/field.hpp>
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


void ShapeTile::draw(QPainter & painter, int tileSize) {
    
    auto shape = getShape();
    if (!shape) {
        return;
    }
    
    auto pixmap = shape->getPixmap(tileSize, getRotation(), getStretch());
    painter.drawPixmap(0, 0, pixmap);
}


TileInsertMode ShapeTile::getInsertMode() const {
    
    auto shape = getShape();
    if (!shape) {
        return TileInsertMode::additive;
    }
    
    return shape->getInsertMode();
    
}


QSharedPointer<rpgmapper::model::layer::TileLayer> & ShapeTile::getLayer(rpgmapper::model::Map * map) const {
    
    static QSharedPointer<rpgmapper::model::layer::TileLayer> nullLayer;
    
    if (!map) {
        return nullLayer;
    }
    auto shape = getShape();
    if (!shape) {
        return nullLayer;
    }
    
    auto layerIndex = shape->getZOrdering();
    switch (shape->getTargetLayer()) {
    
        case Shape::TargetLayer::unknown:
            return nullLayer;
    
        case Shape::TargetLayer::base:
            prepareLayers(map->getLayers().getBaseLayers(), layerIndex);
            return map->getLayers().getBaseLayers()[layerIndex];
    
        case Shape::TargetLayer::tile:
            prepareLayers(map->getLayers().getTileLayers(), layerIndex);
            return map->getLayers().getTileLayers()[layerIndex];
    }
    
    return nullLayer;
}


QSharedPointer<rpgmapper::model::layer::TileLayer> const &
        ShapeTile::getLayer(rpgmapper::model::Map const * map) const {
    
    static QSharedPointer<rpgmapper::model::layer::TileLayer> nullLayer;
    
    if (!map) {
        return nullLayer;
    }
    auto shape = getShape();
    if (!shape) {
        return nullLayer;
    }
    
    auto layerIndex = shape->getZOrdering();
    switch (shape->getTargetLayer()) {
        
        case Shape::TargetLayer::unknown:
            return nullLayer;
        
        case Shape::TargetLayer::base:
            if (map->getLayers().getBaseLayers().size() <= layerIndex) {
                return nullLayer;
            }
            return map->getLayers().getBaseLayers()[layerIndex];
        
        case Shape::TargetLayer::tile:
            if (map->getLayers().getTileLayers().size() <= layerIndex) {
                return nullLayer;
            }
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


rpgmapper::model::resource::Shape * ShapeTile::getShape() const {
    
    auto path = getPath();
    if (path.isEmpty()) {
        return nullptr;
    }
    
    auto resource = ResourceDB::getResource(path);
    return dynamic_cast<Shape *>(resource.data());
}


bool ShapeTile::isPlaceable(rpgmapper::model::Map const * map, QPointF position) const {
    
    auto & layer = getLayer(map);
    if (!layer) {
        return true;
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


TilePointer ShapeTile::place(Tiles & replaced, rpgmapper::model::Map * map, QPointF position) {
    
    if (!isPlaceable(map, position)) {
        throw std::runtime_error{"Tile is not placeable on this position on the given layer stack."};
    }
    
    auto shape = getShape();
    if (!shape) {
        throw std::runtime_error{"Failed to lookup shape for tile."};
    }
    
    auto & layer = getLayer(map);
    if (!layer) {
        throw std::runtime_error{"Got a nullptr layer though tile thinks it is placeable."};
    }
    
    if (!layer->isFieldPresent(position)) {
        layer->addField(FieldPointer{new Field{position}});
    }
    auto field = layer->getField(position);
    
    switch (shape->getInsertMode()) {
        
        case TileInsertMode::additive:
            break;
        
        case TileInsertMode::exclusive:
            replaced = field->getTiles();
            field->getTiles().clear();
            break;
    }
    
    auto placedTile = new ShapeTile{*this};
    placedTile->setMap(map);
    placedTile->setPosition(position);
    
    auto tile = QSharedPointer<Tile>{placedTile};
    field->getTiles().push_back(tile);
    return tile;
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


void ShapeTile::remove() {
    
    auto map = getMap();
    if (!map) {
        throw rpgmapper::model::exception::invalid_map{};
    }
    
    auto shape = getShape();
    if (!shape) {
        throw std::runtime_error{"Failed to lookup shape for tile."};
    }
    
    auto & layer = getLayer(map);
    if (!layer) {
        throw std::runtime_error{"Got a nullptr layer though tile thinks it is on a layer."};
    }
    if (!layer->isFieldPresent(getPosition())) {
        return;
    }
    
    auto field = layer->getField(getPosition());
    auto & tiles = field->getTiles();
    for (auto iter = tiles.begin(); iter != tiles.end(); ++iter) {
        if ((*(*iter).data()) == (*this)) {
            tiles.erase(iter);
            break;
        }
    }
}
