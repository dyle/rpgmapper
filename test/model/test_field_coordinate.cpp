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

// rpgmapper
#include <rpgmapper/map.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    assert(Field::coordinate(QPoint{12, 34}) == 34012);
    assert(Field::position(34) == QPoint(34, 0));
    assert(Field::position(178230) == QPoint(230, 178));

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
