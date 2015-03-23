/*
 * atlas_properties_dialog.h
 *
 * Show and modify properties of an atals
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


#ifndef __VIEW_ATLAS_PROPERTIES_DIALOG_H
#define __VIEW_ATLAS_PROPERTIES_DIALOG_H
 

// ------------------------------------------------------------
// incs

// Qt
#include <QDialog>


// ------------------------------------------------------------
// decl


// fwd
namespace rpg { class atlas; }


/**
 * show and modify the properties of an atlas
 */
class atlas_properties_dialog : public QDialog {


    Q_OBJECT


public:


    /**
     * ctor
     */
    atlas_properties_dialog();


    /**
     * dtor
     */
    virtual ~atlas_properties_dialog();


private:


    rpg::atlas * m_cAtlas;      /**< the current atlas */

    Ui_main_window * ui;        /**< user elements */

};


#endif

