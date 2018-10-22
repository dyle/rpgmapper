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
    rpgmapper::model::command::ProcessorPointer prozessor;
    unsigned long unmodifiedCommandCounter = 0;
    QString fileName;
    ResourceDBPointer resourceDB;

public:

    explicit Impl(Atlas * atlas);

    Impl(Impl const &) = delete;

    bool applyJsonObject(QJsonObject const & json) override;

    void clear() override;

    void collectIOContent(rpgmapper::model::io::Content & content) const;

    RegionPointer & createRegion(QString const & name);

    MapPointer & findMap(QString const & name);

    MapPointer const & findMap(QString const & name) const;

    RegionPointer & findRegion(QString const & name);

    RegionPointer const & findRegion(QString const & name) const;

    std::set<QString> getAllMapNames() const;

    std::set<QString> getAllRegionNames() const;

    rpgmapper::model::command::ProcessorPointer & getCommandProzessor();

    rpgmapper::model::command::ProcessorPointer const & getCommandProzessor() const;

    QString const & getFileName() const {
        return fileName;
    }

    static QString getInvalidCharactersInName();

    QJsonObject getJsonObject(rpgmapper::model::io::Content & content) const override;

    Regions const & getRegions() const {
        return regions;
    }

    ResourceDBPointer & getResourceDB() {
        return resourceDB;
    }

    ResourceDBPointer const & getResourceDB() const {
        return resourceDB;
    }

    bool isModified() const;

    static bool isNameValid(QString name);

    bool moveMap(MapPointer map, RegionPointer regionTo);

    void readIOContent(rpgmapper::model::io::Content const & content);

    bool removeRegion(QString const & name);

    void renameRegion(QString nameBefore, QString nameAfter);

    void resetChanged();

    void setFileName(QString const & fileName) {
        this->fileName = fileName;
    }

    void setName(QString const & name) override;

private:

    bool applyJsonRegionsArray(QJsonArray const & jsonRegions);

};


}
}


#endif
