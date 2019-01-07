/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_REGION_NAME_VALIDATOR_HPP
#define RPGMAPPER_MODEL_REGION_NAME_VALIDATOR_HPP

#include <QString>


namespace rpgmapper::model {


/**
 * Validates an region name.
 */
class RegionNameValidator {

public:
    
    /**
     * Constructor.
     */
    RegionNameValidator() = delete;
    
    /**
     * Validates a give name of a map.
     */
    static bool isValid(QString name);
};


}


#endif
