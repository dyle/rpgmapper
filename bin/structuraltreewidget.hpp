/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_VIEW_STRUCTURALTREEWIDGET_HPP
#define RPGMAPPER_VIEW_STRUCTURALTREEWIDGET_HPP

#include <QTreeWidget>

#include <rpgmapper/map_pointer.hpp>
#include <rpgmapper/region_pointer.hpp>


namespace rpgmapper {
namespace view {


// fwd
// TODO: class MainWindow;

/**
 * This widget shows the organisational structure of the current atlas.
 */
class StructuralTreeWidget : public QTreeWidget {

    Q_OBJECT

public:

    /**
     * Constructor.
     *
     * @param   parent      Parent QWidget instance.
     */
    explicit StructuralTreeWidget(QWidget * parent = nullptr);

public slots:

    //void changedAtlasName(QString oldName, QString newName);

    //void changedMapName(QString regionName, QString nameBefore, QString nameAfter);

    //void changedRegionName(QString nameBefore, QString nameAfter);

    //void createdMap(QString regionName, QString mapName);

    //void createdRegion(QString name);

    //void removedMap(QString regionName, QString mapName);

    //void removedRegion(QString name);

    //void selectFirstMap();

    //void resetStructure();

private:

    //void addAtlas();

    //QTreeWidgetItem * addMap(QTreeWidgetItem * regionItem, rpgmapper::model::MapPointer const & map);

    //QTreeWidgetItem * addRegion(QTreeWidgetItem * atlasItem, rpgmapper::model::RegionPointer const & region);

    //void connectSelectionSignals();

    //ItemInfo getItemInfo(QTreeWidgetItem * item) const;

    //QTreeWidgetItem * searchItem(ItemType type, QString const & name) const;

    //QTreeWidgetItem * searchItem(QTreeWidgetItem * parentItem, ItemType type, QString const & name) const;

private slots:

    /**
     * Adopts the standard signal for changed items of the QTabWidget for special handling.
     *
     * @param   current     the current tab widget item changed.
     */
    void changedCurrentItem(QTreeWidgetItem * current);
    
    /**
     * Adopts the standard signal for double clicked items of the QTabWidget for special handling.
     *
     * @param   item            the item double clicked.
     * @param   column          the column inside the item double clicked.
     */
    void doubleClickedItem(QTreeWidgetItem * item, int column);
    
    /**
     * Adopts the standard signal for single clicked items of the QTabWidget for special handling.
     *
     * @param   item            the item single clicked.
     * @param   column          the column inside the item single clicked.
     */
    void singleClickedItem(QTreeWidgetItem * item, int column);

signals:

    /**
     * The user double clicked the atlas.
     */
    void doubleClickedAtlas();

    /**
     * The user double clicked a map.
     *
     * @param   mapName         the map name double clicked.
     */
    void doubleClickedMap(QString mapName);

    /**
     * The user double clicked a region.
     *
     * @param   regionName      the region name double clicked.
     */
    void doubleClickedRegion(QString regionName);

    /**
     * The user selected the atlas.
     */
    void selectedAtlas();

    /**
     * The user selected a map.
     *
     * @param   mapName         the map selected.
     */
    void selectedMap(QString mapName);

    /**
     * The user selected a region.
     *
     * @param   regionName      the region selected.
     */
    void selectedRegion(QString regionName);
};


}
}


#endif
