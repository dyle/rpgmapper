/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <rpgmapper/resource/shape_catalog.hpp>

using namespace rpgmapper::model::resource;


ShapeCatalog::ShapeCatalog(QString name, QByteArray const & data) : Resource{std::move(name), data} {
}


bool ShapeCatalog::isShapeCatalog(QByteArray const & data) {
    
    auto jsonDocument = QJsonDocument::fromJson(data);
    if (!jsonDocument.isArray()) {
        return false;
    }
    
    return true;
}


void ShapeCatalog::setData(QByteArray const & data) {
    Resource::setData(data);
}
