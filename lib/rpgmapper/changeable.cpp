/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/changeable.hpp>

using namespace rpgmapper::model;


Changeable::Changeable(QObject * cParent) : QObject{cParent} {
}


void Changeable::setModified(bool modified) {
    this->modified = modified;
}
