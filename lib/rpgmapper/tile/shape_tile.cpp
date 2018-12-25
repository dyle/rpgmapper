/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/resource/resource_db.hpp>

#include "shape_tile.hpp"

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
    
    QRect rect{0, 0, tileSize, tileSize};
    
    auto resource = getShape();
    auto shape = dynamic_cast<Shape const *>(resource.data());
    if (!shape) {
        return;
    }
    
    auto pixmap = shape->getPixmap(tileSize);
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


bool ShapeTile::isPlaceable(UNUSED float x,
        UNUSED float y,
        rpgmapper::model::layer::LayerStack const * layerStack) const {
    
    if (!layerStack) {
        return false;
    }
    
    auto resource = getShape();
    auto shape = dynamic_cast<Shape const *>(resource.data());
    if (!shape) {
        return false;
    }
    
    return true;
}


bool ShapeTile::place(float x, float y, LayerStack * layerStack) {
    
    if (!isPlaceable(x, y, layerStack)) {
        throw std::runtime_error{"Tile is not placeable on this position on the given layer stack."};
    }
    
    auto resource = getShape();
    auto shape = dynamic_cast<Shape *>(resource.data());

    switch (shape->getTargetLayer()) {
    
        case Shape::TargetLayer::unknown:
            return false;
            
        case Shape::TargetLayer::base:
            return placeOnLayer(shape, x, y, layerStack->getBaseLayers());
    
        case Shape::TargetLayer::tile:
            return placeOnLayer(shape, x, y, layerStack->getTileLayers());
    }
    
    return false;
}


bool ShapeTile::placeOnLayer(rpgmapper::model::resource::Shape * shape,
        float x,
        float y,
        std::vector<QSharedPointer<rpgmapper::model::layer::TileLayer>> & layerStack) {
    
    auto map = layerStack[0]->getMap();
    if (!map) {
        return false;
    }
    
    while (layerStack.size() <= shape->getZOrdering()) {
        layerStack.push_back(QSharedPointer<TileLayer>{new TileLayer{map}});
    }
    auto layer = layerStack[shape->getZOrdering()].data();
    
    return placeOnLayer(x, y, layer);
}


bool ShapeTile::placeOnLayer(float x, float y, rpgmapper::model::layer::TileLayer * layer) {
    
    if (!layer->isFieldPresent(static_cast<int>(x), static_cast<int>(y))) {
        layer->addField(Field{static_cast<int>(x), static_cast<int>(y)});
    }
    auto field = layer->getField(static_cast<int>(x), static_cast<int>(y));
    
    field->getTiles().push_back(QSharedPointer<Tile>(new ShapeTile{*this}));
    return true;
}
