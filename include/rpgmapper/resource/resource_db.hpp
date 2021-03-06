/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_RESOURCE_DB_HPP
#define RPGMAPPER_MODEL_RESOURCE_RESOURCE_DB_HPP

#include <set>

#include <QString>

#include <rpgmapper/resource/resource_collection_pointer.hpp>
#include <rpgmapper/resource/resource_type.hpp>
#include <rpgmapper/resource/resource_pointer.hpp>


namespace rpgmapper::model::resource {


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
     * Gets a specific resource with a certain path.
     *
     * This is the search order for the given named resource:
     *  1. local, atlas files.
     *  2. user files.
     *  3. system files.
     *
     * @param   path        the path to the resource
     * @return  a resource (maybe nullptr if not found)
     */
    static ResourcePointer getResource(QString path);
    
    /**
     * Collects all resources having a certain path prefix.
     *
     * This is the search order for resources:
     *  1. local, atlas files.
     *  2. user files.
     *  3. system files.
     *
     * @param   prefix      the prefix of the path (e.g. '/backgrounds')
     * @return  a list of resources names found.
     */
    static std::set<QString> getResources(QString prefix);
    
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


#endif
