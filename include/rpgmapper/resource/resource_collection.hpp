/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_RESOURCE_RESOURCE_COLLECTION_HPP
#define RPGMAPPER_MODEL_RESOURCE_RESOURCE_COLLECTION_HPP

#include <map>
#include <set>

#include <QString>

#include <rpgmapper/resource/resource_pointer.hpp>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * This class represents a set of resources.
 */
class ResourceCollection {
    
    /**
     * The resources an object of this class manages by paths.
     */
    std::map<QString, ResourcePointer> resources;

public:

    /**
     * Constructor.
     */
    ResourceCollection() = default;

    /**
     * Copy constructor.
     */
    ResourceCollection(ResourceCollection const &) = delete;

    /**
     * Destructor.
     */
    ~ResourceCollection() = default;

    /**
     * Adds a BLOB with a name to the resource database.
     *
     * @param   path    the path to the BLOB
     * @param   data    the BLOB.
     */
    void addResource(QString path, QByteArray const & data);
    
    /**
     * Adds an existing resource to the database.
     *
     * @param   resource    the resource to add.
     */
    void addResource(QSharedPointer<Resource> resource);
    
    /**
     * Returns the paths of all resources in this collection.
     *
     * @return  a set of resource paths.
     */
    std::set<QString> getPaths() const;

    /**
     * Gets all known resources.
     *
     * @return  all resources we know in this database.
     */
    std::map<QString, ResourcePointer> const & getResources() const {
        return resources;
    }
};


}
}
}


#endif
