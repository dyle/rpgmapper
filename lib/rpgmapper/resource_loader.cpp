/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/resource_loader.hpp>

using namespace rpgmapper::model;


ResourceLoader::ResourceLoader(QObject * parent) : QObject{parent} {
}


void ResourceLoader::load(QStringList & log) {
    log.append(tr("NOT IMPLEMENTED YET!"));
}
