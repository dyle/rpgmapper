/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_EXCEPTION_INVALID_REGIONNAME_HPP
#define RPGMAPPER_MODEL_EXCEPTION_INVALID_REGIONNAME_HPP

#include <stdexcept>


namespace rpgmapper {
namespace model {
namespace exception {


/**
 * An invalid region was presented where a valid one has been required.
 */
class invalid_regionname : public std::invalid_argument {

public:
    
    /**
     * Constructor
     */
    invalid_regionname() : std::invalid_argument("Invalid region name given.") {}
    
};


}
}
}


#endif
