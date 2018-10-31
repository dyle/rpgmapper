/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_atlasname.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/atlas_name_validator.hpp>

using namespace rpgmapper::model;

// TODO: remove, when done
#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


bool Atlas::applyJSON(QJsonObject json) {
    
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


QSharedPointer<Atlas> const & Atlas::null() {
    static QSharedPointer<Atlas> nullAtlas{new InvalidAtlas};
    return nullAtlas;
}


void Atlas::setName(QString name) {
    
    if (getName() == name) {
        return;
    }
    if (!AtlasNameValidator::isValid(name)) {
        throw rpgmapper::model::exception::invalid_atlasname();
    }
    
    Nameable::setName(name);
}
