/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */





// ------------------------------------------------------------
// incs

#include <QPixmapCache>

// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/common_macros.h>
#include <rpgmapper/controller.hpp>
#include <iostream>
#include "structuraltreewidget.hpp"

using namespace rpgmapper::model;
using namespace rpgmapper::view;


// ------------------------------------------------------------
// decl


/**
 * Different types of item supported by this structural tree view.
 */
enum itemType {
    atlas,                  /**< The item is the atlas. */
    map,                    /**< the item is a map. */
    region                  /**< the item is a region. */
};


/**
 * The info on a item of the tree view.
 */
struct itemInfo {
    itemType eItemType = atlas;         /**< The type of the item. */
    mapid_t nMapId = 0;                 /**< The map id if the item is a map. */
    regionid_t nRegionId = 0;           /**< The region id if the item is a region. */
};


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


/**
 * Find a specific item with values in column 1 and column 2
 *
 * @param   cItem           the item to start with
 * @param   sColumn1        value of column 1
 * @param   sColumn2        value of column 2
 * @return  the item or nullptr if not found
 */
static QTreeWidgetItem * findItem(QTreeWidgetItem * cItem, QString const & sColumn1, QString const & sColumn2);


/**
 * Extracts the info of an tree widget item into a info struct.
 *
 * @param   cItem           the tree widget item
 * @param   cItemInfo       the extracted info of the atlas/map/region in the tree widget item
 * @return  true, if the info has been extracted
 */
static bool getItemInfo(QTreeWidgetItem * cItem, itemInfo & cItemInfo);


// ------------------------------------------------------------
// code


/**
 * Ctor
 *
 * @param   cParent     parent widget
 */
StructuralTreeWidget::StructuralTreeWidget(QWidget * cParent) : QTreeWidget{cParent} {

    connect(this, &QTreeWidget::currentItemChanged, this, &StructuralTreeWidget::changedCurrentItem);
    connect(this, &QTreeWidget::itemDoubleClicked, this, &StructuralTreeWidget::doubleClickedItem);

    connect(Controller::instance().atlas().data(), &Atlas::changedName,
            this, &StructuralTreeWidget::changedAtlasName);
    connect(Controller::instance().atlas().data(), &Atlas::changedMapName,
            this, &StructuralTreeWidget::changedMapName);
    connect(Controller::instance().atlas().data(), &Atlas::changedRegionName,
            this, &StructuralTreeWidget::changedRegionName);
    connect(Controller::instance().atlas().data(), &Atlas::deletedMap,
            this, &StructuralTreeWidget::deletedMap);
    connect(Controller::instance().atlas().data(), &Atlas::deletedRegion,
            this, &StructuralTreeWidget::deletedRegion);
    connect(Controller::instance().atlas().data(), &Atlas::newMap,
            this, &StructuralTreeWidget::newMap);
    connect(Controller::instance().atlas().data(), &Atlas::newRegion,
            this, &StructuralTreeWidget::newRegion);
}


/**
 * The atlas has changed.
 */
void StructuralTreeWidget::changedAtlasName() {
    auto cAtlasItem = topLevelItem(0);
    cAtlasItem->setText(0, Controller::instance().atlas()->name());
}


/**
 * The changed the selected item.
 *
 * @param   cCurrent        new selected item
 */
void StructuralTreeWidget::changedCurrentItem(QTreeWidgetItem * cCurrent) {

    itemInfo cItemInfo;
    if (!getItemInfo(cCurrent, cItemInfo)) {
        return;
    }

    switch (cItemInfo.eItemType) {

        case atlas:
            emit selectedAtlas();
            break;

        case map:
            Controller::instance().atlas()->setCurrentMap(cItemInfo.nMapId);
            emit selectedMap(cItemInfo.nMapId);
            break;

        case region:
            Controller::instance().atlas()->setCurrentRegion(cItemInfo.nRegionId);
            emit selectedRegion(cItemInfo.nRegionId);
            break;
    }
}


/**
 * A map changed its name.
 *
 * @param   nMapId          id of the map changed
 */
void StructuralTreeWidget::changedMapName(rpgmapper::model::mapid_t nMapId) {

    auto cMap = Controller::instance().atlas()->mapById(nMapId);
    if (cMap != nullptr) {
        auto cMapItem = findItem(topLevelItem(0), "map", QString::number(nMapId));
        if (cMapItem != nullptr) {
            cMapItem->setText(0, cMap->name());
        }
    }
}


/**
 * A region changed its name.
 *
 * @param   nRegionId       id of the region changed
 */
void StructuralTreeWidget::changedRegionName(rpgmapper::model::regionid_t nRegionId) {

    auto cRegion = Controller::instance().atlas()->regionById(nRegionId);
    if (cRegion != nullptr) {
        auto cRegionItem = findItem(topLevelItem(0), "region", QString::number(nRegionId));
        if (cRegionItem != nullptr) {
            cRegionItem->setText(0, cRegion->name());
        }
    }
}


/**
 * A map has been deleted.
 *
 * @param   nMapId      id of the map deleted
 */
void StructuralTreeWidget::deletedMap(rpgmapper::model::mapid_t nMapId) {

    auto cMapItem = findItem(topLevelItem(0), "map", QString::number(nMapId));
    if (cMapItem != nullptr) {
        topLevelItem(0)->removeChild(cMapItem);
        delete cMapItem;
    }
}


/**
 * A region has been deleted.
 *
 * @param nRegionId     id of the region deleted
 */
void StructuralTreeWidget::deletedRegion(rpgmapper::model::regionid_t nRegionId) {

    auto cRegionItem = findItem(topLevelItem(0), "region", QString::number(nRegionId));
    if (cRegionItem != nullptr) {
        topLevelItem(0)->removeChild(cRegionItem);
        delete cRegionItem;
    }
}


/**
 * The user double clicked an item.
 *
 * @param   cItem       the item double clicked
 * @param   nColumn     the column where she clicked
 */
void StructuralTreeWidget::doubleClickedItem(QTreeWidgetItem * cItem, UNUSED int nColumn) {

    itemInfo cItemInfo;
    if (!getItemInfo(cItem, cItemInfo)) {
        return;
    }

    switch (cItemInfo.eItemType) {

        case atlas:
            emit doubleClickedAtlas();
            break;

        case map:
            Controller::instance().atlas()->setCurrentMap(cItemInfo.nMapId);
            emit doubleClickedMap(cItemInfo.nMapId);
            break;

        case region:
            Controller::instance().atlas()->setCurrentRegion(cItemInfo.nRegionId);
            emit doubleClickedRegion(cItemInfo.nRegionId);
            break;
    }
}


/**
 * We have a new map.
 *
 * @param   nMapId      id of the new map
 */
void StructuralTreeWidget::newMap(rpgmapper::model::mapid_t nMapId) {

    resetStructure();

    auto cMapItem = findItem(topLevelItem(0), "map", QString::number(nMapId));
    if (cMapItem) {
        scrollToItem(cMapItem, QAbstractItemView::EnsureVisible);
        setCurrentItem(cMapItem);
    }
}


/**
 * We have a new region.
 *
 * @param nRegionId     id of the new region
 */
void StructuralTreeWidget::newRegion(rpgmapper::model::regionid_t nRegionId) {

    resetStructure();

    auto cRegionItem = findItem(topLevelItem(0), "region", QString::number(nRegionId));
    if (cRegionItem) {
        scrollToItem(cRegionItem, QAbstractItemView::EnsureVisible);
        setCurrentItem(cRegionItem);
    }
}


/**
 * Reset structure (builds Atlas structure anew)
 */
void StructuralTreeWidget::resetStructure() {
    clear();
    appendStructureAtlas(this);
    sortByColumn(3, Qt::AscendingOrder);
    setSortingEnabled(true);
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

    static QPixmap cPixmap;
    if (cPixmap.isNull()) {
        QPixmapCache::find("atlas", &cPixmap);
    }

    QStringList cStringList;
    cStringList << Controller::instance().atlas()->name() << "atlas" << "";

    auto cTWAtlasItem = new QTreeWidgetItem{cStringList};
    cTWAtlasItem->setIcon(0, cPixmap);
    cTWStructure->insertTopLevelItem(0, cTWAtlasItem);

    for (auto const & cRegion: Controller::instance().atlas()->regions()) {
        auto cTWRegion = appendStructureRegion(cTWAtlasItem, cRegion.second);
        cTWRegion->setExpanded(true);
    }

    cTWAtlasItem->setExpanded(true);
}


/**
 * Add a map structural tree view
 *
 * @param   cTIRegion       the QTreeWidgetItem holding the region item
 * @param   cMap            the map to add
 * @return  The QTreeWidgetItem created
 */
QTreeWidgetItem * appendStructureMap(QTreeWidgetItem * cTWRegion, MapPointer const & cMap) {

    static QPixmap cPixmap;
    if (cPixmap.isNull()) {
        QPixmapCache::find("map", &cPixmap);
    }

    QStringList cStringList;
    cStringList << cMap->name()
                << "map"
                << QString::number(cMap->id())
                << QString::number(cMap->orderValue());

    auto cTWMapItem = new QTreeWidgetItem{cTWRegion, cStringList};
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

    static QPixmap cPixmap;
    if (cPixmap.isNull()) {
        QPixmapCache::find("region", &cPixmap);
    }

    QStringList cStringList;
    cStringList << cRegion->name()
                << "region"
                << QString::number(cRegion->id())
                << QString::number(cRegion->orderValue());

    auto cTWRegionItem = new QTreeWidgetItem{cTWAtlas, cStringList};
    cTWRegionItem->setIcon(0, cPixmap);
    for (auto const & cMap: cRegion->maps()) {
        auto cTWMap = appendStructureMap(cTWRegionItem, cMap.second);
        cTWMap->setExpanded(true);
    }

    return cTWRegionItem;
}


/**
 * Find a specific item with values in column 1 and column 2
 *
 * @param   cItem           the item to start with
 * @param   sColumn1        value of column 1
 * @param   sColumn2        value of column 2
 * @return  the item or nullptr if not found
 */
QTreeWidgetItem * findItem(QTreeWidgetItem * cItem, QString const & sColumn1, QString const & sColumn2) {

    if (cItem == nullptr) {
        return nullptr;
    }
    if ((cItem->text(1) == sColumn1) && (cItem->text(2) == sColumn2)) {
        return cItem;
    }

    QTreeWidgetItem * res = nullptr;
    for (int i = 0; (i < cItem->childCount()) && (res == nullptr); ++i) {
        res = findItem(cItem->child(i), sColumn1, sColumn2);
    }

    return res;
}


/**
 * Extracts the info of an tree widget item into a info struct.
 *
 * @param   cItem           the tree widget item
 * @param   cItemInfo       the extracted info of the atlas/map/region in the tree widget item
 * @return  true, if the info has been extracted
 */
bool getItemInfo(QTreeWidgetItem * cItem, itemInfo & cItemInfo) {

    if (!cItem || (cItem->columnCount() < 2)){
        return false;
    }

    if (cItem->text(1) == "atlas") {
        cItemInfo.eItemType = atlas;
        return true;
    }

    if (cItem->columnCount() >= 3) {

        if (cItem->text(1) == "region") {
            cItemInfo.eItemType = region;
            cItemInfo.nRegionId = cItem->text(2).toInt();
            return true;
        }
        if (cItem->text(1) == "map") {
            cItemInfo.eItemType = map;
            cItemInfo.nMapId = cItem->text(2).toInt();
            return true;
        }
    }

    return false;
}
