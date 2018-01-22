/*
 * changeable.cpp
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
#include <rpgmapper/changeable.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Ctor
 *
 * @param   cParent     parent object
 */
Changeable::Changeable(QObject * cParent) : QObject{cParent}, m_bModified{false} {
}


/**
 * State if the object instance data has changed.
 *
 * This will also check any of the object's children.
 *
 * @return  true if the object instance data and any of its children has changed
 */
bool Changeable::modified() const {
    return m_bModified;
}


/**
 * Set the object instance data changed flag.
 *
 * The new flag is also applied to any of the object's children.
 *
 * @param   bModified       the new object instance data changed flag
 */
void Changeable::modified(bool bModified) {
    m_bModified = bModified;
    emit changed();
}
