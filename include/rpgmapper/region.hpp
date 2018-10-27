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
#include <rpgmapper/resource_db.hpp>
#include <rpgmapper/io/content.hpp>


namespace rpgmapper {
namespace model {


class Atlas;
class Region;

using Regions = std::map<QString, QSharedPointer<rpgmapper::model::Region>>;

class Region : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    Region() = delete;

    explicit Region(QString const & name, Atlas * atlas = nullptr);

    ~Region() override = default;

    bool addMap(QSharedPointer<rpgmapper::model::Map> & map);

    bool applyJSON(QJsonObject const & json);

    QSharedPointer<rpgmapper::model::Map> & createMap(QString const & name);
    
    static QString createRegionName();
    
    QSharedPointer<rpgmapper::model::Map> & findMap(QString const & name);

    Atlas * getAtlas();

    Atlas const * getAtlas() const;

    static QString getInvalidCharactersInName();

    QJsonObject getJSON(rpgmapper::model::io::Content & content) const;
    
    std::map<QString, QSharedPointer<rpgmapper::model::Map>> const & getMaps() const;

    std::set<QString> getMapNames() const;

    QString const & getName() const;

    static bool isNameValid(QString name);

    virtual bool isValid() const {
        return true;
    }

    static QSharedPointer<rpgmapper::model::Region> const & null();

    void removeMap(QString const & name);

    void setName(QString const & name);

private:

    void connectMapSignals(QSharedPointer<rpgmapper::model::Map> & map);

    void disconnectMapSignals(QSharedPointer<rpgmapper::model::Map> & map);

private slots:

    void changedMapName(QString nameBefore, QString nameAfter);

    void changedNumeralForAxis(QString mapName);

    void resizedMap(QString mapName);

signals:

    void mapAdded(QString regionName, QString mapName);

    void mapCreated(QString regionName, QString mapName);

    void mapNameChanged(QString regionName, QString nameBefore, QString nameAfter);

    void mapNumeralForAxisChanged(QString regionName, QString mapName);

    void mapRemoved(QString regionName, QString mapName);

    void mapResized(QString regionName, QString mapName);

    void nameChanged(QString nameBefore, QString nameAfter);
};


class InvalidRegion final : public Region {

public:

    InvalidRegion()
        : Region{QString::Null{}, nullptr} {
    }

    bool isValid() const override {
        return false;
    }
};


}
}


#endif
