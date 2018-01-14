/*
 * atlas.hpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
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


#ifndef MODEL_ATLAS_HPP
#define MODEL_ATLAS_HPP


// ------------------------------------------------------------
// incs

#include <memory>

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

// rpgmapper
#include "nameable.hpp"
#include "region.hpp"


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A single atlas holds regions with maps each.
 *
 * Note: copy an Atlas instance is shallow. For a deep copy use the "clone()" method.
 */
class Atlas : public Nameable {


public:


    /**
     * ctor
     */
    Atlas();


    /**
     * dtor
     */
    virtual ~Atlas();


    /**
     * check if the atlas or any aggregated objects changed.
     *
     * @return  true if the atlas or any dependent object changed.
     */
    virtual bool changedAccumulated() const;


    /**
     * set the change flag of the atlas and any dependent objects
     *
     * @param   bChanged        the new changed information
     */
    virtual void changedAccumulated(bool bChanged);


    /**
     * make a deep copy of this Atlas
     *
     * @return  a new deep copied instance
     */
    Atlas clone() const;


    /**
     * Creates a new region to this atlas
     *
     * @return  a reference to the new region
     */
    Region & createRegion();


    /**
     * create a json string form this Atlas
     *
     * @param   eJsonFormat     the format for representation
     * @return  a string holding the atlas in json format
     */
    QString json(QJsonDocument::JsonFormat eJsonFormat = QJsonDocument::Indented) const;


    /**
     * load the atlas from json
     *
     * @param   cJSON       the json instance to load from
     */
    void load(QJsonObject const & cJSON) override;


    /**
     * get region by id
     *
     * @param   nId         id of the region to get
     * @return  region instance
     */
    Region & region(Region::id_t nId);


    /**
     * get region by id
     *
     * @param   nId         id of the region to get
     * @return  region instance
     */
    Region const & region(Region::id_t nId) const;


    /**
     * return all the regions managed by this atlas
     *
     * @return  all regions of this atlas
     */
    Regions const & regions() const;


    /**
     * save the atlas to json
     *
     * @param   cJSON       the json instance to save to
     */
    void save(QJsonObject & cJSON) const override;


private:


    /**
     * reset the atlas to empty state
     */
    void clear();


    class Atlas_data;                               /**< internal data type */
    std::shared_ptr<Atlas::Atlas_data> d;           /**< internal data instance */

};


}
}


#endif
