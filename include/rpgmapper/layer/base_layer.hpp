/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_BASE_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_BASE_LAYER_HPP


#include <rpgmapper/layer.hpp>


using namespace rpgmapper::model;

namespace rpgmapper {
namespace model {

class BaseLayer : public Layer {

Q_OBJECT

public:

    BaseLayer(Map * map, QObject * parent = nullptr);

};


using BaseLayerPointer = QSharedPointer<BaseLayer>;

using BaseLayers = std::list<BaseLayerPointer>;


}
}


#endif
