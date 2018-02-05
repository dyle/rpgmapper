/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#if defined(__GNUC__) || defined(__GNUCPP__)
#   define UNUSED   __attribute__((unused))
#else
#   define UNUSED
#endif


// ------------------------------------------------------------

#include <iostream>

#include <QJsonDocument>

// rpgmapper
#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    Atlas cAtlas1;
    std::cout << cAtlas1.json(QJsonDocument::Compact).toStdString() << std::endl;

    cAtlas1.mapById(1)->setRegion(cAtlas1.regionById(1));
    std::cout << cAtlas1.json(QJsonDocument::Compact).toStdString() << std::endl;

    auto cRegion2 = cAtlas1.createRegion();
    auto cMap2 = cAtlas1.createMap();
    cRegion2->addMap(cMap2);
    std::cout << cAtlas1.json(QJsonDocument::Compact).toStdString() << std::endl;

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
