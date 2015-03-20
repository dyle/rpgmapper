/*
 * main_window.h
 *
 * Main window for the RPGMapper
 * 
 * Copyright (C) 2015, Oliver Maurhart, <dyle@dyle.org>
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


#ifndef __VIEW_MAIN_WINDOW_H_
#define __VIEW_MAIN_WINDOW_H_
 

// ------------------------------------------------------------
// incs

// Qt
#include <QMainWindow>
#include <QTreeWidgetItem>


// ------------------------------------------------------------
// decl


// fwd
namespace rpg { class atlas; }
class Ui_main_window;


/**
 * the rpgmapper main window
 */
class main_window : public QMainWindow {


    Q_OBJECT


    /**
     * type of a picked treewidgetitem
     */
    enum class tree_item_type : char {
        UNKNOWN = 0,
        ATLAS = 1,
        MAPSET = 2,
        MAP = 3
    };


public:


    /**
     * ctor
     */
    main_window();


    /**
     * dtor
     */
    virtual ~main_window();


    /**
     * get the current atlas
     *
     * @return  the current atlas
     */
    rpg::atlas * atlas() { return m_cAtlas; };


public slots:


    /**
     * clear all visible data items
     */
    void clear();


    /**
     * evaluate current main window state
     */
    void evaluate();


    /**
     * refresh data display
     */
    void refresh();


private slots:


    /**
     * a new item on the atlas has been set to the current one
     *
     * @param   cItem           the new current item
     * @param   cPreviousItem   the old previous item
     */
    void atlasCurrentItemChanged(QTreeWidgetItem * cItem, QTreeWidgetItem * cPreviousItem);


private:


    /**
     * find a map by index
     *
     * @param   nIndex      map  index
     * @return  the tree widget item for the map (or nullptr)
     */
    QTreeWidgetItem * find_map(unsigned int nIndex);


    /**
     * find a map item by name
     *
     * @param   sName       name of the map group
     * @return  the tree widget for the group (or nullptr)
     */
    QTreeWidgetItem * find_mapset(std::string const & sName);


    /**
     * figure out which item type is the given item
     *
     * @param   cItem       the TreeWidgetItem in consideration
     * @return  if represents an atlas, mapset or map
     */
    tree_item_type item_type(QTreeWidgetItem * cItem);


    rpg::atlas * m_cAtlas;      /**< the current atlas */

    Ui_main_window * ui;        /**< user elements */
 

};


#endif

