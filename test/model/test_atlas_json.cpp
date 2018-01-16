/*
 * test_json.cpp
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

#include <iostream>

#include <QJsonDocument>

// rpgmapper
#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    // just dump the JSON string to stdout
    Atlas cAtlas1;
    std::cout << cAtlas1.json(QJsonDocument::Compact).toStdString() << std::endl;

    cAtlas1.maps()[1]->region(cAtlas1.regions()[1]);
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
