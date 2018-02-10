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

public:

    explicit TileLayer(Map * map, QObject * parent = nullptr);

};

using TileLayerPointer = QSharedPointer<TileLayer>;

using TileLayers = std::list<TileLayerPointer>;


}
}


#endif
