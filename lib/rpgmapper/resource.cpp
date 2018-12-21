/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <map>

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

    static std::map<QString, ResourceType> knownPrefix;
    if (knownPrefix.empty()) {
        knownPrefix.emplace(getResourcePrefixForType(ResourceType::background), ResourceType::background);
        knownPrefix.emplace(getResourcePrefixForType(ResourceType::colorpalette), ResourceType::colorpalette);
        knownPrefix.emplace(getResourcePrefixForType(ResourceType::shape), ResourceType::shape);
    }
    
    auto pair = knownPrefix.find(getPrefix());
    if (pair == knownPrefix.end()) {
        return ResourceType::unknown;
    }

    return (*pair).second;
}


void Resource::setData(QByteArray const &data) {
    this->data = data;
}


void Resource::setName(QString name) {
    this->name = name;
}
