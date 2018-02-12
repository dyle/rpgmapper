/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_GRID_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_GRID_LAYER_HPP


#include <rpgmapper/layer/layer.hpp>


using namespace rpgmapper::model;

namespace rpgmapper {
namespace model {

class GridLayer : public Layer {

    Q_OBJECT

public:

    explicit GridLayer(Map * map, QObject * parent = nullptr);

};

using GridLayerPointer = QSharedPointer<GridLayer>;


}
}


#endif
