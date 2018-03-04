/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/command/set_map_numeral_axis.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapNumeralAxis::SetMapNumeralAxis(AtlasPointer & atlas, QString const & mapName, bool xAxis, QString newNumeral)
        : AtlasCommand{atlas}, mapName{mapName}, xAxis{xAxis}, newNumeral{newNumeral} {
}


void SetMapNumeralAxis::execute() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        if (xAxis) {
            oldNumeral = map->getNumeralXAxis()->getName();
            map->setNumeralXAxis(newNumeral);
        }
        else {
            oldNumeral = map->getNumeralYAxis()->getName();
            map->setNumeralYAxis(newNumeral);
        }
    }
}


QString SetMapNumeralAxis::getDescription() const {
    QString axis = xAxis ? "X" : "Y";
    return QString{"Set numeral of map %1 on %2-axis to %3"}.arg(mapName).arg(axis).arg(newNumeral);
}


void SetMapNumeralAxis::undo() {
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        if (xAxis) {
            map->setNumeralXAxis(oldNumeral);
        }
        else {
            map->setNumeralYAxis(oldNumeral);
        }
    }
}
