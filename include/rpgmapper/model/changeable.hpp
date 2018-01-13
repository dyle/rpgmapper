/*
 * changeable.hpp
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


#ifndef MODEL_CHANGEABLE_HPP
#define MODEL_CHANGEABLE_HPP


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A changeable object knows if its inner state has been changed.
 */
class Changeable {


public:


    /**
     * ctor
     */
    Changeable();


    /**
     * dtor
     */
    virtual ~Changeable();


    /**
     * state if the object instance data has changed
     *
     * @return  true if the object instance data has changed
     */
    bool changed() const;


    /**
     * set the object instance data changed flag
     *
     * @param   bChanged        the new object instance data changed flag
     */
    void changed(bool bChanged);


    /**
     * state if the object instance data has changed or of one of its aggregated objects.
     *
     * @return  true if the object instance data or one of its aggregated objects has changed
     */
    virtual bool changedAccumulated() const;


    /**
     * applies the new changed flag to this instance and all aggregated objects
     *
     * @param   bChanged        the new object instance data changed flag for all objects
     */
    virtual void changedAccumulated(bool bChanged);


private:


    bool m_bChanged;

};


}
}


#endif
