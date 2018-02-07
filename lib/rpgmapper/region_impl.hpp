/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_REGION_IMPL_HPP
#define RPGMAPPER_MODEL_REGION_IMPL_HPP


#include <rpgmapper/region.hpp>

using namespace rpgmapper::model;


namespace rpgmapper {
namespace model {


class Region::Impl final {

    Atlas * atlas = nullptr;
    Maps maps;
    QString name;
    Region * region = nullptr;

public:

    explicit Impl(Atlas * atlas, Region * region);

    Impl(Impl const &) = delete;

    MapPointer createMap(QString const & name);

    Atlas * getAtlas() { return atlas; }

    std::set<QString> getMapNames() const;

    Maps const & getMaps() const { return maps; }

    QString const & getName() const { return name; }

    bool removeMap(QString const & name);

    void setName(QString const & name) { this->name = name; }
};


}
}


#endif
