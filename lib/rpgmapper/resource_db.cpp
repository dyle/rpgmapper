/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/resource_collection.hpp>
#include <rpgmapper/resource_db.hpp>
#include <rpgmapper/session.hpp>


using namespace rpgmapper::model;


/**
 * Collect all resources from a DB with a given prefix.
 *
 * @param   collection      the collection of found resources.
 * @param   db              the database to search.
 * @pram    prefix          the prefix to match.
 */
static void collectResourcesWithPrefix(std::set<QString> & collection,
        ResourceCollectionPointer const & db,
        QString const & prefix);


/**
 * Search for a resource with a given name.
 *
 * @param   db          the DB to search.
 * @param   name        the name of the resource to search.
 * @return  a found resource (maybe holding nullptr if not found).
 */
static ResourcePointer findResource(ResourceCollectionPointer db, QString const & name);


ResourceCollectionPointer ResourceDB::getLocalResources() {
    return Session::getCurrentSession()->getAtlas()->getResources();
}


ResourcePointer ResourceDB::getResource(QString path) {
    
    ResourcePointer resource = findResource(getLocalResources(), path);
    
    if (!resource) {
        resource = findResource(getUserResources(), path);
    }
    
    if (!resource) {
        resource = findResource(getSystemResources(), path);
    }
    
    return resource;
}


std::set<QString> ResourceDB::getResources(QString prefix) {
    
    std::set<QString> resources;
    
    collectResourcesWithPrefix(resources, getLocalResources(), prefix);
    collectResourcesWithPrefix(resources, getUserResources(), prefix);
    collectResourcesWithPrefix(resources, getSystemResources(), prefix);
    
    return resources;
}


ResourceCollectionPointer ResourceDB::getSystemResources() {
    static ResourceCollectionPointer systemResources;
    if (!systemResources) {
        systemResources = ResourceCollectionPointer{new ResourceCollection};
    }
    return systemResources;
}


ResourceCollectionPointer ResourceDB::getUserResources() {
    static ResourceCollectionPointer userResources;
    if (!userResources) {
        userResources = ResourceCollectionPointer{new ResourceCollection};
    }
    return userResources;
}


void collectResourcesWithPrefix(std::set<QString> & collection,
        ResourceCollectionPointer const & db,
        QString const & prefix) {
    
    auto paths = db->getPaths();
    for (auto const & path : paths) {
        if (path.startsWith(prefix)) {
            collection.insert(path);
        }
    }
}


ResourcePointer findResource(ResourceCollectionPointer db, QString const & path) {
    
    ResourcePointer resource;
    auto & resources = db->getResources();
    auto iter = resources.find(path);
    if (iter != resources.end()) {
        resource = (*iter).second;
    }
    return resource;
}
