/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/layer/layer_stack.hpp>

#include "color_tile.hpp"


using namespace rpgmapper::model::tiles;

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


ColorTile::ColorTile() : Tile() {
    getAttributes()["type"] = "color";
}


ColorTile::ColorTile(rpgmapper::model::Tile::Attributes & attributes) : Tile{attributes} {
    getAttributes()["type"] = "color";
}


bool ColorTile::operator==(const rpgmapper::model::Tile & rhs) const {
    return getAttributes() == rhs.getAttributes();
}


QColor ColorTile::getColor() const {
    
    auto const & attributes = getAttributes();
    auto iter = attributes.find("color");
    if (iter == attributes.end()) {
        return QColor{Qt::black};
    }
    return QColor{(*iter).second};
}


void ColorTile::draw(QPainter & painter, int tileSize) {
    QRect rect{0, 0, tileSize, tileSize};
    painter.fillRect(rect, getColor());
}


bool ColorTile::place(float x, float y, rpgmapper::model::LayerStack * layerStack) {
    
    if (!layerStack) {
        throw std::runtime_error{"LayerStack must not be nullptr when placing a tile."};
    }
    
    // ColorTiles always add to the lowest base layer.
    auto layer = layerStack->getBaseLayers()[0];
    if (!layer->isFieldPresent(static_cast<int>(x), static_cast<int>(y))) {
        layer->addField(Field{static_cast<int>(x), static_cast<int>(y)});
    }
    auto field = layer->getField(static_cast<int>(x), static_cast<int>(y));
    
    if (!field->getTiles().empty() && ((*field->getTiles()[0].data()) == (*this))) {
        return false;
    }
    
    // placing a color tile removes all other tiles on the same layer.
    field->getTiles().clear();
    field->getTiles().push_back(QSharedPointer<Tile>(new ColorTile{*this}));
    return true;
}
