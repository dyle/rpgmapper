/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <map>

#include <rpgmapper/resource/resource_type.hpp>


QString rpgmapper::model::resource::getResourcePrefixForType(rpgmapper::model::resource::ResourceType type) {
    
    QString prefix{"/"};
    
    switch (type) {
    
        case rpgmapper::model::resource::ResourceType::unknown:
            prefix = "/???";
            break;
    
        case rpgmapper::model::resource::ResourceType::background:
            prefix = "/backgrounds";
            break;
        
        case rpgmapper::model::resource::ResourceType::colorpalette:
            prefix = "/colorpalettes";
            break;
            
        case rpgmapper::model::resource::ResourceType::shape:
            prefix = "/shapes";
            break;
    }
    
    return prefix;
}


QString rpgmapper::model::resource::getResourceTypeName(rpgmapper::model::resource::ResourceType type, bool plural) {
    
    QString name;
    
    switch (type) {
        
        case rpgmapper::model::resource::ResourceType::unknown:
            name = plural ? "<Unknown resources>" : "<Unknown resource>";
            break;
        
        case rpgmapper::model::resource::ResourceType::background:
            name = plural ? "Backgrounds" : "Backhground";
            break;
        
        case rpgmapper::model::resource::ResourceType::colorpalette:
            name = plural ? "Colorpalettes" : "Colorpalette";
            break;
        
        case rpgmapper::model::resource::ResourceType::shape:
            name = plural ? "Shapes" : "Shape";
            break;
    }
    
    return name;
}


rpgmapper::model::resource::ResourceType rpgmapper::model::resource::suggestResourceTypeByPath(QString path) {
    
    static std::map<QString, ResourceType> knownPrefix;
    if (knownPrefix.empty()) {
        knownPrefix.emplace(getResourcePrefixForType(ResourceType::background), ResourceType::background);
        knownPrefix.emplace(getResourcePrefixForType(ResourceType::colorpalette), ResourceType::colorpalette);
        knownPrefix.emplace(getResourcePrefixForType(ResourceType::shape), ResourceType::shape);
    }
    
    auto prefix = path.left(path.indexOf('/', 1));
    auto pair = knownPrefix.find(prefix);
    if (pair == knownPrefix.end()) {
        return ResourceType::unknown;
    }
    
    return (*pair).second;
}
