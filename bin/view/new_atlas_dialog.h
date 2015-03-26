/*
 * new_atlas_dialog.h
 *
 * Create a new atlas dialog
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


#ifndef __VIEW_NEW_ATLAS_DIALOG_H
#define __VIEW_NEW_ATLAS_DIALOG_H
 

// ------------------------------------------------------------
// incs

// Qt
#include <QDialog>


// ------------------------------------------------------------
// decl


// fwd
namespace rpg { class atlas; }
class Ui_new_atlas_dialog;


/**
 * create a new atlas
 */
class new_atlas_dialog : public QDialog {


    Q_OBJECT


public:


    /**
     * ctor
     */
    new_atlas_dialog();


    /**
     * dtor
     */
    virtual ~new_atlas_dialog();


public slots:


    /**
     * clear the dialog
     */
    void clear();


    /**
     * evaluate current main window state
     */
    void evaluate();


private:


    rpg::atlas * m_cAtlas;      /**< the current atlas */

    Ui_new_atlas_dialog * ui;   /**< user elements */

};


#endif

