/*
 * structuraltreewidget.hpp
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
