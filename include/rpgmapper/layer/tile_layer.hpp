/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_TILE_LAYER_HPP


#include <rpgmapper/layer.hpp>


using namespace rpgmapper::model;

namespace rpgmapper {
namespace model {

class TileLayer : public Layer {

    Q_OBJECT

    std::map<int, Field> fields;

public:

    explicit TileLayer(Map * map, QObject * parent = nullptr);

    void addField(Field const & field);

    Field const & getField(int index) const;

    Field const & getField(int x, int y) const { return getField(Field::getIndex(x, y)); }

    Field const & getField(QPoint const & point) const { return getField(point.x(), point.y()); }

};

using TileLayerPointer = QSharedPointer<TileLayer>;

using TileLayers = std::list<TileLayerPointer>;


}
}


#endif
