/*
 * structuraltreewidget.cpp
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

#include <QPixmapCache>

// rpgmapper
#include <rpgmapper/controller.hpp>
#include "structuraltreewidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl


/**
 * Add the atlas to the structural tree view
 *
 * @param   cTWStructure        the QTreeWidget structural widget
 */
static void appendStructureAtlas(StructuralTreeWidget * cTWStructure);


/**
 * Add a map structural tree view
 *
 * @param   cTIRegion       the QTreeWidgetItem holding the region item
 * @param   cMap            the map to add
 * @return  The QTreeWidgetItem created
 */
static QTreeWidgetItem * appendStructureMap(QTreeWidgetItem * cTWRegion, Map const & cMap);


/**
 * Add a region structural tree view
 *
 * @param   cTIAtlas        the QTreeWidgetItem holding the atlas item
 * @param   cRegion         the region to add
 * @return  The QTreeWidgetItem created
 */
static QTreeWidgetItem * appendStructureRegion(QTreeWidgetItem * cTWAtlas, Region const & cRegion);


// ------------------------------------------------------------
// code


/**
 * Ctor
 *
 * @param   cParent     parent widget
 */
StructuralTreeWidget::StructuralTreeWidget(QWidget * cParent) : QTreeWidget(cParent) {

}


/**
 * Reset structure (builds Atlas structure anew)
 */
void StructuralTreeWidget::resetStructure() {
    clear();
    appendStructureAtlas(this);
}


/**
 * Add the atlas to the structural tree view
 *
 * @param   cTWStructure        the QTreeWidget structural widget
 */
void appendStructureAtlas(StructuralTreeWidget * cTWStructure) {

    QTreeWidgetItem * cTWItem = nullptr;
    QPixmap cPixmap;
    QStringList sl;

    sl << Controller::instance().atlas().name() << "atlas" << "";
    cTWItem = new QTreeWidgetItem(sl);
    QPixmapCache::find("atlas", &cPixmap);
    cTWItem->setIcon(0, cPixmap);
    cTWStructure->insertTopLevelItem(0, cTWItem);

    for (auto const & cRegion: Controller::instance().atlas().regions()) {
        auto cTWRegion = appendStructureRegion(cTWItem, cRegion.second);
        cTWRegion->setExpanded(true);
    }

    cTWItem->setExpanded(true);
}


/**
 * Add a map structural tree view
 *
 * @param   cTIRegion       the QTreeWidgetItem holding the region item
 * @param   cMap            the map to add
 * @return  The QTreeWidgetItem created
 */
QTreeWidgetItem * appendStructureMap(QTreeWidgetItem * cTWRegion, Map const & cMap) {

    QPixmap cPixmap;
    QStringList sl;

    sl << cMap.name() << "map" << QString::number(cMap.id());
    auto cTWMapItem = new QTreeWidgetItem(cTWRegion, sl);
    QPixmapCache::find("map", &cPixmap);
    cTWMapItem->setIcon(0, cPixmap);

    return cTWMapItem;
}


/**
 * Add a region structural tree view
 *
 * @param   cTIAtlas        the QTreeWidgetItem holding the atlas item
 * @param   cRegion         the region to add
 * @return  The QTreeWidgetItem created
 */
QTreeWidgetItem * appendStructureRegion(QTreeWidgetItem * cTWAtlas, Region const & cRegion) {

    QPixmap cPixmap;
    QStringList sl;

    sl << cRegion.name() << "region" << QString::number(cRegion.id());
    auto cTWRegionItem = new QTreeWidgetItem(cTWAtlas, sl);
    QPixmapCache::find("region", &cPixmap);
    cTWRegionItem->setIcon(0, cPixmap);

    for (auto const & cMap: cRegion.maps()) {
        auto cTWMap = appendStructureMap(cTWRegionItem, cMap.second);
        cTWMap->setExpanded(true);
    }
    return cTWRegionItem;
}
