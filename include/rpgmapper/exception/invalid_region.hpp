/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_EXCEPTION_INVALID_REGION_HPP
#define RPGMAPPER_MODEL_EXCEPTION_INVALID_REGION_HPP

#include <stdexcept>


namespace rpgmapper::model::exception {


/**
 * An invalid region was presented where a valid one has been required.
 */
class invalid_region : public std::invalid_argument {

public:

    /**
     * Constructor
     */
    invalid_region() : std::invalid_argument("Invalid region.") {}
};


}


#endif
