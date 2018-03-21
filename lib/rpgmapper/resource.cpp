/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QCryptographicHash>

#include <rpgmapper/resource.hpp>

using namespace rpgmapper::model;


Resource::Resource(QString name, QByteArray const & data)
    : data{data},
      name{std::move(name)} {
}


QString Resource::getSHA256(QByteArray const & data) {
    return QString(QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex());
}
