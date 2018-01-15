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
 * ctor
 */
Atlas::Atlas() : Nameable() {
    d = std::make_shared<Atlas::Atlas_data>();
    name("New Atlas");
    createRegion();
}


/**
 * check if the atlas or any aggregated objects changed.
 *
 * @return  true if the atlas or any dependent object changed.
 */
bool Atlas::changedAccumulated() const {

    if (changed()) {
        return true;
    }

    for (auto const & cRegion: d->m_cRegions) {
        if (cRegion.second.changedAccumulated()) {
            return true;
        }
    }

    return false;
}


/**
 * set the change flag of the atlas and any dependent objects
 *
 * @param   bChanged        the new changed information
 */
void Atlas::changedAccumulated(bool bChanged) {

    changed(bChanged);
    for (auto & cRegion: d->m_cRegions) {
        cRegion.second.changedAccumulated(bChanged);
    }
}


/**
 * reset the atlas to empty state
 */
void Atlas::clear() {
    name("");
    d->m_cRegions.clear();
    d->m_nRegionIdCounter = 0;
    changed(true);
}


/**
 * Creates a new region to this atlas
 *
 * @return  a reference to the new region
 */
Region & Atlas::createRegion() {

    d->m_nRegionIdCounter += 1;
    d->m_cRegions.emplace(d->m_nRegionIdCounter, Region());

    Region & cRegion = d->m_cRegions[d->m_nRegionIdCounter];
    cRegion.id(d->m_nRegionIdCounter);
    cRegion.name("New Region " + QString::number(d->m_nRegionIdCounter));

    return cRegion;
}


/**
 * create a json string form this Atlas
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
 * load the atlas from json
 *
 * @param   cJSON       the json instance to load from
 */
void Atlas::load(QJsonObject const & cJSON) {

    clear();

    Nameable::load(cJSON);

    if (cJSON.contains("regions") && cJSON["regions"].isArray()) {

        QJsonArray cJSONRegions = cJSON["regions"].toArray();
        for (auto &&cJSONRegion : cJSONRegions) {

            Region cRegion;
            cRegion.load(cJSONRegion.toObject());

            auto nId = cRegion.id();
            d->m_cRegions.insert(std::make_pair(nId, std::move(cRegion)));
            d->m_nRegionIdCounter = std::max<Region::id_t>(nId, d->m_nRegionIdCounter);
        }
    }

    changedAccumulated(false);
}


/**
 * return all the regions managed by this atlas
 *
 * @return  all regions of this atlas
 */
Regions const & Atlas::regions() const {
    return d->m_cRegions;
}


/**
 * save the atlas to json
 *
 * @param   cJSON       the json instance to save to
 */
void Atlas::save(QJsonObject & cJSON) const {

    Nameable::save(cJSON);

    QJsonArray cJSONRegions;
    for (auto const & cRegion: d->m_cRegions) {
        QJsonObject jo;
        cRegion.second.save(jo);
        cJSONRegions.append(jo);
    }
    cJSON["regions"] = cJSONRegions;
}
