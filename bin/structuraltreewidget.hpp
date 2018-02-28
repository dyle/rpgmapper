/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_VIEW_STRUCTURALTREEWIDGET_HPP
#define RPGMAPPER_VIEW_STRUCTURALTREEWIDGET_HPP


#include <QTreeWidget>

#include <rpgmapper/selection.hpp>


namespace rpgmapper {
namespace view {

class MainWindow;

class StructuralTreeWidget : public QTreeWidget {

    Q_OBJECT

    QWeakPointer<rpgmapper::model::Selection> selection;

    enum class ItemType { atlas, map, region };

    struct ItemInfo {
        ItemType itemType = ItemType::atlas;
        QString name;
        bool valid = false;
    };

public:

    explicit StructuralTreeWidget(QWidget * parent = nullptr);

public slots:

    void addedMap(QString regionName, QString mapName);

    void changedAtlasName(QString name);

    void changedMapName(QString regionName, QString nameBefore, QString nameAfter);

    void changedRegionName(QString nameBefore, QString nameAfter);

    void createdMap(QString regionName, QString mapName);

    void createdRegion(QString name);

    void removedMap(QString regionName, QString mapName);

    void removedRegion(QString name);

    void selectFirstMap();

    void setSelection(rpgmapper::model::SelectionPointer & selection);

    void resetStructure();

private:

    void addAtlas();

    QTreeWidgetItem * addMap(QTreeWidgetItem * regionItem, rpgmapper::model::MapPointer const & map);

    QTreeWidgetItem * addRegion(QTreeWidgetItem * atlasItem, rpgmapper::model::RegionPointer const & region);

    void connectSelectionSignals();

    ItemInfo getItemInfo(QTreeWidgetItem * item) const;

    QTreeWidgetItem * searchItem(ItemType type, QString const & name) const;

    QTreeWidgetItem * searchItem(QTreeWidgetItem * parentItem, ItemType type, QString const & name) const;

private slots:

    void changedCurrentItem(QTreeWidgetItem * current);

    void doubleClickedItem(QTreeWidgetItem * item, int column);

    void singleClickedItem(QTreeWidgetItem * item, int column);

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
