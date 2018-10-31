/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_EXCEPTION_INVALID_SESSION_HPP
#define RPGMAPPER_MODEL_EXCEPTION_INVALID_SESSION_HPP

#include <stdexcept>


namespace rpgmapper {
namespace model {
namespace exception {


/**
 * An invalid session was presented where a valid one has been required.
 */
class invalid_session : public std::invalid_argument {

public:
    
    /**
     * Constructor
     */
    invalid_session() : std::invalid_argument("Invalid session.") {}
    
};


}
}
}


#endif
