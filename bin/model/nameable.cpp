/*
 * nameable.cpp
 *
 * A nameable object knows its name
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
#include "nameable.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * ctor
 */
Nameable::Nameable() : Changeable() {
}


/**
 * dtor
 */
Nameable::~Nameable() {
}


/**
 * Get the name.
 *
 * @return  the name
 */
std::string const & Nameable::name() const {
    return m_sName;
}


/**
 * Set the name.
 *
 * @param   sName       the new name
 */
void Nameable::name(std::string sName) {
    if (m_sName != sName) {
        m_sName = sName;
        changed(true);
    }
}
