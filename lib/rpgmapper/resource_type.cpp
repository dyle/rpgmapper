/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/resource_type.hpp>


QString rpgmapper::model::getResourcePrefixForType(rpgmapper::model::ResourceType type) {
    
    QString prefix{"/"};
    
    switch (type) {
        
        case rpgmapper::model::ResourceType::background:
            prefix = "/backgrounds";
            break;
        
        case rpgmapper::model::ResourceType::colorpalette:
            prefix = "/colorpalettes";
            break;
            
        case rpgmapper::model::ResourceType::shape:
            prefix = "/shapes";
            break;
            
        default:
            break;
    }
    
    return prefix;
}
