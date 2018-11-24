/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QPixmapCache>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

#include "structuraltreewidget.hpp"

#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif

using namespace rpgmapper::model;
using namespace rpgmapper::view;


/**
 * This enumerates the different tree item types we support here.
 */
enum class ItemType {
    atlas,
    region,
    map
};


/**
 * A helper structure to qualify a tree widget item.
 */
struct ItemInfo {
    ItemType type;          /**< What the current widget item is representing. */
    QString name;           /**< The name (id) of the item current represented model item. */
    bool valid;             /**< true, if we this is a valid item here. */
};


/**
 * Extracts the item info of a given treeWidgetItem.
 *
 * @param treeWidgetItem
 * @return
 */
ItemInfo getItemInfo(QTreeWidgetItem const * treeWidgetItem);


/**
 * Searches for a specific item in the tree widget.
 *
 * @param treeWidgetItem
 * @return
 */
QTreeWidgetItem * searchItem(QTreeWidget * treeWidget, ItemType type, QString const & name);


StructuralTreeWidget::StructuralTreeWidget(QWidget * parent) : QTreeWidget{parent} {
    
    connect(this, &QTreeWidget::currentItemChanged, this, &StructuralTreeWidget::changedCurrentItem);
    connect(this, &QTreeWidget::itemDoubleClicked, this, &StructuralTreeWidget::doubleClickedItem);
    connect(this, &QTreeWidget::itemClicked, this, &StructuralTreeWidget::singleClickedItem);
    
    resetStructure();
}


void StructuralTreeWidget::addAtlas() {

    static QPixmap atlasPixmap;
    if (atlasPixmap.isNull()) {
        QPixmapCache::find("atlas", &atlasPixmap);
    }

    auto session = Session::getCurrentSession();
    auto atlas = session->getAtlas();

    QStringList columns;
    columns << atlas->getName() << "atlas" << "0";

    auto atlasItem = new QTreeWidgetItem{columns};
    atlasItem->setIcon(0, atlasPixmap);
    insertTopLevelItem(0, atlasItem);

    for (auto const & region: atlas->getRegions()) {
        auto cTWRegion = addRegion(atlasItem, region.second);
        cTWRegion->setExpanded(true);
    }

    atlasItem->setExpanded(true);
    
    connect(atlas.data(), &Nameable::nameChanged, this, &StructuralTreeWidget::atlasNameChanged);
    connect(atlas.data(), &Atlas::regionAdded, this, &StructuralTreeWidget::regionAdded);
    connect(atlas.data(), &Atlas::regionRemoved, this, &StructuralTreeWidget::regionRemoved);
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
    
    connect(map.data(), &Nameable::nameChanged, this, &StructuralTreeWidget::mapNameChanged);
    
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

    for (auto const & map: region->getMaps()) {
        auto mapItem = addMap(regionItem, map.second);
        mapItem->setExpanded(true);
    }
    
    connect(region.data(), &Nameable::nameChanged, this, &StructuralTreeWidget::regionNameChanged);
    connect(region.data(), &Region::mapAdded, this, &StructuralTreeWidget::mapAdded);
    connect(region.data(), &Region::mapRemoved, this, &StructuralTreeWidget::mapRemoved);

    return regionItem;
}


void StructuralTreeWidget::atlasNameChanged(UNUSED QString oldName, QString newName){
    auto item = topLevelItem(0);
    item->setText(0, newName);
}


void StructuralTreeWidget::changedCurrentItem(QTreeWidgetItem * current) {
    
    auto itemInfo = getItemInfo(current);
    if (!itemInfo.valid) {
        return;
    }

    auto session = Session::getCurrentSession();
    switch (itemInfo.type) {

        case ItemType::atlas:
            session->selectAtlas();
            emit selectedAtlas();
            break;

        case ItemType::map:
            session->selectMap(itemInfo.name);
            emit selectedMap(itemInfo.name);
            break;

        case ItemType::region:
            session->selectRegion(itemInfo.name);
            emit selectedRegion(itemInfo.name);
            break;
    }
}


void StructuralTreeWidget::doubleClickedItem(QTreeWidgetItem * item, UNUSED int column) {
    
    auto itemInfo = getItemInfo(item);
    if (!itemInfo.valid) {
        return;
    }
    
    auto session = Session::getCurrentSession();
    switch (itemInfo.type) {

        case ItemType::atlas:
            session->selectAtlas();
            emit doubleClickedAtlas();
            break;

        case ItemType::map:
            session->selectMap(itemInfo.name);
            emit doubleClickedMap(itemInfo.name);
            break;

        case ItemType::region:
            session->selectRegion(itemInfo.name);
            emit doubleClickedRegion(itemInfo.name);
            break;
    }
}


void StructuralTreeWidget::mapAdded(QString name) {
    
    auto session = Session::getCurrentSession();
    auto regionName = session->getRegionOfMap(name);
    if (!regionName.isEmpty()) {
        
        auto regionItem = ::searchItem(this, ItemType::region, regionName);
        if (!regionItem) {
            throw std::runtime_error{"Try to add map to region in structure widget, but region is not present."};
        }
    
        auto mapItem = addMap(regionItem, session->findMap(name));
        if (mapItem) {
            scrollToItem(mapItem, QAbstractItemView::EnsureVisible);
            setCurrentItem(mapItem);
        }
    }
}


void StructuralTreeWidget::mapNameChanged(QString oldName, QString newName) {
    auto item = ::searchItem(this, ItemType::map, oldName);
    if (item) {
        item->setText(0, newName);
    }
}


void StructuralTreeWidget::mapRemoved(QString name) {

    auto item = ::searchItem(this, ItemType::map, name);
    if (item) {
        
        if (item->isSelected()) {
            auto session = Session::getCurrentSession();
            auto regionName = session->getRegionOfMap(name);
            session->selectRegion(regionName);
        }
        
        topLevelItem(0)->removeChild(item);
        delete item;
    }
}


void StructuralTreeWidget::resetStructure() {
    clear();
    addAtlas();
    sortByColumn(1, Qt::AscendingOrder);
    setSortingEnabled(true);
}


void StructuralTreeWidget::regionAdded(QString name) {

    auto session = Session::getCurrentSession();
    auto region = session->findRegion(std::move(name));
    if (region->isValid()) {
        
        auto itemInfo = searchItem(this, ItemType::region, region->getName());
        if (!itemInfo) {
            addRegion(topLevelItem(0), region);
        }
    }
}


void StructuralTreeWidget::regionNameChanged(QString oldName, QString newName) {
    auto item = ::searchItem(this, ItemType::region, oldName);
    if (item) {
        item->setText(0, newName);
    }
}


void StructuralTreeWidget::regionRemoved(QString name) {
    
    auto item = ::searchItem(this, ItemType::region, name);
    if (item) {
        
        if (item->isSelected()) {
            auto session = Session::getCurrentSession();
            session->selectAtlas();
        }
        
        topLevelItem(0)->removeChild(item);
        delete item;
    }
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


void StructuralTreeWidget::selectMap(QString name) {
    
    auto session = Session::getCurrentSession();
    auto map = session->findMap(name);
    if (!map->isValid()) {
        return;
    }
    
    auto mapItem = searchItem(this, ItemType::map, name);
    if (mapItem && (mapItem != currentItem())) {
        scrollToItem(mapItem);
        setCurrentItem(mapItem);
    }
}


void StructuralTreeWidget::selectRegion(QString name) {
    
    auto session = Session::getCurrentSession();
    auto region = session->findRegion(name);
    if (!region->isValid()) {
        return;
    }
    
    auto regionItem = searchItem(this, ItemType::region, name);
    if (regionItem && (regionItem != currentItem())) {
        scrollToItem(regionItem);
        setCurrentItem(regionItem);
    }
}


void StructuralTreeWidget::singleClickedItem(QTreeWidgetItem * item, UNUSED int column) {
    
    auto itemInfo = getItemInfo(item);
    if (!itemInfo.valid) {
        return;
    }

    auto session = Session::getCurrentSession();
    switch (itemInfo.type) {

        case ItemType::atlas:
            session->selectAtlas();
            break;

        case ItemType::map:
            session->selectMap(itemInfo.name);
            break;

        case ItemType::region:
            session->selectRegion(itemInfo.name);
            break;
    }
}


ItemInfo getItemInfo(QTreeWidgetItem const * treeWidgetItem) {
    
    ItemInfo itemInfo = {ItemType::atlas, QString::null, false};
    
    if ((treeWidgetItem) && (treeWidgetItem->columnCount() > 1)) {
    
        if (treeWidgetItem->text(1) == "atlas") {
            itemInfo = {ItemType::atlas, treeWidgetItem->text(0), true};
        }
        else
        if (treeWidgetItem->text(1) == "region") {
            itemInfo = {ItemType::region, treeWidgetItem->text(0), true};
        }
        else
        if (treeWidgetItem->text(1) == "map") {
            itemInfo = {ItemType::map, treeWidgetItem->text(0), true};
        }
    }
    
    return itemInfo;
}


QTreeWidgetItem * searchItem(QTreeWidget * treeWidget, ItemType type, QString const & name) {
    
    ItemInfo itemInfo = {ItemType::atlas, QString::null, false};
    
    auto atlasItem = treeWidget->topLevelItem(0);
    if (type == ItemType::atlas) {
        return atlasItem;
    }
    
    QTreeWidgetItem * item = nullptr;
    
    for (int i = 0; (i < atlasItem->childCount()) && !item; ++i) {
        
        auto regionItem = atlasItem->child(i);
        if (type == ItemType::region) {
            item = (regionItem->text(0) == name) ? regionItem : nullptr;
        }
        else {
            for (int j = 0; (j < regionItem->childCount()) && !item; ++j) {
                auto mapItem = regionItem->child(j);
                item = (mapItem->text(0) == name) ? mapItem : nullptr;
            }
        }
    }
    
    return item;
}
