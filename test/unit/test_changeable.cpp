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
#include "model/changeable.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl


class A : public Changeable {

public:


    A() = default;


    bool changedAccumulated() const {
        if (changed()) {
            return true;
        }
        for (auto const & c: v) {
            if (c.changedAccumulated()) {
                return true;
            }
        }
        return false;
    }


    void changedAccumulated(bool bChanged) {
        changed(bChanged);
        for (auto & c: v) {
            c.changedAccumulated(bChanged);
        }
    }


    std::vector<Changeable> v = { Changeable(), Changeable(), Changeable() };

};


// ------------------------------------------------------------
// code

int test() {

    // single object

    Changeable c;
    assert(c.changed() == false);

    c.changed(true);
    assert(c.changed() == true);

    // object hierarchie

    A a;
    assert(a.changed() == false);
    for (auto & c: a.v) {
        assert(c.changed() == false);
    }
    assert(a.changedAccumulated() == false);

    a.v[1].changed(true);
    assert(a.changed() == false);
    assert(a.changedAccumulated() == true);

    a.changedAccumulated(false);
    assert(a.changed() == false);
    assert(a.changedAccumulated() == false);

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
