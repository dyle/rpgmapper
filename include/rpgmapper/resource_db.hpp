/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_RESOURCE_DB_HPP
#define RPGMAPPER_RESOURCE_DB_HPP


#include <map>

#include <rpgmapper/resource.hpp>


namespace rpgmapper {
namespace model {


class ResourceDB;
using ResourceDBPointer = QSharedPointer<ResourceDB>;

using Resources = std::map<QString, rpgmapper::model::ResourcePointer>;

class ResourceDB {

     Resources resources;

public:

    ResourceDB() = default;

    ResourceDB(ResourceDB const &) = delete;

    ~ResourceDB() = default;

    void addResource(QString name, QByteArray const & data);

    void addResource(ResourcePointer resource);

    Resources const & getResources() const {
        return resources;
    }
};


}
}


#endif
