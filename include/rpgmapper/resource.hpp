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


class Resource;
using ResourcePointer = QSharedPointer<Resource>;

class Resource {

    QByteArray data;
    QString name;

public:

    explicit Resource(QString name, QByteArray const & data);

    QByteArray const & getData() const {
        return data;
    }

    QString const & getName() const {
        return name;
    }

    QString getHash() const {
        return getSHA256(getData());
    }

    static QString getHash(QByteArray const & data) {
        return getSHA256(data);
    }

    static QString getSHA256(QByteArray const & data);

    bool isEmpty() const {
        return name.isEmpty();
    }
};


}
}


#endif
