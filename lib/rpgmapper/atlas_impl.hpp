/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_IMPL_HPP
#define RPGMAPPER_MODEL_ATLAS_IMPL_HPP


#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;

namespace rpgmapper {
namespace model {

class Atlas::Impl final {

    Atlas * atlas = nullptr;
    bool changed = false;
    QString name;
    Regions regions;

public:

    explicit Impl(Atlas * atlas);

    Impl(Impl const &) = delete;

    bool applyJsonObject(QJsonObject const & json);

    void clear();

    RegionPointer createRegion(QString const & name);

    std::set<QString> getAllMapNames() const;

    std::set<QString> getAllRegionNames() const;

    QJsonObject getJsonObject() const;

    QString const & getName() const { return name; }

    RegionPointer const & getRegion(QString const & name) const;

    Regions const & getRegions() const { return regions; }

    bool hasChanged() const { return changed; }

    void init();

    bool removeRegion(QString const & name);

    void resetChanged();

    void setName(QString const & name);

private:

    bool applyJsonRegionsArray(QJsonArray const & jsonRegions);

};

}
}


#endif
