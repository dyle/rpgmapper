/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_ATLAS_HPP
#define RPGMAPPER_MODEL_ATLAS_HPP


#include <memory>

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QSharedPointer>

//#include <rpgmapper/nameable.hpp>
//#include <rpgmapper/map.hpp>
//#include <rpgmapper/region.hpp>


namespace rpgmapper {
namespace model {


class Atlas : public QObject {

    Q_OBJECT

    class Impl;
    std::shared_ptr<Atlas::Impl> impl;

public:

    explicit Atlas(QObject * parent = nullptr);

    QString const & getName() const;

    void setName(QString const & name);



/*
    Map createMap();

    Region createRegion();

    Map & getCurrentMap();

    Region & getCurrentRegion();

    Map const & getMap(rpgmapper::model::mapid_t mapId) const;

    Maps const & getMaps() const;

    Region const & getRegion(rpgmapper::model::regionid_t regionId) const;

    Regions const & getRegions() const;

    void load(QJsonObject const & json) override;

    bool isModified() const override;

    QString toJson(QJsonDocument::JsonFormat format = QJsonDocument::Indented) const;

    void save(QJsonObject & json) const override;

    void setModified(bool modified) override;
*/
public slots:

/*
    void deleteMap(rpgmapper::model::mapid_t mapId);

    void deleteRegion(rpgmapper::model::regionid_t regionId);

    void setCurrentMap(rpgmapper::model::mapid_t mapId);

    void setCurrentRegion(rpgmapper::model::regionid_t regionId);
*/
private slots:

/*
    void changedMapName();

    void changedRegionName();
*/
signals:

    void changed();
/*
    void createdMap(rpgmapper::model::mapid_t mapId);

    void createdRegion(rpgmapper::model::regionid_t regionId);

    void deletedMap(rpgmapper::model::mapid_t mapId);

    void deletedRegion(rpgmapper::model::regionid_t regionId);

    void selectedMap(rpgmapper::model::mapid_t mapId);

    void selectedRegion(rpgmapper::model::regionid_t regionId);
*/
private:
/*
    void clear();

    void init();
*/
};


using AltasPointer = QSharedPointer<Atlas>;


}
}


#endif
