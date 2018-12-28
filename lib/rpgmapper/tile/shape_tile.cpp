/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/command/additive_tile_placer.hpp>
#include <rpgmapper/command/exclusive_tile_placer.hpp>
#include <rpgmapper/resource/resource_db.hpp>
#include <rpgmapper/tile/tile_insert_modes.hpp>

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


bool ShapeTile::isPlaceable(float x, float y, rpgmapper::model::layer::LayerStack const * layerStack) const {
    
    if (!layerStack) {
        return false;
    }
    
    auto resource = getShape();
    auto shape = dynamic_cast<Shape const *>(resource.data());
    if (!shape) {
        return false;
    }
    
    switch (shape->getTargetLayer()) {
        
        case Shape::TargetLayer::unknown:
            return false;
        
        case Shape::TargetLayer::base:
            return isPlaceableOnLayer(shape, x, y, layerStack->getBaseLayers());
        
        case Shape::TargetLayer::tile:
            return isPlaceableOnLayer(shape, x, y, layerStack->getTileLayers());
    }
    
    return false;
}


bool ShapeTile::isPlaceableOnLayer(rpgmapper::model::resource::Shape const * shape,
        float x,
        float y,
        std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> const & layers) const {
    
    if ((layers.size() - 1) < shape->getZOrdering()) {
        return true;
    }
    auto layer = layers[shape->getZOrdering()].data();
    if (!layer->isFieldPresent(static_cast<int>(x), static_cast<int>(y))) {
        return true;
    }
    
    auto field = layer->getField(static_cast<int>(x), static_cast<int>(y));
    if (field->isTilePresent(this)) {
        return false;
    }
    
    return true;
}


Tiles ShapeTile::place(bool & placed, float x, float y, rpgmapper::model::layer::LayerStack * layerStack) {
    
    placed = false;
    
    if (!isPlaceable(x, y, layerStack)) {
        throw std::runtime_error{"Tile is not placeable on this position on the given layer stack."};
    }
    
    auto resource = getShape();
    auto shape = dynamic_cast<Shape *>(resource.data());

    Tiles tiles;
    switch (shape->getTargetLayer()) {
    
        case Shape::TargetLayer::unknown:
            break;
            
        case Shape::TargetLayer::base:
            tiles = placeOnLayer(placed, shape, x, y, layerStack->getBaseLayers());
            break;
    
        case Shape::TargetLayer::tile:
            tiles = placeOnLayer(placed, shape, x, y, layerStack->getTileLayers());
            break;
    }
    
    return tiles;
}


Tiles ShapeTile::placeOnLayer(bool & placed,
        rpgmapper::model::resource::Shape * shape,
        float x,
        float y,
        std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> & layers) {
    
    auto map = layers[0]->getMap();
    if (!map) {
        placed = false;
        return Tiles{};
    }
    
    while (layers.size() <= shape->getZOrdering()) {
        layers.push_back(QSharedPointer<TileLayer>{new TileLayer{map}});
    }
    auto layer = layers[shape->getZOrdering()].data();
    
    return placeOnLayer(placed, shape, x, y, layer);
}


Tiles ShapeTile::placeOnLayer(bool & placed,
        rpgmapper::model::resource::Shape * shape,
        float x,
        float y,
        rpgmapper::model::layer::TileLayer * layer) {
    
    if (!layer->isFieldPresent(static_cast<int>(x), static_cast<int>(y))) {
        layer->addField(Field{static_cast<int>(x), static_cast<int>(y)});
    }
    auto field = layer->getField(static_cast<int>(x), static_cast<int>(y));
    
    Tiles tiles;
    switch (shape->getInsertMode()) {
        
        case TileInsertMode::additive:
            break;
        
        case TileInsertMode::exclusive:
            tiles = field->getTiles();
            field->getTiles().clear();
            break;
    }
    
    field->getTiles().push_back(QSharedPointer<Tile>(new ShapeTile{*this}));
    placed = true;
    
    return tiles;
}
