/*
 * field.cpp
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

// rpgmapper
#include <rpgmapper/common_macros.h>
#include <rpgmapper/field.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Load a tile from json.
 *
 * @param   cJSON       the json instance to load from
 */
Field rpgmapper::model::loadFromJson(UNUSED QJsonObject const & cJSON) {

    Field cTile{{0, 0}, {}};

    // TODO
//    if (cJSON.contains("position") && cJSON["position"].isObject()) {
//        auto cJSONPosition = cJSON["position"].toObject();
//        if (cJSONPosition.contains("x") && cJSONPosition["x"].isDouble()) {
//            cTile.cPosition.setX(cJSONPosition["x"].toInt());
//        }
//        if (cJSONPosition.contains("y") && cJSONPosition["y"].isDouble()) {
//            cTile.cPosition.setY(cJSONPosition["y"].toInt());
//        }
//    }
//
//    if (cJSON.contains("attributes") && cJSON["attributes"].isArray()) {
//        auto cJSONAttributes = cJSON["attributes"].toArray();
//        for (auto && iter : cJSONAttributes) {
//
//            QString sName;
//            QString sValue;
//            auto cJSONAttribute = iter.toObject();
//            if (cJSONAttribute.contains("name") && cJSONAttribute["name"].isString()) {
//                sName = cJSONAttribute["name"].toString();
//            }
//            if (cJSONAttribute.contains("value") && cJSONAttribute["value"].isString()) {
//                sValue = cJSONAttribute["value"].toString();
//            }
//            cTile.cAttributes[sName] = sValue;
//        }
//    }

    return cTile;
}


/**
 * Save a tile to json.
 *
 * @param   cField       the tile to save
 */
QJsonObject rpgmapper::model::saveToJson(UNUSED Field const & cField) {

    QJsonObject cJSON;

    // TODO
//    QJsonObject cJSONPosition;
//    cJSONPosition["x"] = cField.cPosition.x();
//    cJSONPosition["y"] = cField.cPosition.y();
//    cJSON["position"] = cJSONPosition;
//
//    QJsonArray cJSONAttributes;
//    for (auto const & cPair : cField.cAttributes) {
//        QJsonObject cJSONAttribute;
//        cJSONAttribute["name"] = cPair.first;
//        cJSONAttribute["value"] = cPair.second;
//        cJSONAttributes.append(cJSONAttribute);
//    }
//    cJSON["attributes"] = cJSONAttributes;

    return cJSON;
}
