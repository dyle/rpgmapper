/*
 * map.cpp
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

// rpgmapper
#include <rpgmapper/model/map.hpp>


using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {


/**
 * Internal data of a Map object.
 */
class Map::Map_data {

public:

    Map_data() {
    }

};


}
}


// ------------------------------------------------------------
// code


/**
 * ctor
 */
Map::Map() : Nameable() {
    d = std::shared_ptr<Map::Map_data>(new Map::Map_data());
}


/**
 * dtor
 */
Map::~Map() {
}


/**
 * make a deep copy of this Map
 *
 * @return  a new deep copied instance
 */
Map Map::clone() const {
    Map m;
    m.name(name());
    return m;
}
