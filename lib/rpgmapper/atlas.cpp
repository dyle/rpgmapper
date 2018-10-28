/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;

// TODO: remove, when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


Atlas::Atlas(QObject * parent) : QObject{parent}, Nameable{} {
}


bool Atlas::applyJSON(QJsonObject json) {
    
    if (!Nameable::applyJSON(json)) {
        return false;
    }
    if (json.contains("regions")) {
        if (!json["regions"].isArray()) {
            return false;
        }
        if (!applyJsonRegionsArray(json["regions"].toArray())) {
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


void Atlas::init() {

/* TODO:
    
    impl->clear();
    setName(QObject::tr("New Atlas"));
    auto region = createRegion(QObject::tr("New Region 1"));
    region->createMap(QObject::tr("New Map 1"));
*/
}
