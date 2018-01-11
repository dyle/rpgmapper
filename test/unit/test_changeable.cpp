/*
 * test_changeable.cpp
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
#include <rpgmapper/model/changeable.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl


class A : public Changeable {

public:


    A() = default;


    bool changedAccumulated() const override {
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


    void changedAccumulated(bool bChanged) override {
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

    Changeable cChangeable;
    assert(!cChangeable.changed());

    cChangeable.changed(true);
    assert(cChangeable.changed());

    // object hierarchy

    A a;
    assert(!a.changed());
    for (auto & c: a.v) {
        assert(!c.changed());
    }
    assert(!a.changedAccumulated());

    a.v[1].changed(true);
    assert(!a.changed());
    assert(a.changedAccumulated());

    a.changedAccumulated(false);
    assert(!a.changed());
    assert(!a.changedAccumulated());

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
