/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_HPP
#define RPGMAPPER_MODEL_ATLAS_HPP


#include <memory>
#include <set>

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QSharedPointer>

#include <rpgmapper/region.hpp>
#include <rpgmapper/command/prozessor.hpp>


namespace rpgmapper {
namespace model {


class Atlas : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    explicit Atlas(QObject * parent = nullptr);

    ~Atlas() override = default;

    bool applyJsonObject(QJsonObject json);

    RegionPointer createRegion(QString const & name);

    MapPointer findMap(QString const & name);

    MapPointer const findMap(QString const & name) const;

    RegionPointer findRegion(QString const & name);

    RegionPointer const findRegion(QString const & name) const;

    std::set<QString> getAllMapNames() const;

    std::set<QString> getAllRegionNames() const;

    rpgmapper::model::command::ProzessorPointer & getCommandProzessor();

    rpgmapper::model::command::ProzessorPointer const & getCommandProzessor() const;

    QJsonObject getJsonObject() const;

    QString const & getFileName() const;

    QString const & getName() const;

    Regions const & getRegions() const;

    bool isModified() const;

    virtual bool isValid() const { return true; }

    bool moveMap(QString const & map, QString const & regionTo) {
        return moveMap(findMap(map), findRegion(regionTo));
    }

    bool moveMap(MapPointer map, RegionPointer regionTo);

    void removeRegion(QString const & name);

    void resetChanged();

    void setFileName(QString const & fileName);

    void setName(QString const & name);

signals:

    void nameChanged(QString const & name);

    void mapAdded(QString const & regionName, QString const & mapName);

    void mapCreated(QString const & mapName);

    void mapNameChanged(QString const & mapNameBefore, QString const & mapNameAfter);

    void mapResized(QString const & mapName);

    void mapRemoved(QString const & mapName);

    void regionCreated(QString const & name);

    void regionNameChanged(QString const & nameBefore, QString const & nameAfter);

    void regionRemoved(QString const & name);

};

class InvalidAtlas final : public Atlas {
public:
    InvalidAtlas() : Atlas{nullptr} {}
    bool isValid() const override { return false; }
};

using AtlasPointer = QSharedPointer<Atlas>;


}
}


#endif
