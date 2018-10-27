/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_IMPL_HPP
#define RPGMAPPER_MODEL_ATLAS_IMPL_HPP


#include <rpgmapper/atlas.hpp>
#include <rpgmapper/nameable.hpp>


namespace rpgmapper {
namespace model {


class Atlas::Impl final : public Nameable {

    Atlas * atlas = nullptr;
    Regions regions;
    QSharedPointer<rpgmapper::model::command::Processor> prozessor;
    unsigned long unmodifiedCommandCounter = 0;
    QString fileName;
    ResourceDBPointer resourceDB;

public:

    explicit Impl(Atlas * atlas);

    Impl(Impl const &) = delete;

    bool applyJSON(QJsonObject const & json) override;

    void clear() override;

    void collectIOContent(rpgmapper::model::io::Content & content) const;

    QSharedPointer<rpgmapper::model::Region> & createRegion(QString const & name);

    QSharedPointer<rpgmapper::model::Map> & findMap(QString const & name);

    QSharedPointer<rpgmapper::model::Map> const & findMap(QString const & name) const;

    QSharedPointer<rpgmapper::model::Region> & findRegion(QString const & name);

    QSharedPointer<rpgmapper::model::Region> const & findRegion(QString const & name) const;

    std::set<QString> getAllMapNames() const;

    std::set<QString> getAllRegionNames() const;

    QSharedPointer<rpgmapper::model::command::Processor> & getCommandProzessor();

    QSharedPointer<rpgmapper::model::command::Processor> const & getCommandProzessor() const;

    QString const & getFileName() const {
        return fileName;
    }

    static QString getInvalidCharactersInName();

    QJsonObject getJSON(rpgmapper::model::io::Content & content) const override;

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

    bool moveMap(QSharedPointer<rpgmapper::model::Map> map, QSharedPointer<rpgmapper::model::Region> regionTo);

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
