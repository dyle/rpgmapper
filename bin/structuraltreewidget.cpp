/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QPixmapCache>

#include "mainwindow.hpp"
#include "structuraltreewidget.hpp"

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

using namespace rpgmapper::model;
using namespace rpgmapper::view;


StructuralTreeWidget::StructuralTreeWidget(QWidget * parent) : QTreeWidget{parent} {
    connect(this, &QTreeWidget::currentItemChanged, this, &StructuralTreeWidget::changedCurrentItem);
    connect(this, &QTreeWidget::itemDoubleClicked, this, &StructuralTreeWidget::doubleClickedItem);
}


void StructuralTreeWidget::addAtlas() {

    static QPixmap atlasPixmap;
    if (atlasPixmap.isNull()) {
        QPixmapCache::find("atlas", &atlasPixmap);
    }

    QStringList columns;
    columns << selection->getAtlas()->getName() << "atlas" << "0";

    auto atlasItem = new QTreeWidgetItem{columns};
    atlasItem->setIcon(0, atlasPixmap);
    insertTopLevelItem(0, atlasItem);

    for (auto const & cRegion: selection->getAtlas()->getRegions()) {
        auto cTWRegion = addRegion(atlasItem, cRegion.second);
        cTWRegion->setExpanded(true);
    }

    atlasItem->setExpanded(true);
}


QTreeWidgetItem * StructuralTreeWidget::addMap(QTreeWidgetItem * regionItem, MapPointer const & map) {

    static QPixmap mapPixmap;
    if (mapPixmap.isNull()) {
        QPixmapCache::find("map", &mapPixmap);
    }

    QStringList columns;
    columns << map->getName() << "map" << "0";
    auto mapItem = new QTreeWidgetItem{regionItem, columns};
    mapItem->setIcon(0, mapPixmap);

    return mapItem;
}


QTreeWidgetItem * StructuralTreeWidget::addRegion(QTreeWidgetItem * atlasItem, RegionPointer const & region) {

    static QPixmap regionPixmap;
    if (regionPixmap.isNull()) {
        QPixmapCache::find("region", &regionPixmap);
    }

    QStringList columns;
    columns << region->getName() << "region" << "0";
    auto regionItem = new QTreeWidgetItem{atlasItem, columns};
    regionItem->setIcon(0, regionPixmap);

    for (auto const & cMap: region->getMaps()) {
        auto mapItem = addMap(regionItem, cMap.second);
        mapItem->setExpanded(true);
    }

    return regionItem;
}


void StructuralTreeWidget::changedAtlasName(QString const & name) {
    auto item = topLevelItem(0);
    item->setText(0, name);
}


void StructuralTreeWidget::changedCurrentItem(QTreeWidgetItem * current) {

    auto itemInfo = getItemInfo(current);
    if (!itemInfo.valid) {
        return;
    }

    switch (itemInfo.itemType) {

        case ItemType::atlas:
            emit selectedAtlas();
            break;

        case ItemType::map:
            selection->selectMap(itemInfo.name);
            emit selectedMap(itemInfo.name);
            break;

        case ItemType::region:
            selection->selectRegion(itemInfo.name);
            emit selectedRegion(itemInfo.name);
            break;
    }
}


void StructuralTreeWidget::changedMapName(QString const & nameBefore, QString const & nameAfter) {

    auto item = searchItem(ItemType::map, nameBefore);
    if (item == nullptr) {
        return;
    }
    item->setText(0, nameAfter);
}


void StructuralTreeWidget::changedRegionName(QString const & nameBefore, QString const & nameAfter) {

    auto item = searchItem(ItemType::region, nameBefore);
    if (item == nullptr) {
        return;
    }
    item->setText(0, nameAfter);
}


void StructuralTreeWidget::connectSelectionSignals() {

    if (selection == nullptr) {
        return;
    }

    connect(selection.data(), &Selection::newAtlas, this, &StructuralTreeWidget::resetStructure);

    connect(selection->getAtlas().data(), &Atlas::nameChanged,
            this, &StructuralTreeWidget::changedAtlasName);
    connect(selection->getAtlas().data(), &Atlas::mapNameChanged,
            this, &StructuralTreeWidget::changedMapName);
    connect(selection->getAtlas().data(), &Atlas::regionNameChanged,
            this, &StructuralTreeWidget::changedRegionName);
    connect(selection->getAtlas().data(), &Atlas::mapRemoved,
            this, &StructuralTreeWidget::removedMap);
    connect(selection->getAtlas().data(), &Atlas::regionRemoved,
            this, &StructuralTreeWidget::removedRegion);
    connect(selection->getAtlas().data(), &Atlas::mapCreated,
            this, &StructuralTreeWidget::createdMap);
    connect(selection->getAtlas().data(), &Atlas::regionCreated,
            this, &StructuralTreeWidget::createdRegion);
}


void StructuralTreeWidget::createdMap(QString const &name) {

    auto map = selection->getAtlas()->findMap(name);
    if (!map->isValid()) {
        return;
    }

    auto parentItem = searchItem(ItemType::region, map->getRegionName());
    if (parentItem == nullptr) {
        return;
    }

    auto mapName = addMap(parentItem, map);
    if (mapName) {
        scrollToItem(mapName, QAbstractItemView::EnsureVisible);
        setCurrentItem(mapName);
    }
}


void StructuralTreeWidget::createdRegion(QString const &name) {

    auto region = selection->getAtlas()->findRegion(name);
    if (!region->isValid()) {
        return;
    }

    auto parentItem = searchItem(ItemType::atlas, QString::null);
    if (parentItem == nullptr) {
        return;
    }

    auto regionItem = addRegion(parentItem, region);
    if (regionItem) {
        scrollToItem(regionItem, QAbstractItemView::EnsureVisible);
        setCurrentItem(regionItem);
    }
}


void StructuralTreeWidget::doubleClickedItem(QTreeWidgetItem * item, UNUSED int column) {

    auto itemInfo = getItemInfo(item);
    if (!itemInfo.valid) {
        return;
    }

    switch (itemInfo.itemType) {

        case ItemType::atlas:
            emit doubleClickedAtlas();
            break;

        case ItemType::map:
            selection->selectMap(itemInfo.name);
            emit doubleClickedMap(itemInfo.name);
            break;

        case ItemType::region:
            selection->selectRegion(itemInfo.name);
            emit doubleClickedRegion(itemInfo.name);
            break;
    }
}


StructuralTreeWidget::ItemInfo StructuralTreeWidget::getItemInfo(QTreeWidgetItem * item) const {

    ItemInfo itemInfo{ItemType::atlas, QString::null, false};

    if ((item != nullptr) && (item->columnCount() > 1)) {

        if (item->text(1) == "atlas") {
            itemInfo = { ItemType::atlas, item->text(0), true};
        }
        else
        if (item->text(1) == "region") {
            itemInfo = { ItemType::region, item->text(0), true};
        }
        else
        if (item->text(1) == "map") {
            itemInfo = { ItemType::map, item->text(0), true};
        }
    }

    return itemInfo;
}


void StructuralTreeWidget::removedMap(QString const &name) {

    auto item = searchItem(ItemType::map, name);
    if (item == nullptr) {
        return;
    }
    topLevelItem(0)->removeChild(item);
    delete item;
}


void StructuralTreeWidget::removedRegion(QString const &name) {

    auto item = searchItem(ItemType::region, name);
    if (item == nullptr) {
        return;
    }
    topLevelItem(0)->removeChild(item);
    delete item;
}


void StructuralTreeWidget::resetStructure() {
    clear();
    addAtlas();
    sortByColumn(1, Qt::AscendingOrder);
    setSortingEnabled(true);
}


QTreeWidgetItem * StructuralTreeWidget::searchItem(ItemType type, QString const & name) const {
    return searchItem(nullptr, type, name);
}


QTreeWidgetItem * StructuralTreeWidget::searchItem(QTreeWidgetItem * parentItem,
                                                   ItemType type,
                                                   QString const & name) const {

    if (type == ItemType::atlas) {
        return topLevelItem(0);
    }

    if (parentItem == nullptr) {
        parentItem = topLevelItem(0);
    }

    auto itemInfo = getItemInfo(parentItem);
    if ((itemInfo.itemType == type) && (itemInfo.name == name)) {
        return parentItem;
    }

    QTreeWidgetItem * item = nullptr;
    for (int i = 0; (i < parentItem->childCount()) && (item == nullptr); ++i) {
        item = searchItem(parentItem->child(i), type, name);
    }

    return item;
}


void StructuralTreeWidget::selectFirstMap() {

    auto atlasItem = topLevelItem(0);
    if (atlasItem == nullptr) {
        return;
    }

    for (int i = 0; i < atlasItem->childCount(); ++i) {

        auto regionItem = atlasItem->child(i);
        if (regionItem == nullptr) {
            continue;
        }

        for (int j = 0; j < regionItem->childCount(); ++j) {

            auto mapItem = regionItem->child(j);
            if (!mapItem) {
                continue;
            }

            if ((mapItem->columnCount() >= 2) && (mapItem->text(1) == "map")) {
                scrollToItem(mapItem);
                setCurrentItem(mapItem);
            }
        }
    }
}


void StructuralTreeWidget::setSelection(rpgmapper::model::SelectionPointer & selection) {
    this->selection = selection;
    connectSelectionSignals();
    resetStructure();
}
