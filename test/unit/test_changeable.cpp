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
#include <rpgmapper/changeable.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl


class A : public Changeable {

public:


    A() : Changeable{} {}


    bool modified() const override {
        if (Changeable::modified()) {
            return true;
        }
        for (auto const & c: v) {
            if (c->modified()) {
                return true;
            }
        }
        return false;
    }


    void modified(bool bModified) override {
        Changeable::modified(bModified);
        for (auto & c: v) {
            c->modified(bModified);
        }
    }


    std::vector<rpgmapper::model::ChangeablePointer> v = {
            rpgmapper::model::ChangeablePointer{new Changeable},
            rpgmapper::model::ChangeablePointer{new Changeable},
            rpgmapper::model::ChangeablePointer{new Changeable}
    };

};


// ------------------------------------------------------------
// code

int test() {

    ChangeablePointer cChangeable{new Changeable};
    assert(!cChangeable->modified());

    cChangeable->modified(true);
    assert(cChangeable->modified());

    A a;
    assert(!a.modified());
    for (auto & c: a.v) {
        assert(!c->modified());
    }

    a.v[1]->modified(true);
    assert(a.modified());

    a.modified(false);
    assert(!a.modified());

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
