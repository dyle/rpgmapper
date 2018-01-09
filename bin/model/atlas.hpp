/*
 * atlas.h
 *
 * A RPG atlas
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


#ifndef MODEL_ATLAS_H
#define MODEL_ATLAS_H


// ------------------------------------------------------------
// incs

#include <memory>

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
     * Check if the data needs to be saved.
     *
     * @return  true, if the data has to be saved.
      */
    bool needSave() const;


    /**
     * return all the regions managed in this region
     *
     * @return  all regions of this region
     */
    Regions const & regions() const;


    /**
     * Enforce that no save is yet needed.
      */
    void resetSave();


private:


    class Atlas_data;                               /**< internal data type */
    std::shared_ptr<Atlas::Atlas_data> d;           /**< internal data instance */

};


}
}


#endif
