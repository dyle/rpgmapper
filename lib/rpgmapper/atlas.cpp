/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/exception/invalid_region.hpp>
#include <rpgmapper/exception/invalid_regionname.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/atlas_name_validator.hpp>
#include <rpgmapper/region.hpp>

using namespace rpgmapper::model;

// TODO: remove, when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


Atlas::Atlas(QString name) : Nameable{std::move(name)} {
}


bool Atlas::applyJSON(QJsonObject const & json) {
    
    if (!Nameable::applyJSON(json)) {
        return false;
    }
    if (json.contains("regions")) {
        if (!json["regions"].isArray()) {
            return false;
        }
        if (!applyJSONRegionsArray(json["regions"].toArray())) {
            return false;
        }
    }
    return true;
}


bool Atlas::applyJSONRegionsArray(UNUSED QJsonArray const & jsonRegions) {

/* TODO:
    for (auto && jsonRegion : jsonRegions) {
        
        if (jsonRegion.toObject().contains("name") && jsonRegion.toObject()["name"].isString()) {
            auto region = createRegion(jsonRegion.toObject()["name"].toString());
            if (!region->applyJSON(jsonRegion.toObject())) {
                return false;
            }
        }
    }
*/
    return true;
}


void Atlas::addRegion(RegionPointer region) {
    
    if (!region->isValid()) {
        throw exception::invalid_region{};
    }
    if (regions.find(region->getName()) != regions.end()) {
        throw exception::invalid_region{};
    }
    
    auto regionName = region->getName();
    this->regions[regionName] = region;
    connect(region.data(), &Nameable::nameChanged, this, &Atlas::regionNameChanged);
    // TODO: add region connector: delete, name change
    emit regionAdded(regionName);
}


QJsonObject Atlas::getJSON() const {
    
    auto json = Nameable::getJSON();
    
    
    /* TODO:
    QJsonArray jsonRegions;
    std::for_each(std::begin(regions),
                  std::end(regions),
                  [&] (auto const & pair) { jsonRegions.append(pair.second->getJSON(content)); });
    json["regions"] = jsonRegions;
    */
    
    return json;
}


RegionPointer Atlas::getRegion(QString name) {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        throw exception::invalid_regionname{};
    }
    return (*iter).second;
}


RegionPointer const Atlas::getRegion(QString name) const {
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        throw exception::invalid_regionname{};
    }
    return (*iter).second;
}


void Atlas::regionNameChanged(QString oldName, QString newName) {
    
    auto iterOld = regions.find(oldName);
    if (iterOld == regions.end()) {
        return;
    }
    auto iterNew = regions.find(newName);
    if (iterNew != regions.end()) {
        throw exception::invalid_regionname{};
    }
    
    auto region = (*iterOld).second;
    regions.erase(iterOld);
    regions.emplace(newName, region);
}


QSharedPointer<Atlas> const & Atlas::null() {
    static QSharedPointer<Atlas> nullAtlas{new InvalidAtlas};
    return nullAtlas;
}


void Atlas::removeRegion(QString name) {
    
    auto iter = regions.find(name);
    if (iter == regions.end()) {
        throw exception::invalid_regionname{};
    }

    auto region = (*iter).second;
    disconnect(region.data(), &Nameable::nameChanged, this, &Atlas::regionNameChanged);
    regions.erase(iter);
    emit regionRemoved(name);
}
