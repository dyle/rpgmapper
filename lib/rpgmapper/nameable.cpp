/*
 * nameable.cpp
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
#include <rpgmapper/nameable.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Ctor.
 *
 * @param   cParent     parent object
 */
Nameable::Nameable(QObject * cParent) : Changeable{cParent} {
}


/**
 * Load the name from json.
 *
 * @param   cJSON       the json instance to load from
 */
void Nameable::load(QJsonObject const & cJSON) {
    if (cJSON.contains("setName") && cJSON["setName"].isString()) {
        setName(cJSON["setName"].toString());
    }
}


/**
 * Get the name.
 *
 * @return  the name
 */
QString const & Nameable::name() const {
    return m_sName;
}


/**
 * Save the name to json.
 *
 * @param   cJSON       the json instance to save to
 */
void Nameable::save(QJsonObject & cJSON) const {
    cJSON["setName"] = name();
}


/**
 * Set the name.
 *
 * @param   sName       the new name
 */
void Nameable::setName(QString sName) {
    if (m_sName != sName) {
        m_sName = sName;
        setModified(true);
        emit changedName();
    }
}
