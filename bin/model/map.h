/*
 * map.h
 *
 * A single RPG map
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


#ifndef __MODEL_MAP_H
#define __MODEL_MAP_H


// ------------------------------------------------------------
// incs


#include <set>


// Qt
#include <QObject>


// ------------------------------------------------------------
// decl


namespace rpg {

    
/**
 * a single rpg map
 */
class map : public QObject {


    Q_OBJECT


public:


    /**
     * ctor
     *
     * @param   cParent         parent object
     * @param   sName           name of map
     * @param   sDescription    description of map
     */
    map(QObject * cParent = nullptr, QString const & sName = "<unnamed>", QString const & sDescription = "") 
        : QObject(cParent), m_sName(sName), m_sDescription(sDescription) {};


    /**
     * copy ctor
     */
    map(map const &) = delete;


    /**
     * dtor
     */
    ~map();


    /**
     * < operator
     * 
     * sort criteria based on map's name
     *
     * @param   rhs     right hand side
     * @return  bool if (*this) < rhs
     */
    bool operator<(map const & rhs) const { return name() < rhs.name(); };


    /**
     * get the description of the map
     * 
     * @return  the map' description
     */
    QString const & description() const { return m_sDescription; };


    /**
     * get the name of the map
     * 
     * @return  the map' name
     */
    QString const & name() const { return m_sName; };


    /**
     * set the description of the map
     * 
     * @param   sDescription        the new description of the map
     */
    void set_description(QString const & sDescription) { 
        m_sDescription = sDescription; 
        emit changed(this); 
    };


    /**
     * set the name of the map
     * 
     * @param   sName               the new name of the map
     */
    void set_name(QString const & sName) { 
        m_sName = sName; 
        emit changed(this); 
    };


signals:


    /**
     * data on the map changed
     *
     * @param   cMap        the map changed
     */
    void changed(rpg::map * cMap);


private:


    QString m_sName;            /**< map name */
    QString m_sDescription;     /**< map description */

};


/**
 * a set of maps
 */
typedef std::set<rpg::map *> mapset;


}


#endif

