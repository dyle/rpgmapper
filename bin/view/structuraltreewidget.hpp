/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef VIEW_STRUCTURALTREEWIDGET_HPP
#define VIEW_STRUCTURALTREEWIDGET_HPP


// ------------------------------------------------------------
// incs

#include <QTreeWidget>

// rpgmapper
#include <rpgmapper/types.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace view {


/**
 * A QTreeWidget which displays the Atlas structure.
 */
class StructuralTreeWidget : public QTreeWidget {


    Q_OBJECT


public:


    /**
     * Ctor
     *
     * @param   cParent     parent widget
     */
    explicit StructuralTreeWidget(QWidget * cParent = nullptr);


public slots:


    /**
     * The atlas has changed.
     */
    void changedAtlasName();


    /**
     * A map changed its name.
     *
     * @param   nMapId          id of the map changed
     */
    void changedMapName(rpgmapper::model::mapid_t nMapId);


    /**
     * A region changed its name.
     *
     * @param   nRegionId       id of the region changed
     */
    void changedRegionName(rpgmapper::model::regionid_t nRegionId);


    /**
     * A map has been deleted.
     *
     * @param   nMapId      id of the map deleted
     */
    void deletedMap(rpgmapper::model::mapid_t nMapId);


    /**
     * A region has been deleted.
     *
     * @param nRegionId     id of the region deleted
     */
    void deletedRegion(rpgmapper::model::regionid_t nRegionId);


    /**
     * We have a new map.
     *
     * @param   nMapId      id of the new map
     */
    void newMap(rpgmapper::model::mapid_t nMapId);


    /**
     * We have a new region.
     *
     * @param nRegionId     id of the new region
     */
    void newRegion(rpgmapper::model::regionid_t nRegionId);


    /**
     * Selects the first available Map in the structure.
     */
    void selectFirstMap();


    /**
     * Reset structure (builds Atlas structure anew)
     */
    void resetStructure();


private slots:


    /**
     * The changed the selected item.
     *
     * @param   cCurrent        new selected item
     */
    void changedCurrentItem(QTreeWidgetItem * cCurrent);


    /**
     * The user double clicked an item.
     *
     * @param   cItem       the item double clicked
     * @param   nColumn     the column where she clicked
     */
    void doubleClickedItem(QTreeWidgetItem * cItem, int nColumn);


signals:


    /**
     * The atlas has been double-clicked.
     */
    void doubleClickedAtlas();


    /**
     * A map has been double clicked.
     *
     * @param   nMapId          id of the map double clicked
     */
    void doubleClickedMap(rpgmapper::model::mapid_t nMapId);


    /**
     * A region has been double clicked.
     *
     * @param   nRegionId       id of the region double clicked
     */
    void doubleClickedRegion(rpgmapper::model::regionid_t nRegionId);


    /**
     * Selected the atlas.
     */
    void selectedAtlas();


    /**
     * Selected a map.
     *
     * @param   nMapId      id of the newly selected map
     */
    void selectedMap(rpgmapper::model::mapid_t nMapId);


    /**
     * Selected a region.
     *
     * @param   nRegionId   id of the newly selected region
     */
    void selectedRegion(rpgmapper::model::regionid_t cRegionId);


};


}
}


#endif
