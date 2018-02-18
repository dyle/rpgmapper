/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_REGION_HPP
#define RPGMAPPER_MODEL_REGION_HPP


#include <map>
#include <memory>
#include <set>

#include <QObject>
#include <QSharedPointer>

#include <rpgmapper/map.hpp>


namespace rpgmapper {
namespace model {


class Atlas;

class Region : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    Region() = delete;

    explicit Region(QString const & name, Atlas * atlas = nullptr);

    virtual ~Region() = default;

    bool addMap(MapPointer & map);

    bool applyJsonObject(QJsonObject const & json);

    MapPointer createMap(QString const & name);

    MapPointer findMap(QString const & name);

    Atlas * getAtlas();

    QJsonObject getJsonObject() const;

    Maps const & getMaps() const;

    std::set<QString> getMapNames() const;

    QString const & getName() const;

    virtual bool isValid() const { return true; }

    void removeMap(QString const & name);

    void setName(QString const & name);

private:

    void connectMapSignals(MapPointer & map);

    void disconnectMapSignals(MapPointer & map);

private slots:

    void changedMapName(QString const & nameBefore, QString const & nameAfter);

    void resizedMap();

signals:

    void mapAdded(QString const & mapName);

    void mapCreated(QString const & mapName);

    void mapNameChanged(QString const & nameBefore, QString const & nameAfter);

    void mapResized(QString const & mapName);

    void mapRemoved(QString const & mapName);

    void nameChanged(QString const & nameBefore, QString const & nameAfter);
};

class InvalidRegion final : public Region {
public:
    InvalidRegion() : Region{QString::Null{}, nullptr} {}
    bool isValid() const override { return false; }
};

using RegionPointer = QSharedPointer<Region>;

using Regions = std::map<QString, RegionPointer>;


}
}


#endif
