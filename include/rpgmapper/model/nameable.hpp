/*
 * nameable.h
 *
 * A nameable object knows its name
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


#ifndef MODEL_NAMEABLE_H
#define MODEL_NAMEABLE_H


// ------------------------------------------------------------
// incs


#include <string>

// rpgmapper
#include "changeable.hpp"


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A nameable object knows its name
 */
class Nameable : public Changeable {


public:


    /**
     * ctor
     */
    Nameable();


    /**
     * dtor
     */
    virtual ~Nameable();


    /**
     * Get the name.
     *
     * @return  the name
     */
    std::string const & name() const;


    /**
     * Set the name.
     *
     * @param   sName       the new name
     */
    void name(std::string sName);


private:


    std::string m_sName;

};


}
}


#endif
