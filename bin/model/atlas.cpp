/*
 * atlas.cpp
 *
 * A RPG atlas
 * 
 * Copyright (C) 2015, Oliver Maurhart, <dyle@dyle.org>
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

// Qt
#include <QApplication>

// rpgmappger
#include "common_macros.h"
#include "atlas.h"

using namespace rpg;


// ------------------------------------------------------------
// code


/**
 * ctor
 *
 * @param   cParent         parent object
 * @param   sName           name of atlas
 * @param   sDescription    description of atlas
 */
atlas::atlas(QObject * cParent, std::string const & sName, std::string const & sDescription) 
    : QObject(cParent), m_sName(sName), m_sDescription(sDescription), m_bUnsaved(false) {
   
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(deleteLater()));

    // insert empty new default map
    add_map(new rpg::map());
    m_bUnsaved = false;
}


/**
 * dtor
 */
atlas::~atlas() {
}


/**
 * add a map to the atlas
 *
 * @param   cMap        the map to add
 */
void atlas::add_map(rpg::map * cMap) {

    if (!cMap) throw std::invalid_argument("atlas refuses to add null map");

    // do not add twice
    auto cMapSet = m_cMaps.map_set();
    if (cMapSet.find(cMap) != cMapSet.end()) {
        throw std::invalid_argument("atlas already contains map");
    }

    // real insert
    std::string sDefaultGroup = "<default>";
    m_cMaps[sDefaultGroup].insert(cMap);
    cMap->setParent(this);

    // setup connectors
    connect(cMap, SIGNAL(changed(rpg::map*)), SLOT(map_changed(rpg::map*)));
    connect(cMap, SIGNAL(destroyed(QObject*)), SLOT(map_destroyed(QObject*)));

    m_bUnsaved = true;
    emit map_added(sDefaultGroup, cMap);
    emit modified();
}


/**
 * delete a map from the atlas
 *
 * @param   sName       name of the map to delete
 */
void atlas::del_map(std::string & sName) {

    rpg::map * cMap = m_cMaps.find_map(sName);
    if (cMap == nullptr) return;

    delete cMap;
    
    m_bUnsaved = true;
    emit modified();
}


/**
 * a map has changed
 *
 * @param   cMap        the map changed
 */
void atlas::map_changed(UNUSED rpg::map * cMap) {
    m_bUnsaved = true;
    emit modified();
}


/**
 * a map has been destroyed
 *
 * @param   cMap        the map destroyed
 */
void atlas::map_destroyed(QObject * cMap) {

    if (m_cMaps.erase_map(dynamic_cast<rpg::map *>(cMap)->name())) {
        m_bUnsaved = true;
        emit modified();
    }
}

