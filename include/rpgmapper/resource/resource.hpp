/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_RESOURCE_HPP
#define RPGMAPPER_RESOURCE_HPP

#include <QByteArray>
#include <QMimeType>
#include <QSharedPointer>
#include <QString>

#include <rpgmapper/resource/resource_type.hpp>


namespace rpgmapper {
namespace model {
namespace resource {


/**
 * A resource is a named BLOB.
 */
class Resource {

    QByteArray data;        /**< The Blob. */
    QString name;           /**< The name associated with the BLOB. */
    QString path;           /**< The path relative to the root resource base to the BLOB. */

public:
    
    /**
     * Constructor.
     *
     * @param   path        path to the BLOB.
     * @param   data        the BLOB.
     */
    Resource(QString path, QByteArray const & data);

    /**
     * Copy constructor.
     */
    Resource(Resource const &) = delete;

    /**
     * Gets the BLOB.
     *
     * @return  the BLOB.
     */
    QByteArray const & getData() const {
        return data;
    }

    /**
     * Gets the name of the BLOB.
     *
     * @return  the name of the BLOB.
     */
    QString const & getName() const {
        return name;
    }

    /**
     * Creates a somehow unique hash value of the BLOB.
     *
     * @return  A string holding the hash value of the BLOB.
     */
    QString getHash() const {
        return getSHA256(getData());
    }
    
    /**
     * Creates a somehow unique hash value of the BLOB.
     *
     * @param   data        a BLOB.
     * @return  A string holding the hash value of the BLOB.
     */
    static QString getHash(QByteArray const & data) {
        return getSHA256(data);
    }
    
    /**
     * Returns the detected mime type of the resource.
     *
     * @return  the (suggested) mime type of the resource.
     */
    QMimeType getMimeType() const;
    
    /**
     * Gets the path to this resource, relative to the resource root.
     *
     * @return  the path uniquely identifying this resource.
     */
    QString getPath() const {
        return path;
    }
    
    /**
     * Returns the first prefix of the path.
     *
     * @return  the first prefix of the path used to identify the resource type.
     */
    QString getPrefix() const;
    
    /**
     * Calculate the SHA256 value of a BLOB.
     *
     * @param   data        a BLOB.
     * @return  A string holding the SHA256 of the BLOB.
     */
    static QString getSHA256(QByteArray const & data);
    
    /**
     * Gets the type of this resource (based on the resource path).
     *
     * @return  the type of this resource.
     */
    ResourceType getType() const;
    
    /**
     * Sets a new data to this resource.
     *
     * @param   data        the new data.
     */
    virtual void setData(QByteArray const & data);
    
    /**
     * Sets a new name for this resource.
     *
     * @param   name        the new name.
     */
    void setName(QString name);
    
    /**
     * Strips a prefix from the path and returns the rest of the path.
     *
     * @return  the path without the known prefix.
     */
    QString stripPrefixFromPath() const;
};


}
}
}


#endif
