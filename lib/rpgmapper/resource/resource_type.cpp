/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <map>
#include <tuple>

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
    
    using PluralName = QString;
    using SingularName = QString;
    static std::map<rpgmapper::model::resource::ResourceType, std::tuple<PluralName, SingularName>> const names = {
        {rpgmapper::model::resource::ResourceType::unknown, {"<Unknown resources>", "<Unknown resource>"}},
        {rpgmapper::model::resource::ResourceType::background, {"Backgrounds", "Background"}},
        {rpgmapper::model::resource::ResourceType::colorpalette, {"Colorpalettes", "Colorpalette"}},
        {rpgmapper::model::resource::ResourceType::shape, {"Shapes", "Shape"}},
    };
    
    auto const & pair = names.find(type);
    if (pair == names.end()) {
        return getResourceTypeName(rpgmapper::model::resource::ResourceType::unknown, plural);
    }
    
    auto const & name = (*pair).second;
    return plural ? std::get<0>(name) : std::get<1>(name);
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
