/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/command/set_map_numeral_axis.hpp>
#include <rpgmapper/exception/invalid_map.hpp>
#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


SetMapNumeralAxis::SetMapNumeralAxis(rpgmapper::model::Map * map, bool xAxis, QString newNumeral)
        : map{map},
          xAxis{xAxis},
          newNumeral{std::move(newNumeral)} {
    
    if (!map || !map->isValid()) {
        throw rpgmapper::model::exception::invalid_map{};
    }
}


void SetMapNumeralAxis::execute() {
    
    if (xAxis) {
        oldNumeral = map->getCoordinateSystem()->getNumeralXAxis()->getName();
        map->getCoordinateSystem()->setNumeralXAxis(newNumeral);
    }
    else {
        oldNumeral = map->getCoordinateSystem()->getNumeralYAxis()->getName();
        map->getCoordinateSystem()->setNumeralYAxis(newNumeral);
    }
}


QString SetMapNumeralAxis::getDescription() const {
    auto mapName = map->getName();
    QString axis = xAxis ? "X" : "Y";
    return QString{"Set numeral of map %1 on %2-axis to %3"}.arg(mapName).arg(axis).arg(newNumeral);
}


void SetMapNumeralAxis::undo() {
    if (xAxis) {
        map->getCoordinateSystem()->setNumeralXAxis(oldNumeral);
    }
    else {
        map->getCoordinateSystem()->setNumeralYAxis(oldNumeral);
    }
}
