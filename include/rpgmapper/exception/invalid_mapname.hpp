/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_EXCEPTION_INVALID_MAPNAME_HPP
#define RPGMAPPER_MODEL_EXCEPTION_INVALID_MAPNAME_HPP

#include <stdexcept>


namespace rpgmapper::model::exception {


/**
 * An invalid map name was presented where a valid one has been required.
 */
class invalid_mapname : public std::invalid_argument {

public:
    
    /**
     * Constructor
     */
    invalid_mapname() : std::invalid_argument("Invalid map name given.") {}
};


}


#endif
