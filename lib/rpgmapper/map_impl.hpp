/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_MAP_IMPL_HPP
#define RPGMAPPER_MODEL_MAP_IMPL_HPP


#include <QSize>

#include <rpgmapper/map.hpp>
#include "nameable.hpp"

using namespace rpgmapper::model;


namespace rpgmapper {
namespace model {


class Map::Impl final : public Nameable {

    QString name;
    Map * map = nullptr;
    Region * region = nullptr;

    LayerPointer backgroundLayer;
    Layers baseLayers;
    LayerPointer gridLayer;
    LayerPointer textLayer;
    Layers tileLayers;

    QSize size;

public:

    explicit Impl(Map * map, Region * region);

    Impl(Impl const & ) = delete;

    bool applyJsonObject(QJsonObject const & json) override;

    LayerPointer const & getBackgroundLayer() const { return backgroundLayer; }

    Layers const & getBaseLayers() const { return baseLayers; }

    LayerPointer const & getGridLayer() const { return gridLayer; }

    QJsonObject getJsonObject() const override ;

    Region * getRegion() { return region; }

    QSize getSize() const  { return size; }

    Layers const & getTileLayers() const { return tileLayers; }

    LayerPointer const & getTextLayer() const { return textLayer; }

    void resize(QSize const & size);

};

}
}


#endif
