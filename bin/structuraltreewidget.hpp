/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_STRUCTURALTREEWIDGET_HPP
#define RPGMAPPER_VIEW_STRUCTURALTREEWIDGET_HPP


#include <QTreeWidget>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>


namespace rpgmapper {
namespace view {

class MainWindow;

class StructuralTreeWidget : public QTreeWidget {

    Q_OBJECT

    MainWindow * mainWindow = nullptr;

    enum class ItemType { atlas, map, region };

    struct ItemInfo {
        ItemType itemType = ItemType::atlas;
        QString name;
        bool valid = false;
    };

public:

    explicit StructuralTreeWidget(MainWindow * parent = nullptr);

public slots:

    void changedAtlasName(QString const & name);

    void changedMapName(QString const & nameBefore, QString const & nameAfter);

    void changedRegionName(QString const & nameBefore, QString const & nameAfter);

    void deletedMap(QString const & name);

    void deletedRegion(QString const & name);

    void newMap(QString const & name);

    void newRegion(QString const & name);

    void selectFirstMap();

    void resetStructure();

private:

    void addAtlas();

    QTreeWidgetItem * addMap(QTreeWidgetItem * regionItem, rpgmapper::model::MapPointer const & map);

    QTreeWidgetItem * addRegion(QTreeWidgetItem * atlasItem, rpgmapper::model::RegionPointer const & region);

    rpgmapper::model::AtlasPointer getAtlas();

    ItemInfo getItemInfo(QTreeWidgetItem * item) const;

    MainWindow * getMainWindow() { return mainWindow; }

    QTreeWidgetItem * searchItem(ItemType type, QString const & name) const;

    QTreeWidgetItem * searchItem(QTreeWidgetItem * parentItem, ItemType type, QString const & name) const;

private slots:

    void changedCurrentItem(QTreeWidgetItem * current);

    void doubleClickedItem(QTreeWidgetItem * item, int column);

signals:

    void doubleClickedAtlas();

    void doubleClickedMap(QString mapName);

    void doubleClickedRegion(QString regionName);

    void selectedAtlas();

    void selectedMap(QString mapName);

    void selectedRegion(QString regionName);
};


}
}


#endif
