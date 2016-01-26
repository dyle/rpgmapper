/*
 * atlas.cpp
 *
 * A RPG atlas
 * 
 * Copyright (C) 2015, 2016 Oliver Maurhart, <dyle@dyle.org>
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
atlas::atlas(QObject * cParent, QString const & sName, QString const & sDescription) 
    : QObject(cParent), m_sName(sName), m_sDescription(sDescription), m_bUnsaved(false) {
   
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(deleteLater()));

    add_map(rpg::map_ptr(new rpg::map()));
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
 * @param   sGroup      the map group to add the map to
 */
void atlas::add_map(rpg::map_ptr cMap, QString sGroup) {

    if (!cMap) throw std::invalid_argument("atlas refuses to add null map");

    // do not add twice
    auto cMapSet = m_cMaps.map_set();
    if (cMapSet.find(cMap) != cMapSet.end()) {
        throw std::invalid_argument("atlas already contains map");
    }

    m_cMaps[sGroup].insert(cMap);
    cMap->setParent(this);

    connect(cMap.get(), SIGNAL(changed(rpg::map const *)), SLOT(map_changed(rpg::map const *)));

    m_bUnsaved = true;
    emit map_added(sGroup, cMap.get());
    emit modified();
}


/**
 * delete a map from the atlas
 *
 * @param   sName       name of the map to delete
 */
void atlas::del_map(QString & sName) {

    rpg::map_ptr cMap = m_cMaps.remove_map(sName);
    if (cMap == nullptr) return;

    m_bUnsaved = true;
    emit modified();
}


/**
 * a map has changed
 *
 * @param   cMap        the map changed
 */
void atlas::map_changed(UNUSED rpg::map const * cMap) {
    m_bUnsaved = true;
    emit modified();
}


/**
 * set the description of the atlas
 * 
 * @param   sDescription        the new description of the atlas
 */
void atlas::set_description(QString const & sDescription) { 
    if (sDescription == m_sDescription) return;
    m_sDescription = sDescription; 
    m_bUnsaved = true; 
    emit modified(); 
}


/**
 * set a new filename on disk
 *
 * @param   sFileName       the new filename on disk
 */
void atlas::set_filename(QString const & sFileName) {
    if (sFileName == m_sFileName) return;
    m_sFileName = m_sFileName;
    m_bUnsaved = true;
    emit modified();
}


/**
 * set the atlas image
 *
 * @param   cImage the new atlas image
 */
void atlas::set_image(QImage & cImage) { 
    m_cImage = cImage; 
    emit modified(); 
}


