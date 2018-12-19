/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/shape_catalog.hpp>

using namespace rpgmapper::model;


ShapeCatalog::ShapeCatalog(QString name, QByteArray const & data) : Resource{std::move(name), data} {
}


void ShapeCatalog::setData(QByteArray const & data) {
    Resource::setData(data);
}
