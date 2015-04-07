/*
 * atlas.h
 *
 * A RPG atlas
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
    atlas(QObject * cParent, std::string const & sName = "<unnamed atlas>", std::string const & sDescription = "");


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
     */
    void add_map(rpg::map * cMap);


    /**
     * delete a map from the atlas
     *
     * @param   sName       name of the map to delete
     */
    void del_map(std::string & sName);


    /**
     * get the description of the atlas
     * 
     * @return  the atlas' description
     */
    std::string const & description() const { return m_sDescription; };


    /**
     * return a map
     *
     * @param   name of the map to retrieve
     * @return  the map found (or nullptr if not)
     */
    rpg::map * find(std::string const & sName);


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
    rpg::maps const & maps() const { return m_cMaps; };


    /**
     * get the name of the atlas
     * 
     * @return  the atlas' name
     */
    std::string const & name() const { return m_sName; };


    /**
     * set the description of the atlas
     * 
     * @param   sDescription        the new description of the atlas
     */
    void set_description(std::string const & sDescription) { 
        m_sDescription = sDescription; 
        m_bUnsaved = true; 
        emit modified(); 
    };


    /**
     * set the atlas image
     *
     * @param   cImage the new atlas image
     */
    void set_image(QImage & cImage) { m_cImage = cImage; emit modified(); };


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
    void map_added(std::string const sGroupName, rpg::map * cMap);


private slots:


    /**
     * a map has changed
     *
     * @param   cMap        the map changed
     */
    void map_changed(rpg::map * cMap);


    /**
     * a map has been destroyed
     *
     * @param   cMap        the map destroyed
     */
    void map_destroyed(QObject * cMap);


private:


    std::string m_sName;            /**< atlas name */
    std::string m_sDescription;     /**< atlas description */

    rpg::maps m_cMaps;              /**< all map groups we know */

    bool m_bUnsaved;                /**< new data needs to be saved */

    QImage m_cImage;                /**< the atlas image */

};


}


#endif

