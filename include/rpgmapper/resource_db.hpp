/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_RESOURCE_DB_HPP
#define RPGMAPPER_RESOURCE_DB_HPP

#include <map>

#include <rpgmapper/resource_pointer.hpp>


namespace rpgmapper {
namespace model {


/**
 * This class represents a resource database.
 */
class ResourceDB {
    
    /**
     * The resources an object of this class manages.
     */
    std::map<QString, ResourcePointer> resources;

public:

    /**
     * Constructor.
     */
    ResourceDB() = default;

    /**
     * Copy constructor.
     */
    ResourceDB(ResourceDB const &) = delete;

    /**
     * Destructor.
     */
    ~ResourceDB() = default;

    /**
     * Adds a BLOB with a name to the resource database.
     *
     * @param   name    the name of the BLOB
     * @param   data    the BLOB.
     */
    void addResource(QString name, QByteArray const & data);
    
    /**
     * Adds an existing resource to the database.
     *
     * @param   resource    the resource to add.
     */
    void addResource(QSharedPointer<Resource> resource);

    /**
     * Gets a BLOB based on a hash value.
     *
     * @param   hash        the hash value.
     * @return  The BLOB as registered with this hash value.
     */
    QByteArray const & getData(QString hash) const;

    /**
     * Gets a BLOB based on a hash value (const version).
     *
     * @param   hash        the hash value.
     * @return  The BLOB as registered with this hash value.
     */
    ResourcePointer const & getResource(QString hash) const;
    
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


#endif
