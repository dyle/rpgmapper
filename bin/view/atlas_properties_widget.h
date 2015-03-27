/*
 * atlas_properties_widget.h
 *
 * Show and modify properties of an atlas (as a custom widget)
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


#ifndef __VIEW_ATLAS_PROPERTIES_WIDGET_H
#define __VIEW_ATLAS_PROPERTIES_WIDGET_H
 

// ------------------------------------------------------------
// incs

// Qt
#include <QWidget>


// ------------------------------------------------------------
// decl

// fix some Qt4 uic quirks
#ifndef AtlasPropertiesWidget
#define AtlasPropertiesWidget atlas_properties_widget
#endif


// fwd
class QFileDialog;
class QLabel;
namespace rpg { class atlas; }
class Ui_atlas_properties_widget;


/**
 * show and modify the properties of an atlas
 */
class atlas_properties_widget : public QWidget {


    Q_OBJECT


public:


    /**
     * ctor
     *
     * @param   cParent     parent widget
     */
    atlas_properties_widget(QWidget * cParent = nullptr);


    /**
     * dtor
     */
    virtual ~atlas_properties_widget();


    /**
     * check if the current widget data represents a valid atlas
     *
     * @return  true, if we have valid atlas data
     */
    bool valid();


signals:


    /**
     * atlas data has changed
     */
    void changed();


public slots:


    /**
     * clear all widget data
     */
    void clear();


private slots:


    /**
     * some edit field has changed
     *
     * @param   sText       the new text (ignored)
     */
    void text_changed(QString const & sText);


    /**
     * let the user select an image file
     */
    void select_image_file();


private:


    rpg::atlas * m_cAtlas;                  /**< the current atlas */

    Ui_atlas_properties_widget * ui;        /**< user elements */

    QFileDialog * m_cFileDialog;            /**< for opening an image */
    QLabel * m_cLblPicture;                 /**< the atlas picture widget */

};


#endif

