/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_MAP_IMPL_HPP
#define RPGMAPPER_MODEL_MAP_IMPL_HPP


#include <QSize>

#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include "nameable.hpp"


namespace rpgmapper {
namespace model {


class Map::Impl final : public Nameable, public CoordinateSystem {

    QString name;
    Map * map = nullptr;
    Region * region = nullptr;

    BackgroundLayerPointer backgroundLayer;
    TileLayers baseLayers;
    GridLayerPointer gridLayer;
    TextLayerPointer textLayer;
    TileLayers tileLayers;

public:

    explicit Impl(Map * map, Region * region);

    Impl(Impl const & ) = delete;

    bool applyJsonObject(QJsonObject const & json) override;

    BackgroundLayerPointer getBackgroundLayer() { return backgroundLayer; }

    BackgroundLayerPointer const getBackgroundLayer() const { return backgroundLayer; }

    TileLayers & getBaseLayers() { return baseLayers; }

    TileLayers const & getBaseLayers() const { return baseLayers; }

    CoordinateSystem & getCoordinateSystem() { return *this; }

    CoordinateSystem const & getCoordinateSystem() const { return *this; }

    GridLayerPointer getGridLayer() { return gridLayer; }

    GridLayerPointer const getGridLayer() const { return gridLayer; }

    QJsonObject getJsonObject() const override ;

    Region * getRegion() { return region; }

    QString getRegionName() const { return region != nullptr ? region->getName() : QString::null; }

    TileLayers & getTileLayers() { return tileLayers; }

    TileLayers const & getTileLayers() const { return tileLayers; }

    TextLayerPointer getTextLayer() { return textLayer; }

    TextLayerPointer const getTextLayer() const { return textLayer; }

};

}
}


#endif
