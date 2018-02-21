/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/coordinate_system.hpp>
#include <rpgmapper/field.hpp>

using namespace rpgmapper::model;


Field::Field(int x, int y) : Field{QPoint(x, y)} {
}


Field::Field(QPoint const & position) : position(position) {
}


int Field::getIndex(int x, int y) {
    return y * CoordinateSystem::getMaximumSize().width() + x;
}


Field const & Field::nullField() {
    static InvalidField nullField;
    return nullField;
}
