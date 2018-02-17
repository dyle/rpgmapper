/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_IMPL_HPP
#define RPGMAPPER_MODEL_ATLAS_IMPL_HPP


#include <rpgmapper/atlas.hpp>
#include "nameable.hpp"


namespace rpgmapper {
namespace model {


class Atlas::Impl final : public Nameable {

    Atlas * atlas = nullptr;
    Regions regions;
    rpgmapper::model::command::ProzessorPointer prozessor;
    unsigned int unmodifiedCommandCounter = 0;

public:

    explicit Impl(Atlas * atlas);

    Impl(Impl const &) = delete;

    bool applyJsonObject(QJsonObject const & json) override;

    void clear() override;

    RegionPointer createRegion(QString const & name);

    MapPointer findMap(QString const & name);

    MapPointer const findMap(QString const & name) const;

    RegionPointer findRegion(QString const & name);

    RegionPointer const findRegion(QString const & name) const;

    std::set<QString> getAllMapNames() const;

    std::set<QString> getAllRegionNames() const;

    rpgmapper::model::command::ProzessorPointer & getCommandProzessor();

    rpgmapper::model::command::ProzessorPointer const & getCommandProzessor() const;

    QJsonObject getJsonObject() const override;

    Regions const & getRegions() const { return regions; }

    void init();

    bool isModified() const;

    bool moveMap(MapPointer map, RegionPointer regionTo);

    bool removeRegion(QString const & name);

    void resetChanged();

    void setName(QString const & name) override;

private:

    bool applyJsonRegionsArray(QJsonArray const & jsonRegions);

};


}
}


#endif
