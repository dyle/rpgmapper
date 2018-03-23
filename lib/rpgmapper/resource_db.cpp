/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/resource_db.hpp>

using namespace rpgmapper::model;


void ResourceDB::addResource(QString name, QByteArray const & data) {
    addResource(ResourcePointer{new rpgmapper::model::Resource{std::move(name), data}});
}


void ResourceDB::addResource(ResourcePointer resource) {
    if (resource->getData().isEmpty()) {
        throw std::runtime_error("Refused to add empty resource to resource DB.");
    }
    resources[resource->getHash()] = resource;
}
