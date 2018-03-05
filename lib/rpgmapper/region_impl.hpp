/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_REGION_IMPL_HPP
#define RPGMAPPER_MODEL_REGION_IMPL_HPP


#include <rpgmapper/region.hpp>
#include "nameable.hpp"


namespace rpgmapper {
namespace model {


class Region::Impl final : public Nameable {

    Atlas * atlas = nullptr;
    Maps maps;
    Region * region = nullptr;

public:

    explicit Impl(Atlas * atlas, Region * region);

    Impl(Impl const &) = delete;

    bool addMap(MapPointer & map);

    bool applyJsonObject(QJsonObject const & json) override;

    void clear() override;

    MapPointer & createMap(QString const & name);

    MapPointer & findMap(QString const & name);

    Atlas * getAtlas() { return atlas; }

    static QString getInvalidCharactersInName();

    QJsonObject getJsonObject() const override;

    std::set<QString> getMapNames() const;

    Maps const & getMaps() const { return maps; }

    static bool isNameValid(QString name);

    bool removeMap(QString const & name);

private:

    bool applyJsonMapsArray(QJsonArray const & jsonMaps);
};


}
}


#endif
