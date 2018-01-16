/*
 * controller.cpp
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
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {

/**
 * Internal data of an Atlas object.
 */
class Controller::Controller_data {

public:

    Controller_data() = default;


    AtlasPointer m_cAtlas;              /**< the atlas managed by this controller */
};

}
}

// ------------------------------------------------------------
// code


/**
 * Ctor.
 */
Controller::Controller() {
    d = std::make_shared<Controller::Controller_data>();
    d->m_cAtlas = AtlasPointer(new Atlas);
}


/**
 * Get the current atlas
 *
 * @return  the current atlas instance
 */
AtlasPointer & Controller::atlas() {
    return d->m_cAtlas;
}


/**
 * Get the singleton controller instance.
 *
 * @return  the singleton controller instance of rpgmapper.
 */
Controller & Controller::instance() {
    static Controller cController;
    return cController;
}
