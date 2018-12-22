/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <QMimeDatabase>
#include <QMimeType>

#include <rpgmapper/resource/shape.hpp>

using namespace rpgmapper::model::resource;


Shape::Shape(QString name, QByteArray const & data) : Resource{std::move(name), data} {
}


bool Shape::isShape(QByteArray const & data) {
    
    static QMimeDatabase mimeDatabase;
    auto mimeType = mimeDatabase.mimeTypeForData(data);
    
    auto mimeTypeString = mimeType.name();
    return mimeTypeString == "image/svg+xml";
}


void Shape::setData(QByteArray const & data) {
    Resource::setData(data);
}
