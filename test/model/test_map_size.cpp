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

#include <cassert>
#include <iostream>

// rpgmapper
#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    Atlas cAtlas;
    auto cMap = cAtlas.createMap();
    std::cout << "Map: width=" << cMap->size().width() << ", height=" << cMap->size().height() << std::endl;

    cMap->setSize(QSize(100, 100));
    std::cout << "Map: width=" << cMap->size().width() << ", height=" << cMap->size().height() << std::endl;
    assert(cMap->size().width() == 100);
    assert(cMap->size().height() == 100);

    try {
        cMap->setSize(QSize(MINIMUM_MAP_WIDTH - 1, MINIMUM_MAP_HEIGHT - 1));
        assert(false);
    }
    catch (...) {}

    try {
        cMap->setSize(QSize(MAXIMUM_MAP_WIDTH + 1, MAXIMUM_MAP_HEIGHT + 1));
        assert(false);
    }
    catch (...) {}

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
