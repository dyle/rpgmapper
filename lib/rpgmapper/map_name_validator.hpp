/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_MAP_NAME_VALIDATOR_HPP
#define RPGMAPPER_MODEL_MAP_NAME_VALIDATOR_HPP

#include <QString>


namespace rpgmapper {
namespace model {


/**
 * Validates a map name.
 */
class MapNameValidator {
        
public:
    
    /**
     * Constructor.
     */
    MapNameValidator() = delete;
    
    /**
     * Validates a give name of a map.
     */
    static bool isValid(QString name);
};


}
}


#endif
