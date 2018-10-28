#include <utility>

/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_numeral_axis.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapNumeralAxis::SetMapNumeralAxis(QString mapName, bool xAxis, QString newNumeral)
        : mapName{std::move(mapName)}, xAxis{xAxis}, newNumeral{std::move(newNumeral)} {
}


void SetMapNumeralAxis::execute() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        if (xAxis) {
            oldNumeral = map->getCoordinateSystem()->getNumeralXAxis()->getName();
            map->getCoordinateSystem()->setNumeralXAxis(newNumeral);
        }
        else {
            oldNumeral = map->getCoordinateSystem()->getNumeralYAxis()->getName();
            map->getCoordinateSystem()->setNumeralYAxis(newNumeral);
        }
    }
*/
}


QString SetMapNumeralAxis::getDescription() const {
    QString axis = xAxis ? "X" : "Y";
    return QString{"Set numeral of map %1 on %2-axis to %3"}.arg(mapName).arg(axis).arg(newNumeral);
}


void SetMapNumeralAxis::undo() {
/**
 * TODO
 *
    auto atlas = getAtlas();
    auto map = atlas->findMap(mapName);
    if (map->isValid()) {
        if (xAxis) {
            map->getCoordinateSystem()->setNumeralXAxis(oldNumeral);
        }
        else {
            map->getCoordinateSystem()->setNumeralYAxis(oldNumeral);
        }
    }
*/
}
