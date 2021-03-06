/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_MAP_IMPL_HPP
#define RPGMAPPER_MODEL_MAP_IMPL_HPP

#include <QSize>

#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/nameable.hpp>


namespace rpgmapper::model {


class Map::Impl final : public Nameable, public CoordinateSystem {


public:

    explicit Impl(Map * map, Region * region);

    Impl(Impl const & ) = delete;

    bool applyJSON(QJsonObject const & json) override;

    AxisLayerPointer & getAxisLayer() {
        return axisLayer;
    }

    AxisLayerPointer const & getAxisLayer() const {
        return axisLayer;
    }

    BackgroundLayerPointer & getBackgroundLayer() {
        return backgroundLayer;
    }

    BackgroundLayerPointer const & getBackgroundLayer() const {
        return backgroundLayer;
    }

    TileLayers & getBaseLayers() {
        return baseLayers;
    }

    TileLayers const & getBaseLayers() const {
        return baseLayers;
    }

    CoordinateSystem & getCoordinateSystem() {
        return *this;
    }

    CoordinateSystem const & getCoordinateSystem() const {
        return *this;
    }

    GridLayerPointer & getGridLayer() {
        return gridLayer;
    }

    GridLayerPointer const & getGridLayer() const {
        return gridLayer;
    }

    QJsonObject getJSON(rpgmapper::model::io::Content & content) const override;

    static QString getInvalidCharactersInName();

    Region * getRegion() {
        return region;
    }

    Region const * getRegion() const {
        return region;
    }

    QString const & getRegionName() const;

    TileLayers & getTileLayers() {
        return tileLayers;
    }

    TileLayers const & getTileLayers() const {
        return tileLayers;
    }

    TextLayerPointer & getTextLayer() {
        return textLayer;
    }

    TextLayerPointer const & getTextLayer() const {
        return textLayer;
    }

    static bool isNameValid(QString name);

private:

    bool applyJsonBaseLayers(QJsonArray const & jsonArray);

    bool applyJsonLayers(QJsonObject const & json);

    bool applyJsonTileLayers(QJsonArray const & jsonArray);
};


}


#endif
