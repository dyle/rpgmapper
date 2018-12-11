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


void ColorTile::place(int x, int y, rpgmapper::model::LayerStack * layerStack) {
    
    if (!layerStack) {
        throw std::runtime_error{"LayerStack must not be nullptr when placing a tile."};
    }
    
    QSharedPointer<Field> field;
    auto layer = layerStack->getCurrentBaseLayer();
    if (!layer->isFieldPresent(x, y)) {
        layer->addField(Field{x, y});
    }
    field = layer->getField(x, y);
    
    // placing a color tile removes all other tiles.
    field->getTiles().clear();
    field->getTiles().push_back(QSharedPointer<Tile>(new ColorTile{*this}));
}
