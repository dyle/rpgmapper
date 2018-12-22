/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <utility>

#include <rpgmapper/resource/shape.hpp>

using namespace rpgmapper::model::resource;


Shape::Shape(QString name, QByteArray const & data) : Resource{std::move(name), data} {
}


void Shape::setData(QByteArray const & data) {
    Resource::setData(data);
}
