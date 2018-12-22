/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <map>
#include <tuple>

#include <rpgmapper/resource/resource_type.hpp>


QString rpgmapper::model::resource::getResourcePrefixForType(rpgmapper::model::resource::ResourceType type) {
    
    static std::map<ResourceType, QString> const prefixes {
        {ResourceType::unknown, "/???"},
        {ResourceType::background, "/backgrounds"},
        {ResourceType::colorpalette, "/colorpalettes"},
        {ResourceType::shape, "/shapes"}
    };
    
    auto const & pair = prefixes.find(type);
    if (pair == prefixes.end()) {
        return getResourcePrefixForType(ResourceType::unknown);
    }
    
    return (*pair).second;
}


QString rpgmapper::model::resource::getResourceTypeName(rpgmapper::model::resource::ResourceType type, bool plural) {
    
    using PluralName = QString;
    using SingularName = QString;
    static std::map<ResourceType, std::tuple<PluralName, SingularName>> const names {
        {ResourceType::unknown, {"<Unknown resources>", "<Unknown resource>"}},
        {ResourceType::background, {"Backgrounds", "Background"}},
        {ResourceType::colorpalette, {"Colorpalettes", "Colorpalette"}},
        {ResourceType::shape, {"Shapes", "Shape"}},
    };
    
    auto const & pair = names.find(type);
    if (pair == names.end()) {
        return getResourceTypeName(ResourceType::unknown, plural);
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
