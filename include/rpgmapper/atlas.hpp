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


class Atlas;

using AtlasPointer = QSharedPointer<Atlas>;

class Atlas : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    explicit Atlas(QObject * parent = nullptr);

    ~Atlas() override = default;

    bool applyJsonObject(QJsonObject json);

    RegionPointer & createRegion(QString const & name);

    MapPointer & findMap(QString const & name);

    MapPointer const & findMap(QString const & name) const;

    RegionPointer & findRegion(QString const & name);

    RegionPointer const & findRegion(QString const & name) const;

    std::set<QString> getAllMapNames() const;

    std::set<QString> getAllRegionNames() const;

    rpgmapper::model::command::ProzessorPointer & getCommandProzessor();

    rpgmapper::model::command::ProzessorPointer const & getCommandProzessor() const;

    QJsonObject getJsonObject() const;

    QString const & getFileName() const;

    static QString getInvalidCharactersInName();

    QString const & getName() const;

    Regions const & getRegions() const;

    void init();

    bool isModified() const;

    static bool isNameValid(QString name);

    virtual bool isValid() const { return true; }

    bool moveMap(QString const & map, QString const & regionTo) {
        return moveMap(findMap(map), findRegion(regionTo));
    }

    bool moveMap(MapPointer map, RegionPointer regionTo);

    static AtlasPointer const & null();

    void removeRegion(QString const & name);

    void resetChanged();

    void setFileName(QString const & fileName);

    void setName(QString const & name);

private:

    void connectRegionSignals(RegionPointer & region);

private slots:

    void changedRegionName(QString nameBefore, QString nameAfter);

signals:

    void commandExecuted();

    void mapAdded(QString regionName, QString mapName);

    void mapCreated(QString regionName, QString mapName);

    void mapNameChanged(QString regionName, QString nameBefore, QString nameAfter);

    void mapNumeralForAxisChanged(QString regionName, QString mapName);

    void mapRemoved(QString regionName, QString mapName);

    void mapResized(QString regionName, QString mapName);

    void nameChanged(QString name);

    void regionCreated(QString name);

    void regionNameChanged(QString nameBefore, QString nameAfter);

    void regionRemoved(QString name);
};

class InvalidAtlas final : public Atlas {
public:
    InvalidAtlas() : Atlas{nullptr} {}
    bool isValid() const override { return false; }
};


}
}


#endif
