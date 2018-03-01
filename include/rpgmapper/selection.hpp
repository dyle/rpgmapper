/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_SELECTION_HPP
#define RPGMAPPER_MODEL_SELECTION_HPP


#include <QSharedPointer>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>


namespace rpgmapper {
namespace model {


class Selection : public QObject {

    Q_OBJECT

    AtlasPointer atlas;
    MapPointer map;
    RegionPointer region;

public:

    explicit Selection(QObject * parent);

    ~Selection() override = default;

    QString createNewMapName() const;

    QString createNewRegionName() const;

    AtlasPointer & getAtlas() { return atlas; }

    AtlasPointer const & getAtlas() const { return atlas; }

    MapPointer & getMap() { return map; }

    MapPointer const & getMap() const { return map; }

    RegionPointer & getRegion() { return region; }

    RegionPointer const & getRegion() const { return region; }

    void setAtlas(AtlasPointer atlas);

    void selectMap(MapPointer map);

    void selectMap(QString const & mapName);

    void selectRegion(RegionPointer region);

    void selectRegion(QString const & regionName);


public slots:

    void removedMap(QString regionName, QString mapName);

    void removedRegion(QString name);

signals:

    void newAtlas();

    void mapSelected(QString mapName);

    void regionSelected(QString regionName);
};

using SelectionPointer = QSharedPointer<Selection>;


}
}


#endif
