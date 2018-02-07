/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_MAP_IMPL_HPP
#define RPGMAPPER_MODEL_MAP_IMPL_HPP


#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


namespace rpgmapper {
namespace model {


class Map::Impl final {

    QString name;
    Region * region = nullptr;

public:

    explicit Impl(Region * region);

    Impl(Impl const & ) = delete;

    QString const & getName() const { return name; }

    Region * getRegion() { return region; }

    void setName(QString const & name) { this->name = name; }
};

}
}


#endif
