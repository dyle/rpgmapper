/*
 * main_window.cpp
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

 
// ------------------------------------------------------------
// incs

#include <sstream>
#include <stdexcept>

// Qt
#include <QDesktopWidget>
#include <QPixmapCache>

// rpgmapper
#include "../common_macros.h"
#include "../model/atlas.h"
#include "main_window.h"
#include "ui_main_window.h"


// ------------------------------------------------------------
// code


/**
 * ctor
 */
main_window::main_window() : QMainWindow() {
    
    ui = new Ui_main_window;
    ui->setupUi(this);

    m_cAtlas = new rpg::atlas(this);

    refresh();

    // model connectors
    connect(m_cAtlas, 
        SIGNAL(modified()), 
        SLOT(refresh()));

    // widget connectors
    connect(ui->twAtlas, 
        SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), 
        SLOT(atlas_current_item_changed(QTreeWidgetItem*, QTreeWidgetItem*)));


    // main actions connectors
    connect(ui->acQuit, 
        SIGNAL(triggered()), SLOT(action_quit()));
    connect(ui->acAbout, 
        SIGNAL(triggered()), SLOT(action_about()));
    connect(ui->acNew, 
        SIGNAL(triggered()), SLOT(action_new()));
    connect(ui->acOpen, 
        SIGNAL(triggered()), SLOT(action_open()));
    connect(ui->acSave, 
        SIGNAL(triggered()), SLOT(action_save()));
    connect(ui->acSaveAs, 
        SIGNAL(triggered()), SLOT(action_save_as()));
    connect(ui->acAtlasProperties, 
        SIGNAL(triggered()), SLOT(action_atlas_properties()));

    connect(ui->acNewMapSet, 
        SIGNAL(triggered()), SLOT(action_new_mapset()));
    connect(ui->acDeleteMapSet, 
        SIGNAL(triggered()), SLOT(action_del_mapset()));
    connect(ui->acMapSetProperties, 
        SIGNAL(triggered()), SLOT(action_mapset_properties()));

    connect(ui->acNewMap, 
        SIGNAL(triggered()), SLOT(action_new_map()));
    connect(ui->acDeleteMap, 
        SIGNAL(triggered()), SLOT(action_del_map()));
    connect(ui->acOpenMap, 
        SIGNAL(triggered()), SLOT(action_open_map()));
    connect(ui->acCloseMap, 
        SIGNAL(triggered()), SLOT(action_close_map()));
    connect(ui->acMapProperties, 
        SIGNAL(triggered()), SLOT(action_map_properties()));

    evaluate();
}


/**
 * dtor
 */
main_window::~main_window() {
    delete ui;
}


/**
 * about action triggered
 */
void main_window::action_about() {
}


/**
 * save as action triggered
 */
void main_window::action_save_as() {
}


/**
 * show atlas properties action triggered
 */
void main_window::action_atlas_properties() {
}


/**
 * close map action triggered
 */
void main_window::action_close_map() {
}


/**
 * delete a map action triggered
 */
void main_window::action_del_map() {
}


/**
 * del a whole mapset action triggered
 */
void main_window::action_del_mapset() {
}


/**
 * show map properties action triggered
 */
void main_window::action_map_properties() {
}


/**
 * show mapset properties action triggered
 */
void main_window::action_mapset_properties() {
}


/**
 * create a new mapset action triggered
 */
void main_window::action_new_mapset() {
}


/**
 * new atlas action triggered
 */
void main_window::action_new() {
}


/**
 * new map action triggered
 */
void main_window::action_new_map() {
}


/**
 * open atlas action triggered
 */
void main_window::action_open() {
}


/**
 * open map action triggered
 */
void main_window::action_open_map() {
}


/**
 * quit action triggered
 */
void main_window::action_quit() {
}


/**
 * save atlas action triggered
 */
void main_window::action_save() {
}


/**
 * a new item on the atlas has been set to the current one
 *
 * @param   cItem           the new current item
 * @param   cPreviousItem   the old previous item
 */
void main_window::atlas_current_item_changed(UNUSED QTreeWidgetItem * cItem, UNUSED QTreeWidgetItem * cPreviousItem) {
    evaluate();
}


/**
 * centers the window on the desktop with default width and height
 */
void main_window::center_window() {
    
    const int nDefaultWidth = 600;
    const int nDefaultHeight = 400;
    
    QDesktopWidget* cDesktop = qApp->desktop();
    int nX = (cDesktop->width() - nDefaultWidth) / 2;
    int nY = (cDesktop->height() - nDefaultHeight) / 2;
    
    // ready to display
    resize(QSize(nDefaultWidth, nDefaultHeight));
    move(QPoint(nX, nY));
}


/**
 * clear all visible data items
 */
void main_window::clear() {
    ui->twAtlas->clear();
}


/**
 * evaluate current main window state
 */
void main_window::evaluate() {

    std::stringstream ss;
    ss << "RPGMapper - " << m_cAtlas->name();
    if (m_cAtlas->unsaved()) ss << "*";
    setWindowTitle(QString::fromStdString(ss.str()));

    ui->acQuit->setEnabled(true);
    ui->acAbout->setEnabled(true);
    ui->acNew->setEnabled(true);
    ui->acOpen->setEnabled(true);
    ui->acSave->setEnabled(true);
    ui->acSaveAs->setEnabled(true);
    ui->acAtlasProperties->setEnabled(true);

    main_window::tree_item_type eCurrentItemType = main_window::tree_item_type::UNKNOWN;
    try {
        eCurrentItemType = item_type(ui->twAtlas->currentItem());
    }
    catch (...) {}


    ui->acNewMapSet->setEnabled(eCurrentItemType >= main_window::tree_item_type::ATLAS);
    ui->acDeleteMapSet->setEnabled(eCurrentItemType >= main_window::tree_item_type::MAPSET);
    ui->acMapSetProperties->setEnabled(eCurrentItemType >= main_window::tree_item_type::MAPSET);

    ui->acNewMap->setEnabled(eCurrentItemType >= main_window::tree_item_type::MAPSET);
    ui->acDeleteMap->setEnabled(eCurrentItemType >= main_window::tree_item_type::MAP);
    ui->acOpenMap->setEnabled(eCurrentItemType >= main_window::tree_item_type::MAP);
    // TODO
    // ui->acCloseMap->setEnabled(eCurrentItemType >= main_window::tree_item_type::MAP); 
    ui->acMapProperties->setEnabled(eCurrentItemType >= main_window::tree_item_type::MAP);
}


/**
 * find a map by index
 *
 * @param   nIndex      map  index
 * @return  the tree widget item for the map (or nullptr)
 */
QTreeWidgetItem * main_window::find_map(unsigned int nIndex) {

    QTreeWidgetItem * res = nullptr;

    QString sMapKey = QString("map:") + QString::number(nIndex);
    QList<QTreeWidgetItem *> cSearchResult = ui->twAtlas->findItems(sMapKey, Qt::MatchExactly, 1);
    if (cSearchResult.size() > 0) {
        res = cSearchResult.first();
    }
    
    return res;
}


/**
 * find a map item by name
 *
 * @param   sName       name of the map group
 * @return  the tree widget for the group (or nullptr)
 */
QTreeWidgetItem * main_window::find_mapset(std::string const & sName) {

    QTreeWidgetItem * res = nullptr;

    QString sMapKey = QString("mapset:") + QString::fromStdString(sName);
    QList<QTreeWidgetItem *> cSearchResult = ui->twAtlas->findItems(sMapKey, Qt::MatchExactly, 1);
    if (cSearchResult.size() > 0) {
        res = cSearchResult.first();
    }
    
    return res;
}


/**
 * refresh data display
 */
void main_window::refresh() {

    QTreeWidgetItem * cAtlasItem = nullptr;
    QPixmap cPixmap;

    // rebuild tree widget
    if (ui->twAtlas->topLevelItemCount() == 0) {
        cAtlasItem = new QTreeWidgetItem(ui->twAtlas);
    }
    else {
        cAtlasItem = ui->twAtlas->topLevelItem(0);
    }
    cAtlasItem->setText(0, QString::fromStdString(m_cAtlas->name()));
    cAtlasItem->setText(1, "atlas");
    QPixmapCache::find("atlas", &cPixmap);
    cAtlasItem->setIcon(0, cPixmap);
    cAtlasItem->setExpanded(true);

    // walk over the map groups
    for (auto cMapGroupIter = m_cAtlas->maps().cbegin(); cMapGroupIter != m_cAtlas->maps().cend(); ++cMapGroupIter) {

        // pick the old entry or create new one and then set the new values
        QTreeWidgetItem * cMapGroupItem = nullptr;
        QString sKey = QString("mapset:") + QString::fromStdString((*cMapGroupIter).first);
        QList<QTreeWidgetItem *> cMapGroupItems = ui->twAtlas->findItems(sKey, Qt::MatchExactly, 1);
        if (cMapGroupItems.size() == 0) {
            cMapGroupItem = new QTreeWidgetItem(cAtlasItem);
        }
        else {
            cMapGroupItem = cMapGroupItems.first();
        }

        // adjust mapset values
        cMapGroupItem->setText(0, QString::fromStdString((*cMapGroupIter).first));
        cMapGroupItem->setText(1, sKey);
        QPixmapCache::find("mapset", &cPixmap);
        cMapGroupItem->setIcon(0, cPixmap);

        // walk over the maps in the group
        for (auto cMapIter = (*cMapGroupIter).second.cbegin(); cMapIter != (*cMapGroupIter).second.cend(); ++cMapIter) {

            // pick the old entry or create new one and then set the new values
            QTreeWidgetItem * cMapItem = nullptr;
            QString sKey = QString("map:") + QString::fromStdString((*cMapIter)->name());
            QList<QTreeWidgetItem *> cMapItems = ui->twAtlas->findItems(sKey, Qt::MatchExactly, 1);
            if (cMapItems.size() == 0) {
                cMapItem = new QTreeWidgetItem(cMapGroupItem);
            }
            else {
                cMapItem = cMapItems.first();
            }

            // reparent if necessary
            if (cMapItem->parent() != cMapGroupItem) {
                cMapItem->parent()->removeChild(cMapItem);
                cMapGroupItem->addChild(cMapItem);
            }

            // adjust map values
            cMapItem->setText(0, QString::fromStdString((*cMapIter)->name()));
            cMapItem->setText(1, sKey);
            QPixmapCache::find("map", &cPixmap);
            cMapItem->setIcon(0, cPixmap);
        }
    }
}


/**
 * figure out which item type is the given item
 *
 * @param   cItem       the TreeWidgetItem in consideration
 * @return  if represents an atlas, mapset or map
 */
main_window::tree_item_type main_window::item_type(QTreeWidgetItem * cItem) {

    if (!cItem) throw std::invalid_argument("can't identify item type of a nullptr");
   
    if (cItem->text(1).left(strlen("atlas")) == "atlas") return tree_item_type::ATLAS;
    if (cItem->text(1).left(strlen("mapset:")) == "mapset:") return tree_item_type::MAPSET;
    if (cItem->text(1).left(strlen("map:")) == "map:") return tree_item_type::MAP;

    throw std::invalid_argument("unknown item type");
    return tree_item_type::UNKNOWN;
}

