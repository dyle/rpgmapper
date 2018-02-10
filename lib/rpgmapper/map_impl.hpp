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

    BackgroundLayerPointer backgroundLayer;
    BaseLayers baseLayers;
    GridLayerPointer gridLayer;
    TextLayerPointer textLayer;
    TileLayers tileLayers;

    QSize size;

public:

    explicit Impl(Map * map, Region * region);

    Impl(Impl const & ) = delete;

    bool applyJsonObject(QJsonObject const & json) override;

    BackgroundLayerPointer const & getBackgroundLayer() const { return backgroundLayer; }

    BaseLayers const & getBaseLayers() const { return baseLayers; }

    GridLayerPointer const & getGridLayer() const { return gridLayer; }

    QJsonObject getJsonObject() const override ;

    Region * getRegion() { return region; }

    QSize getSize() const  { return size; }

    TileLayers const & getTileLayers() const { return tileLayers; }

    TextLayerPointer const & getTextLayer() const { return textLayer; }

    void resize(QSize const & size);

};

}
}


#endif
