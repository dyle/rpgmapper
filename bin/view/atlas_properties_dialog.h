/*
 * atlas_properties_dialog.h
 *
 * Show and modify properties of an atlas
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
class Ui_atlas_properties_dialog;

/**
 * show and modify the properties of an atlas
 */
class atlas_properties_dialog : public QDialog {


    Q_OBJECT


public:


    /**
     * ctor
     *
     * @param   sTitle      title of the dialog
     * @param   sText       additional text to set
     */
    atlas_properties_dialog(QString const & sTitle, QString const & sText);


    /**
     * dtor
     */
    virtual ~atlas_properties_dialog();


    /**
     * get the atlas description
     *
     * @return  description of the atlas
     */
    QString description() const;


    /**
     * get the atlas image
     *
     * @return  the atlas image
     */
    QImage & image();


    /**
     * get the atlas image
     *
     * @return  the atlas image
     */
    QImage const & image() const;


    /**
     * get the path to the atlas image
     *
     * @return  path to the atlas image
     */
    QString image_path() const;


    /**
     * get the atlas name
     *
     * @return  name of the atlas
     */
    QString name() const;


    /**
     * set the image path to search
     *
     * @param   sPath       the path to the user's images
     */
    void set_image_path(QString const & sPath);


public slots:


    /**
     * clear the dialog
     */
    void clear();


    /**
     * evaluate current main window state
     */
    void evaluate();


private slots:


    /**
     * atlas properties have changed
     */
    void atlas_properties_changed();


private:


    rpg::atlas * m_cAtlas;                  /**< the current atlas */

    Ui_atlas_properties_dialog * ui;        /**< user elements */

};


#endif

