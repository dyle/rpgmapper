/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_BASE_HPP
#define RPGMAPPER_MODEL_BASE_HPP

#include <ostream>
#include <string>
#include <sstream>


namespace rpgmapper::model {


/**
 * The base class of all rpgmapper objects.
 */
class Base {

public:
    
    /**
     * Constructor.
     */
    Base() = default;
    
    /**
     * Returns a JSON string of this object by casting it to std::string.
     *
     * @return  a human readable JSON string of this object.
     */
    explicit operator std::string() const {
        std::stringstream ss;
        ss << "{" << json() << "}";
        return ss.str();
    }

protected:
    
    /**
     * Collects all fields of this object as JSON members.
     *
     * @return  a JSON string of all member fields.
     */
    virtual std::string json() const = 0;
};


}


/**
 * Stream a base rpgmapper object.
 *
 * @param   s       the out stream instance.
 * @param   o       the object to stream
 */
inline std::ostream & operator<<(std::ostream & s, rpgmapper::model::Base const & o) {
    return s << static_cast<std::string>(o);
}


#endif
