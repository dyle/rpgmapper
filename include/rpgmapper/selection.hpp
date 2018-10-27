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

    QSharedPointer<rpgmapper::model::Atlas> atlas;
    QSharedPointer<rpgmapper::model::Map> map;
    QSharedPointer<rpgmapper::model::Region> region;

public:

    explicit Selection(QObject * parent);

    ~Selection() override = default;

    QString createNewMapName() const;

    QString createNewRegionName() const;

    QSharedPointer<rpgmapper::model::Atlas> & getAtlas() {
        return atlas;
    }

    QSharedPointer<rpgmapper::model::Atlas> const & getAtlas() const {
        return atlas;
    }

    QSharedPointer<rpgmapper::model::Map> & getMap() {
        return map;
    }

    QSharedPointer<rpgmapper::model::Map> const & getMap() const {
        return map;
    }

    QSharedPointer<rpgmapper::model::Region> & getRegion() {
        return region;
    }

    QSharedPointer<rpgmapper::model::Region> const & getRegion() const {
        return region;
    }

    void setAtlas(QSharedPointer<rpgmapper::model::Atlas> atlas);

    void selectMap(QSharedPointer<rpgmapper::model::Map> map);

    void selectMap(QString const & mapName);

    void selectRegion(QSharedPointer<rpgmapper::model::Region> region);

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
