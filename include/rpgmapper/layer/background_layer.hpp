/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_LAYER_BACKGROUND_LAYER_HPP
#define RPGMAPPER_MODEL_LAYER_BACKGROUND_LAYER_HPP


#include <rpgmapper/layer/layer.hpp>


namespace rpgmapper {
namespace model {

class BackgroundLayer : public Layer {

    Q_OBJECT

public:

    explicit BackgroundLayer(rpgmapper::model::Map * map, QObject * parent = nullptr);

    virtual ~BackgroundLayer() = default;

    QColor getColor() const;

};

using BackgroundLayerPointer = QSharedPointer<BackgroundLayer>;


}
}


#endif
