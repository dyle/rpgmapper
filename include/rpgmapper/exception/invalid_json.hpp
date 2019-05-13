/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_EXCEPTION_INVALID_JSON_HPP
#define RPGMAPPER_MODEL_EXCEPTION_INVALID_JSON_HPP

#include <stdexcept>


namespace rpgmapper::model::exception {


/**
 * An invalid json instance was presented.
 */
class invalid_json : public std::invalid_argument {

public:
    
    /**
     * Constructor
     *
     * @param   what        the exception message
     */
    invalid_json(char const * what) : std::invalid_argument(what) {}
};


}


#endif
