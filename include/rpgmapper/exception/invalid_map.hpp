/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_EXCEPTION_INVALID_MAP_HPP
#define RPGMAPPER_MODEL_EXCEPTION_INVALID_MAP_HPP

#include <stdexcept>


namespace rpgmapper {
namespace model {
namespace exception {


/**
 * An invalid map was presented where a valid one has been required.
 */
class invalid_map : public std::invalid_argument {

public:
    
    /**
     * Constructor
     */
    invalid_map() : std::invalid_argument("Invalid map.") {}
    
};


}
}
}


#endif
