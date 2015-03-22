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
        SLOT(atlasCurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));


    // main actions connectors
    connect(ui->acQuit, SIGNAL(triggered()), SLOT(actionQuit()));
    connect(ui->acAbout, SIGNAL(triggered()), SLOT(actionAbout()));
    connect(ui->acNew, SIGNAL(triggered()), SLOT(actionNew()));
    connect(ui->acOpen, SIGNAL(triggered()), SLOT(actionOpen()));
    connect(ui->acSave, SIGNAL(triggered()), SLOT(actionSave()));
    connect(ui->acSaveAs, SIGNAL(triggered()), SLOT(actionaSaveAs()));
    connect(ui->acAtlasProperties, SIGNAL(triggered()), SLOT(actionAtlasProperties()));

    connect(ui->acNewMapSet, SIGNAL(triggered()), SLOT(actionNeMapset()));
    connect(ui->acDeleteMapSet, SIGNAL(triggered()), SLOT(actionDelMapset()));
    connect(ui->acMapSetProperties, SIGNAL(triggered()), SLOT(actionMapsetProperties()));

    connect(ui->acNewMap, SIGNAL(triggered()), SLOT(actionNewMap()));
    connect(ui->acDeleteMap, SIGNAL(triggered()), SLOT(actionDelMap()));
    connect(ui->acOpenMap, SIGNAL(triggered()), SLOT(actionOpenMap()));
    connect(ui->acCloseMap, SIGNAL(triggered()), SLOT(actionCloseMap()));
    connect(ui->acMapProperties, SIGNAL(triggered()), SLOT(actionMapProperties()));

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
void main_window::actionAbout() {
}


/**
 * about action triggered
 */
void main_window::actionaSaveAs() {
}


/**
 * about action triggered
 */
void main_window::actionAtlasProperties() {
}


/**
 * about action triggered
 */
void main_window::actionCloseMap() {
}


/**
 * about action triggered
 */
void main_window::actionDelMap() {
}


/**
 * about action triggered
 */
void main_window::actionDelMapset() {
}


/**
 * about action triggered
 */
void main_window::actionMapProperties() {
}


/**
 * about action triggered
 */
void main_window::actionMapsetProperties() {
}


/**
 * about action triggered
 */
void main_window::actionNeMapset() {
}


/**
 * about action triggered
 */
void main_window::actionNew() {
}


/**
 * about action triggered
 */
void main_window::actionNewMap() {
}


/**
 * about action triggered
 */
void main_window::actionOpen() {
}


/**
 * about action triggered
 */
void main_window::actionOpenMap() {
}


/**
 * about action triggered
 */
void main_window::actionQuit() {
}


/**
 * about action triggered
 */
void main_window::actionSave() {
}


/**
 * a new item on the atlas has been set to the current one
 *
 * @param   cItem           the new current item
 * @param   cPreviousItem   the old previous item
 */
void main_window::atlasCurrentItemChanged(UNUSED QTreeWidgetItem * cItem, UNUSED QTreeWidgetItem * cPreviousItem) {
    evaluate();
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

