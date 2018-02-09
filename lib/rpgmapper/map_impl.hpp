/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_MAP_IMPL_HPP
#define RPGMAPPER_MODEL_MAP_IMPL_HPP


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

public:

    explicit Impl(Map * map, Region * region);

    Impl(Impl const & ) = delete;

    bool applyJsonObject(QJsonObject const & json) override;

    LayerPointer const & getBackgroundLayer() const;

    QJsonObject getJsonObject() const override ;

    Region * getRegion() { return region; }
};

}
}


#endif
