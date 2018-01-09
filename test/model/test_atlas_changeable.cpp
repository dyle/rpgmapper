/*
 * test_changeable.cpp
 *
 * This the Changeable object.
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
#include <vector>

// rpgmapper
#include <rpgmapper/model/atlas.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    Atlas a;
    assert(a.changedAccumulated() == true);
    a.changedAccumulated(false);
    assert(a.changedAccumulated() == false);

    a.name("bar");
    assert(a.changedAccumulated() == true);
    a.changedAccumulated(false);
    assert(a.changedAccumulated() == false);

    Region & r = a.createRegion();
    assert(a.changedAccumulated() == true);
    a.changedAccumulated(false);
    assert(a.changedAccumulated() == false);

    r.name("foobar");
    assert(a.changedAccumulated() == true);

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
