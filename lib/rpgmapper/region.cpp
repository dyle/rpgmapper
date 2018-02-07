/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/atlas.hpp>
#include "region_impl.hpp"


Region::Region(QString const & name, Atlas * atlas) : QObject{atlas} {
    impl = std::make_shared<Region::Impl>(atlas, this);
    impl->setName(name);
}


Atlas * Region::getAtlas() {
    return impl->getAtlas();
}


MapPointer Region::createMap(QString const & name) {
    auto map = impl->createMap(name);
    if (map->isValid()) {
        emit mapCreated(name);
    }
    return map;
}


Maps const & Region::getMaps() const {
    return impl->getMaps();
}


std::set<QString> Region::getMapNames() const {
    return impl->getMapNames();
}


QString const & Region::getName() const {
    return impl->getName();
}


void Region::removeMap(QString const & name) {
    if (impl->removeMap(name)) {
        emit mapRemoved(name);
    }
}


void Region::setName(QString const & name) {
    if (name == impl->getName()) {
        return;
    }
    impl->setName(name);
    emit changedName();
}












#if 0


/**
 * Global region id counter.
 */
static regionid_t g_nRegionIdCounter = 0;


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cRegion      parent object
 * @param   nId     id of the region
 */
Region::Region(Region * cRegion, regionid_t nId) : Nameable{cRegion}, m_nId{nId} {

    if (cRegion == nullptr) {
        throw std::invalid_argument("Region argument shall not be nullptr.");
    }

    d = std::make_shared<Region::Region_data>();
    d->m_cRegion = cRegion;
    d->m_nOrderValue = nId;

    init();
}


/**
 * Adds a map to this region.
 *
 * @param   cMap    the map to add.
 */
void Region::addMap(MapPointer & cMap) {

    if (cMap.data() == nullptr) {
        throw std::invalid_argument("Map argument shall not be nullptr.");
    }

    if (d->m_cMaps.find(cMap->id()) == d->m_cMaps.end()) {

        d->m_cMaps.insert(cMap->id());
        cMap->setRegion(d->m_cRegion->regionById(id()));
        connect(cMap.data(), &Map::changedRegion, this, &Region::changedMapRegion);

        emit addedMap(cMap->id());
    }
}


/**
 * A map changed its region.
 */
void Region::changedMapRegion() {

    auto * cMap = dynamic_cast<Map *>(QObject::sender());
    if (!cMap) {
        return;
    }
    auto nMapId = cMap->id();
    auto nRegionId = cMap->region()->id();

    if (nRegionId == id()) {
        addMap(d->m_cRegion->mapById(nMapId));
    }
    else {
        if (d->m_cMaps.find(nMapId) != d->m_cMaps.end()) {
            removeMap(nMapId);
        }
    }


    // TODO
//    if (nOldRegionId == id()) {
//        addMap(d->m_cRegion->maps()[nMapId]);
//        return;
//    }
//
//    auto nRegionId = cMap->region()->id();
//    if ((nOldRegionId == id()) && (d->m_cMaps.find(nMapId) != d->m_cMaps.end())) {
//
//        d->m_cMaps.erase(nMapId);
//
            // TODO
//        disconnect(cMap, &Map::changedRegion, this, &Region::changedMapRegion);
//
//        emit removedMap(d->m_cRegion->maps()[nMapId]);
//    }
//
//    if ((nRegionId == id()) && (d->m_cMaps.find(nMapId) == d->m_cMaps.end())) {
//        addMap(d->m_cRegion->maps()[nMapId]);
//    }

}


/**
 * Reset the region to an empty state.
 */
void Region::clear() {
    setName("");
}


/**
 * Create a new region (factory method).
 *
 * @param   cRegion      parent object
 * @return  a new region
 */
RegionPointer Region::create(Region * cRegion) {
    if (cRegion == nullptr) {
        throw std::invalid_argument("Region argument shall not be nullptr.");
    }
    return RegionPointer{new Region{cRegion, ++g_nRegionIdCounter}, &Region::deleteLater};
}


/**
 * Provide some nice initial state.
 */
void Region::init() {
    clear();
    setName("New Region " + QString::number(id()));
}


/**
 * Load the region from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Region::load(QJsonObject const & cJSON) {

    clear();
    Nameable::load(cJSON);

    if (cJSON.contains("id") && cJSON["id"].isDouble()) {
        m_nId = cJSON["id"].toInt();
        g_nRegionIdCounter = std::max(g_nRegionIdCounter, m_nId);
    }
    if (cJSON.contains("orderValue") && cJSON["orderValue"].isDouble()) {
        setOrderValue(cJSON["orderValue"].toInt());
    }

    if (cJSON.contains("maps") && cJSON["maps"].isArray()) {

        QJsonArray cJSONMaps = cJSON["maps"].toArray();
        for (auto && cJSONMapId : cJSONMaps) {
            if (cJSONMapId.isDouble()) {
                addMap(d->m_cRegion->mapById(cJSONMapId.toInt()));
            }
        }
    }
}


/**
 * Load the region from json.
 *
 * @param   cJSON       the json instance to load from
 * @param   cRegion      parent object
 * @return  the loaded region instance
 */
RegionPointer Region::load(QJsonObject const & cJSON, Region * cRegion) {
    auto cRegion = RegionPointer{new Region{cRegion, -1}, &Map::deleteLater};
    cRegion->load(cJSON);
    return cRegion;
}


/**
 * Get all maps of this region.
 *
 * @return  The maps of this region.
 */
Maps Region::maps() const {

    Maps cMaps;
    std::for_each(d->m_cMaps.begin(),
                  d->m_cMaps.end(),
                  [&] (mapid_t nId) { cMaps.insert(std::make_pair(nId, d->m_cRegion->mapById(nId))); });
    return cMaps;
}


/**
 * Means to order this region among other regions.
 *
 * @return  a value indicating the position of this region among others
 */
int Region::orderValue() const {
    return d->m_nOrderValue;
}



/**
 * Remove a map from this region.
 *
 * @param   nMapId      id of the map removed
 */
void Region::removeMap(rpgmapper::model::mapid_t nMapId) {

    if (d->m_cMaps.find(nMapId) != d->m_cMaps.end()) {

        auto cMap = d->m_cRegion->mapById(nMapId);
        if (cMap.data() != nullptr) {
            disconnect(cMap.data(), &Map::changedRegion, this, &Region::changedMapRegion);
        }

        d->m_cMaps.erase(nMapId);
        emit removedMap(nMapId);
    }
}


/**
 * Save the region to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Region::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    cJSON["id"] = id();
    cJSON["orderValue"] = orderValue();

    QJsonArray cJSONMaps;
    for (auto nMapId: d->m_cMaps) {
        cJSONMaps.append(nMapId);
    }
    cJSON["maps"] = cJSONMaps;
}


/**
 * Set the means to order this region among other regions.
 *
 * @param   nOrderValue     a value indicating the position of this region among others
 */
void Region::setOrderValue(int nOrderValue) {

    if (d->m_nOrderValue == nOrderValue) {
        return;
    }
    d->m_nOrderValue = nOrderValue;
    setModified(true);
}
#endif
