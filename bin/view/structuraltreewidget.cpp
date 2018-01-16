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

#include <iostream>
#include <QPixmapCache>

// rpgmapper
#include <rpgmapper/atlas.hpp>
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
static QTreeWidgetItem * appendStructureMap(QTreeWidgetItem * cTWRegion, MapPointer const & cMap);


/**
 * Add a region structural tree view
 *
 * @param   cTIAtlas        the QTreeWidgetItem holding the atlas item
 * @param   cRegion         the region to add
 * @return  The QTreeWidgetItem created
 */
static QTreeWidgetItem * appendStructureRegion(QTreeWidgetItem * cTWAtlas, RegionPointer const & cRegion);


// ------------------------------------------------------------
// code


/**
 * Ctor
 *
 * @param   cParent     parent widget
 */
StructuralTreeWidget::StructuralTreeWidget(QWidget * cParent) : QTreeWidget(cParent) {
    connect(this, &QTreeWidget::currentItemChanged, this, &StructuralTreeWidget::changedCurrentItem);
}


/**
 * The changed the selected item.
 *
 * @param   cCurrent        new selected item
 */
void StructuralTreeWidget::changedCurrentItem(QTreeWidgetItem * cCurrent) {

    if (!cCurrent || (cCurrent->columnCount() < 2)){
        return;
    }
    if (cCurrent->text(1) == "atlas") {
        emit selectedAtlas();
    }

    if (cCurrent->columnCount() >= 3) {
        if (cCurrent->text(1) == "region") {
            emit selectedRegion(cCurrent->text(2).toInt());
        }
        if (cCurrent->text(1) == "map") {
            emit selectedMap(cCurrent->text(2).toInt());
        }
    }
}


/**
 * Reset structure (builds Atlas structure anew)
 */
void StructuralTreeWidget::resetStructure() {
    clear();
    appendStructureAtlas(this);
}


/**
 * Selects the first available Map in the structure.
 */
void StructuralTreeWidget::selectFirstMap() {

    auto cAtlasItem = topLevelItem(0);
    if (!cAtlasItem) {
        return;
    }

    for (int i = 0; i < cAtlasItem->childCount(); ++i) {

        auto cRegionItem = cAtlasItem->child(i);
        if (!cRegionItem) {
            continue;
        }

        for (int j = 0; j < cRegionItem->childCount(); ++j) {

            auto cMapItem = cRegionItem->child(j);
            if (!cMapItem) {
                continue;
            }

            if ((cMapItem->columnCount() >= 2) && (cMapItem->text(1) == "map")) {
                scrollToItem(cMapItem);
                setCurrentItem(cMapItem);
            }
        }
    }
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

    sl << Controller::instance().atlas()->name() << "atlas" << "";
    cTWItem = new QTreeWidgetItem(sl);
    QPixmapCache::find("atlas", &cPixmap);
    cTWItem->setIcon(0, cPixmap);
    cTWStructure->insertTopLevelItem(0, cTWItem);

    for (auto const & cRegion: Controller::instance().atlas()->regions()) {
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
QTreeWidgetItem * appendStructureMap(QTreeWidgetItem * cTWRegion, MapPointer const & cMap) {

    QPixmap cPixmap;
    QStringList sl;

    sl << cMap->name() << "map" << QString::number(cMap->id());
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
QTreeWidgetItem * appendStructureRegion(QTreeWidgetItem * cTWAtlas, RegionPointer const & cRegion) {

    QPixmap cPixmap;
    QStringList sl;

    sl << cRegion->name() << "region" << QString::number(cRegion->id());
    auto cTWRegionItem = new QTreeWidgetItem(cTWAtlas, sl);
    QPixmapCache::find("region", &cPixmap);
    cTWRegionItem->setIcon(0, cPixmap);

    for (auto const & cMap: cRegion->maps()) {
        auto cTWMap = appendStructureMap(cTWRegionItem, cMap.second);
        cTWMap->setExpanded(true);
    }
    return cTWRegionItem;
}
