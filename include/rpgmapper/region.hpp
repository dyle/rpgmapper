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

    bool applyJsonObject(QJsonObject const & json);

    MapPointer createMap(QString const & name);

    Atlas * getAtlas();

    QJsonObject getJsonObject() const;

    Maps const & getMaps() const;

    std::set<QString> getMapNames() const;

    QString const & getName() const;

    virtual bool isValid() const { return true; }

    void removeMap(QString const & name);

    void setName(QString const & name);

signals:

    void changedName();

    void mapCreated(QString name);

    void mapRemoved(QString name);

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













#if 0

    /**
     * Create a new region (factory method).
     *
     * @param   cAtlas      parent object
     * @return  a new region
     */
    static RegionPointer create(Atlas * cAtlas);


    /**
     * Adds a map to this region.
     *
     * @param   cMap    the map to add.
     */
    void addMap(MapPointer & cMap);


    /**
     * Return the id of the region.
     *
     * @return  the id of the region
     */
    regionid_t id() const { return m_nId; }


    /**
     * Load the region from json.
     *
     * @param   cJSON       the json instance to load from
     * @param   cAtlas      parent object
     * @return  the loaded region instance
     */
    static RegionPointer load(QJsonObject const & cJSON, Atlas * cAtlas);


    /**
     * Get all maps of this region.
     *
     * @return  The maps of this region.
     */
    Maps maps() const;


    /**
     * Means to order this region among other regions.
     *
     * @return  a value indicating the position of this region among others
     */
    int orderValue() const;


    /**
     * Remove a map from this region.
     *
     * @param   nMapId      id of the map removed
     */
    void removeMap(rpgmapper::model::mapid_t nMapId);


    /**
     * Save the region to json.
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


    /**
     * Set the means to order this region among other regions.
     *
     * @param   nOrderValue     a value indicating the position of this region among others
     */
    void setOrderValue(int nOrderValue);


public slots:


    /**
     * Reset the region to an empty state.
     */
    void clear();


protected:


    /**
     * Load the region from json.
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


private slots:


    /**
     * A map changed its region.
     */
    void changedMapRegion();


signals:


    /**
     * A map has been added to this region.
     *
     * @param   nMapId      id of the map added
     */
    void addedMap(rpgmapper::model::mapid_t nMapId);


    /**
     * A map has been removed from this region.
     *
     * @param   nMapId      id of the map removed
     */
    void removedMap(rpgmapper::model::mapid_t nMapId);


private:


    /**
     * Ctor.
     *
     * @param   cAtlas      parent object
     * @param   nId     id of the region
     */
    explicit Region(Atlas * cAtlas, regionid_t nId);


    /**
     * Provide some nice initial state.
     */
    void init();


    regionid_t m_nId;                               /**< Region id. */

    class Region_data;                              /**< Internal data type. */
    std::shared_ptr<Region::Region_data> d;         /**< Internal data instance. */

#endif

