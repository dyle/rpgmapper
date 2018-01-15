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

    Regions m_cRegions;                         /**< all the regions managed by this Atlas */
    Region::id_t m_nRegionIdCounter = 0;        /**< region id counter */
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
Atlas::Atlas(QObject * cParent) : Nameable(cParent) {
    d = std::make_shared<Atlas::Atlas_data>();
    name("New Atlas");
    createRegion();
}


/**
 * reset the atlas to empty state
 */
void Atlas::clear() {
    name("");
    d->m_cRegions.clear();
    d->m_nRegionIdCounter = 0;
    modified(true);
}


/**
 * Creates a new region to this atlas
 *
 * @return  a reference to the new region
 */
RegionPointer Atlas::createRegion() {

    d->m_nRegionIdCounter += 1;
    auto cPair = d->m_cRegions.emplace(d->m_nRegionIdCounter, RegionPointer(new Region(), &Region::deleteLater));
    auto cRegion = (*cPair.first).second;

    cRegion->id(d->m_nRegionIdCounter);
    cRegion->name("New Region " + QString::number(d->m_nRegionIdCounter));

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

    QJsonDocument cJSONDoc(cJSON);
    return  QTextCodec::codecForName("UTF-8")->toUnicode(cJSONDoc.toJson(eJsonFormat).data());
}


/**
 * Load the atlas from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Atlas::load(QJsonObject const & cJSON) {

    clear();

    Nameable::load(cJSON);

    if (cJSON.contains("regions") && cJSON["regions"].isArray()) {

        QJsonArray cJSONRegions = cJSON["regions"].toArray();
        for (auto &&cJSONRegion : cJSONRegions) {

            RegionPointer cRegion(new Region(), &Region::deleteLater);
            cRegion->load(cJSONRegion.toObject());

            auto nId = cRegion->id();
            d->m_cRegions.insert(std::make_pair(nId, cRegion));
            d->m_nRegionIdCounter = std::max<Region::id_t>(nId, d->m_nRegionIdCounter);
        }
    }

    modified(false);
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
    // TODO: work on descendants
    return false;
}


/**
 * Set the atlas and all descendants to a new modification state.
 *
 * @param   bModified       the new modification state
 */
void Atlas::modified(bool bModified) {
    Nameable::modified(bModified);
    // TODO: work on descendants
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
        QJsonObject jo;
        cRegion.second->save(jo);
        cJSONRegions.append(jo);
    }
    cJSON["regions"] = cJSONRegions;
}
