/*
 * atlas.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// ------------------------------------------------------------
// incs

#include <cassert>

#include <QDebug>
#include <QJsonArray>
#include <QTextCodec>

// rpgmapper
#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {


/**
 * Internal data of an Atlas object.
 */
class Atlas::Atlas_data {

public:

    Atlas_data() = default;

    Maps m_cMaps;                               /**< All the maps managed by this atlas. */
    Regions m_cRegions;                         /**< All the regions managed by this atlas. */
};


}
}


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent     parent object
 */
Atlas::Atlas(QObject * cParent) : Nameable{cParent} {

    d = std::make_shared<Atlas::Atlas_data>();

    name("New Atlas");
    createRegion()->addMap(createMap());

    modified(false);
}


/**
 * The id of a map changed.
 *
 * @param   nOldId      the old id
 */
void Atlas::changedMapId(mapid_t nOldId) {

    auto cMap = dynamic_cast<Map *>(sender());
    assert(cMap != nullptr);
    assert(d->m_cMaps.find(cMap->id()) == d->m_cMaps.end());
    auto iter = d->m_cMaps.find(nOldId);
    assert(iter != d->m_cMaps.end());

    d->m_cMaps[cMap->id()] = (*iter).second;
    d->m_cMaps.erase(nOldId);

    emit changedAtlas();
}


/**
 * The id of a region changed.
 *
 * @param   nOldId      the old id
 */
void Atlas::changedRegionId(regionid_t nOldId) {
    
    auto cRegion = dynamic_cast<Region *>(sender());
    assert(cRegion != nullptr);
    assert(d->m_cRegions.find(cRegion->id()) == d->m_cRegions.end());
    auto iter = d->m_cRegions.find(nOldId);
    assert(iter != d->m_cRegions.end());

    d->m_cRegions[cRegion->id()] = (*iter).second;
    d->m_cRegions.erase(nOldId);

    emit changedAtlas();
}


/**
 * Reset the atlas to an empty state.
 */
void Atlas::clear() {
    name("");
    d->m_cMaps.clear();
    d->m_cRegions.clear();
    modified(true);
}


/**
 * Creates a new map to this atlas.
 *
 * @return  a reference to the new map
 */
MapPointer Atlas::createMap() {

    auto cMap = Map::create(this);
    connect(cMap.data(), &Map::changedId, this, &Atlas::changedMapId);
    connect(cMap.data(), &Map::changedName, this, &Atlas::mapChangedName);

    d->m_cMaps.insert(std::make_pair(cMap->id(), cMap));
    return cMap;
}


/**
 * Creates a new region to this atlas.
 *
 * @return  a reference to the new region
 */
RegionPointer Atlas::createRegion() {

    auto cRegion = Region::create(this);
    connect(cRegion.data(), &Region::changedId, this, &Atlas::changedRegionId);
    connect(cRegion.data(), &Region::changedName, this, &Atlas::regionChangedName);

    d->m_cRegions.insert(std::make_pair(cRegion->id(), cRegion));
    return cRegion;
}


/**
 * Create a json string form this atlas.
 *
 * @param   eJsonFormat     the format for representation
 * @return  a string holding the atlas in json format
 */
QString Atlas::json(QJsonDocument::JsonFormat eJsonFormat) const {
    QJsonObject cJSON;
    save(cJSON);
    QJsonDocument cJSONDoc{cJSON};
    return QTextCodec::codecForName("UTF-8")->toUnicode(cJSONDoc.toJson(eJsonFormat).data());
}


/**
 * Load the atlas from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Atlas::load(QJsonObject const & cJSON) {

    clear();

    Nameable::load(cJSON);

    if (cJSON.contains("maps") && cJSON["maps"].isArray()) {

        QJsonArray cJSONMaps = cJSON["maps"].toArray();
        for (auto && cJSONMap : cJSONMaps) {
            auto cMap = createMap();
            cMap->load(cJSONMap.toObject());
        }
    }

    if (cJSON.contains("regions") && cJSON["regions"].isArray()) {

        QJsonArray cJSONRegions = cJSON["regions"].toArray();
        for (auto &&cJSONRegion : cJSONRegions) {
            auto cRegion = createRegion();
            cRegion->load(cJSONRegion.toObject());
        }
    }

    modified(false);
}


/**
 * A map has changed its name.
 */
void Atlas::mapChangedName() {
    auto cMap = dynamic_cast<Map *>(sender());
    if (cMap != nullptr) {
        emit changedMapName(cMap->id());
        emit changedAtlas();
    }
}


/**
 * Return all the maps managed by this atlas.
 *
 * @return  all maps of this atlas
 */
Maps & Atlas::maps() {
    return d->m_cMaps;
}


/**
 * Return all the maps managed by this atlas.
 *
 * @return  all maps of this atlas
 */
Maps const & Atlas::maps() const {
    return d->m_cMaps;
}


/**
 * State if the atlas (and any descendants) has changed.
 *
 * @return  true, if the atlas (or any descendants) has changed.
 */
bool Atlas::modified() const {

    if (Nameable::modified()) {
        return true;
    }

    if (std::any_of(maps().begin(),
                    maps().end(),
                    [](Maps::value_type const & cPair) { return cPair.second->modified(); })) {
        return true;
    }

    return std::any_of(regions().begin(),
                       regions().end(),
                       [](Regions::value_type const & cPair) { return cPair.second->modified(); });
}


/**
 * Set the atlas and all descendants to a new modification state.
 * Only applies "true" to the current item and not to all maps and regions.
 *
 * @param   bModified       the new modification state
 */
void Atlas::modified(bool bModified) {

    Nameable::modified(bModified);

    if (!bModified) {

        std::for_each(maps().begin(),
                      maps().end(),
                      [&] (Maps::value_type & cPair) { cPair.second->modified(bModified); });

        std::for_each(regions().begin(),
                      regions().end(),
                      [&] (Regions::value_type & cPair) { cPair.second->modified(bModified); });
    }

    emit changedAtlas();
}


/**
 * A region has changed its name.
 */
void Atlas::regionChangedName() {
    auto cRegion = dynamic_cast<Region *>(sender());
    if (cRegion != nullptr) {
        emit changedRegionName(cRegion->id());
        emit changedAtlas();
    }
}


/**
 * Return all the regions managed by this atlas.
 *
 * @return  all regions of this atlas
 */
Regions & Atlas::regions() {
    return d->m_cRegions;
}


/**
 * Return all the regions managed by this atlas.
 *
 * @return  all regions of this atlas
 */
Regions const & Atlas::regions() const {
    return d->m_cRegions;
}


/**
 * Save the atlas to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Atlas::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    QJsonArray cJSONRegions;
    for (auto const & cRegion: d->m_cRegions) {
        QJsonObject cJSONRegion;
        cRegion.second->save(cJSONRegion);
        cJSONRegions.append(cJSONRegion);
    }
    cJSON["regions"] = cJSONRegions;

    QJsonArray cJSONMaps;
    for (auto const & cMap: d->m_cMaps) {
        QJsonObject cJSONMap;
        cMap.second->save(cJSONMap);
        cJSONMaps.append(cJSONMap);
    }
    cJSON["maps"] = cJSONMaps;
}
