/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_EXCEPTION_INVALID_FIELD_HPP
#define RPGMAPPER_MODEL_EXCEPTION_INVALID_FIELD_HPP

#include <stdexcept>


namespace rpgmapper::model::exception {


/**
 * An invalid field has been given.
 */
class invalid_field : public std::invalid_argument {

public:
    
    /**
     * Constructor
     */
    invalid_field() : std::invalid_argument("Invalid field.") {}
};


}


#endif
