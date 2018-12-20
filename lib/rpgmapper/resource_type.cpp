/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/resource_type.hpp>


QString rpgmapper::model::getResourcePrefixForType(rpgmapper::model::ResourceType type) {
    
    QString prefix{"/"};
    
    switch (type) {
    
        case rpgmapper::model::ResourceType::unknown:
            prefix = "/???";
            break;
    
        case rpgmapper::model::ResourceType::background:
            prefix = "/backgrounds";
            break;
        
        case rpgmapper::model::ResourceType::colorpalette:
            prefix = "/colorpalettes";
            break;
            
        case rpgmapper::model::ResourceType::shape:
            prefix = "/shapes";
            break;
    }
    
    return prefix;
}


QString rpgmapper::model::getResourceTypeName(rpgmapper::model::ResourceType type, bool plural) {
    
    QString name;
    
    switch (type) {
        
        case rpgmapper::model::ResourceType::unknown:
            name = plural ? "<Unknown resources>" : "<Unknown resource>";
            break;
        
        case rpgmapper::model::ResourceType::background:
            name = plural ? "Backgrounds" : "Backhground";
            break;
        
        case rpgmapper::model::ResourceType::colorpalette:
            name = plural ? "Colorpalettes" : "Colorpalette";
            break;
        
        case rpgmapper::model::ResourceType::shape:
            name = plural ? "Shapes" : "Shape";
            break;
    }
    
    return name;
}
