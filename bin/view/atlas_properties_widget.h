/*
 * atlas_properties_widget.h
 *
 * Show and modify properties of an atlas (as a custom widget)
 * 
 * Copyright (C) 2015, 2016 Oliver Maurhart, <dyle@dyle.org>
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

// rpgmapper
#include "view/clickable_label.h"


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
    QImage & image() { return m_cImage; };


    /**
     * get the atlas image
     *
     * @return  the atlas image
     */
    QImage const & image() const { return m_cImage; };


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
     * set the atlas description
     *
     * @param   sDescription        the new description
     */
    void set_description(QString sDescription);


    /**
     * set the atlas image
     *
     * @param   cImage the new atlas image
     */
    void set_image(QImage & cImage) { m_cImage = cImage; };


    /**
     * set the path to the atlas image
     *
     * @param   sImagePath      the new image path
     */
    void set_image_path(QString sImagePath);


    /**
     * set the atlas name
     *
     * @param   sName           the new atlas name
     */
    void set_name(QString sName);


    /**
     * check if the current widget data represents a valid atlas
     *
     * @return  true, if we have valid atlas data
     */
    bool valid() const;


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
    QImage m_cImage;                        /**< the atlas image */

    Ui_atlas_properties_widget * ui;        /**< user elements */

    QFileDialog * m_cFileDialog;            /**< for opening an image */
    clickable_label * m_cLblPicture;        /**< the atlas picture widget */
    QString m_sImagePath;                   /**< path to loaded image */

};


#endif

