/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/resource_db.hpp>

using namespace rpgmapper::model;


void ResourceDB::addResource(QString name, QByteArray const & data) {
    addResource(QSharedPointer<Resource>{new rpgmapper::model::Resource{std::move(name), data}});
}


void ResourceDB::addResource(QSharedPointer<Resource> resource) {
    if (resource->getData().isEmpty()) {
        throw std::runtime_error("Refused to add empty resource to resource DB.");
    }
    resources[resource->getHash()] = resource;
}


QByteArray const & ResourceDB::getData(QString hash) const {
    return getResource(std::move(hash))->getData();
}


QSharedPointer<Resource> const & ResourceDB::getResource(QString hash) const {
    
    static QSharedPointer<Resource> emptyResource{new Resource{QString::null, QByteArray{}}};
    
    auto pair = resources.find(hash);
    if (pair == resources.end()) {
        return emptyResource;
    }
    
    return (*pair).second;
}
