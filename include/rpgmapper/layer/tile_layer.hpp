/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP


#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {

class TileLayer : public Layer {

    Q_OBJECT

    std::map<int, FieldPointer> fields;

public:

    explicit TileLayer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    ~TileLayer() override = default;

    void addField(Field const & field);

    FieldPointer const getField(int index) const;

    FieldPointer const getField(int x, int y) const { return getField(Field::getIndex(x, y)); }

    FieldPointer const getField(QPoint const & point) const { return getField(point.x(), point.y()); }

    void draw(QPainter & painter, int tileSize) const override;
};

using TileLayerPointer = QSharedPointer<TileLayer>;

using TileLayers = std::list<TileLayerPointer>;


}
}


#endif
