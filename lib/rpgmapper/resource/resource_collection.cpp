/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/resource/resource.hpp>
#include <rpgmapper/resource/resource_collection.hpp>

using namespace rpgmapper::model::resource;


void ResourceCollection::addResource(ResourcePointer resource) {
    if (resource->getData().isEmpty()) {
        throw std::runtime_error("Refused to add empty resource to resource DB.");
    }
    resources[resource->getPath()] = resource;
}


std::set<QString> ResourceCollection::getPaths() const {
    
    std::set<QString> paths;
    
    std::for_each(resources.begin(),
                  resources.end(),
                  [&] (auto p) { paths.insert(p.first); });
    
    return paths;
}
