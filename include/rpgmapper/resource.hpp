/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_RESOURCE_HPP
#define RPGMAPPER_RESOURCE_HPP

#include <QByteArray>
#include <QSharedPointer>
#include <QString>


namespace rpgmapper {
namespace model {


/**
 * A resource is a named BLOB.
 */
class Resource {

    QByteArray data;        /**< The Blob. */
    QString name;           /**< The name associated with the BLOB. */

public:

    /**
     * Constructor.
     *
     * @param   name        name of the BLOB.
     * @param   data        the BLOB.
     */
    Resource(QString name, QByteArray const & data);

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
     * Calculate the SHA256 value of a BLOB.
     *
     * @param   data        a BLOB.
     * @return  A string holding the SHA256 of the BLOB.
     */
    static QString getSHA256(QByteArray const & data);
    
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
};


}
}


#endif
