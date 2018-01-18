/*
 * test_map_json.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

    cMap->size(QSize(100, 100));
    std::cout << "Map: width=" << cMap->size().width() << ", height=" << cMap->size().height() << std::endl;
    assert(cMap->size().width() == 100);
    assert(cMap->size().height() == 100);

    try {
        cMap->size(QSize(Map::minimumWidth() - 1, Map::minimumHeight() - 1));
        assert(false);
    }
    catch (...) {}

    try {
        cMap->size(QSize(Map::maximumWidth(), Map::maximumHeight()));
        assert(false);
    }
    catch (...) {}

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
