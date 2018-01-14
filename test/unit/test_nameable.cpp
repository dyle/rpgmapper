/*
 * test_nameable.cpp
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

// rpgmapper
#include <rpgmapper/model/nameable.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    Nameable cNameable;
    assert(!cNameable.changed());
    assert(cNameable.name().isNull());

    cNameable.name("foo");
    assert(cNameable.changed());
    assert(cNameable.name() == "foo");

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
