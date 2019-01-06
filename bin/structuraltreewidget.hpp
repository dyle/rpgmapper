/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
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

    /**
     * The atlas changed its name.
     *
     * @param   oldName     old name of the atlas.
     * @param   newName     new name of the atlas.
     */
    void atlasNameChanged(QString oldName, QString newName);

    /**
     * A map has been added to the structure.
     *
     * @param   name        the name of the map added.
     */
    void mapAdded(QString name);
    
    /**
     * A map changed its name.
     *
     * @param   oldName     old name of the map.
     * @param   newName     new name of the map.
     */
    void mapNameChanged(QString oldName, QString newName);
    
    /**
     * A map has been removed from the structure.
     *
     * @param   name        the name of the map removed.
     */
    void mapRemoved(QString name);
    
    /**
     * A region has been added.
     *
     * @param   name        name of the region added.
     */
    void regionAdded(QString name);
    
    /**
     * A region changed its name.
     *
     * @param   oldName         old name of the region.
     * @param   newName         new name of the region.
     */
    void regionNameChanged(QString oldName, QString newName);
    
    /**
     * A region has been removed.
     *
     * @param   name        name of the region removed.
     */
    void regionRemoved(QString name);
    
    /**
     * Selects the very first map in the structure.
     */
    void selectFirstMap();

    /**
     * Select and show a map.
     *
     * @param   name        the map to show.
     */
    void selectMap(QString name);
    
    /**
     * Select and show a region.
     *
     * @param   name        the region to show.
     */
    void selectRegion(QString name);
    
    /**
     * Clears everything and grabs the current session atlas and refresh the whole displayed structure.
     */
    void resetStructure();

private:

    /**
     * Adds the current session atlas to the structure.
     */
    void addAtlas();

    /**
     * Adds a map to a region.
     *
     * @param   regionItem      the tree widget item holding the region.
     * @param   map             the map to add.
     * @return  the new tree widget item holding the map.
     */
    QTreeWidgetItem * addMap(QTreeWidgetItem * regionItem, rpgmapper::model::MapPointer const & map);

    /**
     * Adds a region to the structure.
     *
     * @param   atlasItem   the tree widget item holding the atlas.
     * @param   region      the region to add.
     * @return  the new tree widget item holding the region.
     */
    QTreeWidgetItem * addRegion(QTreeWidgetItem * atlasItem, rpgmapper::model::RegionPointer const & region);

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
