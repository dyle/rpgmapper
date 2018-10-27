/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_REGION_IMPL_HPP
#define RPGMAPPER_MODEL_REGION_IMPL_HPP


#include <rpgmapper/region.hpp>
#include <rpgmapper/nameable.hpp>


namespace rpgmapper {
namespace model {


class Region::Impl final : public Nameable {

    Atlas * atlas = nullptr;
    Maps maps;
    Region * region = nullptr;

public:

    explicit Impl(Atlas * atlas, Region * region);

    Impl(Impl const &) = delete;

    bool addMap(QSharedPointer<rpgmapper::model::Map> & map);

    bool applyJSON(QJsonObject const & json) override;

    void clear() override;

    QSharedPointer<rpgmapper::model::Map> & createMap(QString const & name);

    QSharedPointer<rpgmapper::model::Map> & findMap(QString const & name);

    Atlas * getAtlas() {
        return atlas;
    }

    Atlas const * getAtlas() const {
        return atlas;
    }

    static QString getInvalidCharactersInName();

    QJsonObject getJSON(rpgmapper::model::io::Content & content) const override;

    std::set<QString> getMapNames() const;

    Maps const & getMaps() const {
        return maps;
    }

    static bool isNameValid(QString name);

    bool removeMap(QString const & name);

private:

    bool applyJsonMapsArray(QJsonArray const & jsonMaps);
};


}
}


#endif
