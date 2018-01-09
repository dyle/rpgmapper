/*
 * changeable.cpp
 *
 * A changeable object knows, if its data has been changed.
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

 // rpgmappger
 #include "common_macros.h"
 #include "changeable.hpp"

 using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * ctor
 */
Changeable::Changeable() : m_bChanged(false) {
}


/**
 * dtor
 */
Changeable::~Changeable() {
}


/**
 * state if the object instance data has changed
 *
 * @return  true if the object instance  data has changed
 */
bool Changeable::changed() const {
    return m_bChanged;
}


/**
 * set the object instance  data changed flag
 *
 * @param   bChanged        the new object instance  data changed flag
 */
void Changeable::changed(bool bChanged) {
    m_bChanged = bChanged;
}
