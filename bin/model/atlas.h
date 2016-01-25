/*
 * atlas.h
 *
 * A RPG atlas
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


#ifndef __MODEL_ATLAS_H
#define __MODEL_ATLAS_H


// ------------------------------------------------------------
// incs

#include <map>
#include <set>
#include <stdexcept>

// Qt
#include <QImage>
#include <QObject>

// rpgmapper
#include "map.h"
#include "maps.h"


// ------------------------------------------------------------
// decl


namespace rpg {


/**
 * a single atlas holds maps
 */
class atlas : public QObject {


    Q_OBJECT


public:


    /**
     * ctor
     *
     * @param   cParent         parent object
     * @param   sName           name of atlas
     * @param   sDescription    description of atlas
     */
    atlas(QObject * cParent, QString const & sName = "<unnamed atlas>", QString const & sDescription = "");


    /**
     * copy ctor
     */
    atlas(atlas const &) = delete;


    /**
     * dtor
     */
    ~atlas();


    /**
     * add a map to the atlas
     *
     * @param   cMap        the map to add
     * @param   sGroup      the map group to add the map to
     */
    void add_map(rpg::map * cMap, QString sGroup = "<default>");


    /**
     * delete a map from the atlas
     *
     * @param   sName       name of the map to delete
     */
    void del_map(QString & sName);


    /**
     * get the description of the atlas
     * 
     * @return  the atlas' description
     */
    QString const & description() const { return m_sDescription; };


    /**
     * return the filename of the atlas on disk
     *
     * @return  the name of the atlas file
     */
    QString const & filename() const { return m_sFileName; };


    /**
     * return a map
     *
     * @param   name of the map to retrieve
     * @return  the map found (or nullptr if not)
     */
    rpg::map * find(QString const & sName);


    /**
     * return a map
     *
     * @param   name of the map to retrieve
     * @return  the map found (or nullptr if not)
     */
    rpg::map const * find(QString const & sName) const;


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
     * return the maps
     *
     * @return  the maps
     */
    rpg::maps & maps() { return m_cMaps; };


    /**
     * return the maps
     *
     * @return  the maps
     */
    rpg::maps const & maps() const { return m_cMaps; };


    /**
     * get the name of the atlas
     * 
     * @return  the atlas' name
     */
    QString const & name() const { return m_sName; };


    /**
     * set the description of the atlas
     * 
     * @param   sDescription        the new description of the atlas
     */
    void set_description(QString const & sDescription) { 
        if (sDescription == m_sDescription) return;
        m_sDescription = sDescription; 
        m_bUnsaved = true; 
        emit modified(); 
    };


    /**
     * set a new filename on disk
     *
     * @param   sFileName       the new filename on disk
     */
    void set_filename(QString const & sFileName) {
        if (sFileName == m_sFileName) return;
        m_sFileName = m_sFileName;
        m_bUnsaved = true;
        emit modified();
    }


    /**
     * set the atlas image
     *
     * @param   cImage the new atlas image
     */
    void set_image(QImage & cImage) { 
        m_cImage = cImage; 
        emit modified(); 
    };


    /**
     * check if there is new data to be saved to disk yet
     * 
     * @return  true, if new data has not yet been saved
     */
    bool unsaved() const { return m_bUnsaved; };


signals:


    /**
     * atlas data has been modified
     */
    void modified();


    /**
     * a new map has been added to the atlas
     *
     * @param   sGroupName      name of group where added
     * @param   cMap            the new map
     */
    void map_added(QString const sGroupName, rpg::map * cMap);


private slots:


    /**
     * a map has changed
     *
     * @param   cMap        the map changed
     */
    void map_changed(rpg::map * cMap);


private:


    QString m_sName;            /**< atlas name */
    QString m_sDescription;     /**< atlas description */
    QString m_sFileName;        /**< the filename of the atlas on disk */

    rpg::maps m_cMaps;          /**< all map groups we know */

    bool m_bUnsaved;            /**< new data needs to be saved */

    QImage m_cImage;            /**< the atlas image */

};


}


#endif

