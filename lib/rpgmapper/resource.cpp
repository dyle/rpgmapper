/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QCryptographicHash>
#include <QMimeDatabase>

#include <rpgmapper/resource.hpp>

using namespace rpgmapper::model;


Resource::Resource(QString path, QByteArray const & data) : data{data}, path{std::move(path)} {
}


QString Resource::getSHA256(QByteArray const & data) {
    return QString(QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex());
}


QMimeType Resource::getMimeType() const {
    static QMimeDatabase mimeDatabase;
    return mimeDatabase.mimeTypeForData(getData());
}


QString Resource::getPrefix() const {
    auto path = getPath();
    return path.left(path.indexOf('/', 1));
}


ResourceType Resource::getType() const {
    return suggestResourceTypeByPath(getPath());
}


void Resource::setData(QByteArray const &data) {
    this->data = data;
}


void Resource::setName(QString name) {
    this->name = name;
}
