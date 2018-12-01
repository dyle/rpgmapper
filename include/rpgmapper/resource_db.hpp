/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_RESOURCE_DB_HPP
#define RPGMAPPER_RESOURCE_DB_HPP

#include <rpgmapper/resource_collection_pointer.hpp>
#include <rpgmapper/resource_pointer.hpp>


namespace rpgmapper {
namespace model {


/**
 * This is the place where all resources in the RPGMapper are managed.
 */
class ResourceDB {
    
    /**
     * All loaded resources loaded from system files.
     */
    static ResourceCollectionPointer systemResources;
    
    /**
     * All loaded resources loaded from user files.
     */
    static ResourceCollectionPointer userResources;

public:
    
    /**
     * Constructor
     */
    ResourceDB() = delete;

    /**
     * Gets the local, atlas resource (loaded from an atlas file)
     *
     * @return  the resources found in the atlas file.
     */
    static ResourceCollectionPointer getLocalResources();
    
    /**
     * Gets a specific resource with a certain name.
     *
     * This is the search order for the given named resource:
     *  1. local, atlas files.
     *  2. user files.
     *  3. system files.
     *
     * @param   name        the name of the resource
     * @return  a resource (maybe invalid if not found)
     */
    static ResourcePointer getResource(QString name);
    
    /**
     * Collects all resources having a certain name prefix.
     *
     * This is the search order for resources:
     *  1. local, atlas files.
     *  2. user files.
     *  3. system files.
     *
     * @param   prefix      the prefix of the name (e.g. '/backgrounds')
     * @return  a list of resources names found.
     */
    static std::list<QString> getResources(QString prefix);
    
    /**
     * Gets the system resources.
     *
     * @return  the resources found in the installation.
     */
    static ResourceCollectionPointer getSystemResources();
    
    /**
     * Gets the user defined resources.
     *
     * @return  the resources found in the user folder.
     */
    static ResourceCollectionPointer getUserResources();
};


}
}


#endif
