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
#include <rpgmapper/field.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Load a tile from json.
 *
 * @param   cJSON       the json instance to load from
 */
Field rpgmapper::model::loadFromJson(QJsonObject const & cJSON) {

    Field cField{{0, 0}, {}};

    if (cJSON.contains("position") && cJSON["position"].isObject()) {
        auto cJSONPosition = cJSON["position"].toObject();
        if (cJSONPosition.contains("x") && cJSONPosition["x"].isDouble()) {
            cField.cPosition.setX(cJSONPosition["x"].toInt());
        }
        if (cJSONPosition.contains("y") && cJSONPosition["y"].isDouble()) {
            cField.cPosition.setY(cJSONPosition["y"].toInt());
        }
    }

    if (cJSON.contains("tiles") && cJSON["tiles"].isArray()) {

        auto cJSONTiles = cJSON["tiles"].toArray();
        for (auto && cJSONTile : cJSONTiles) {

            Tile cTile;
            for (auto && iter : cJSONTile.toArray()) {

                QString sName;
                QString sValue;
                auto cJSONAttribute = iter.toObject();
                if (cJSONAttribute.contains("setName") && cJSONAttribute["setName"].isString()) {
                    sName = cJSONAttribute["setName"].toString();
                }
                if (cJSONAttribute.contains("value") && cJSONAttribute["value"].isString()) {
                    sValue = cJSONAttribute["value"].toString();
                }
                cTile[sName] = sValue;
            }
            cField.cTiles.push_back(cTile);
        }
    }

    return cField;
}


/**
 * Save a tile to json.
 *
 * @param   cField       the tile to save
 */
QJsonObject rpgmapper::model::saveToJson(Field const & cField) {

    QJsonObject cJSON;

    QJsonObject cJSONPosition;
    cJSONPosition["x"] = cField.cPosition.x();
    cJSONPosition["y"] = cField.cPosition.y();
    cJSON["position"] = cJSONPosition;

    QJsonArray cJSONTiles;
    for (auto const & cTile : cField.cTiles) {

        QJsonArray cJSONAttributes;
        for (auto const & cPair : cTile) {
            QJsonObject cJSONAttribute;
            cJSONAttribute["setName"] = cPair.first;
            cJSONAttribute["value"] = cPair.second;
            cJSONAttributes.append(cJSONAttribute);
        }
        cJSONTiles.append(cJSONAttributes);
    }
    cJSON["tiles"] = cJSONTiles;

    return cJSON;
}
