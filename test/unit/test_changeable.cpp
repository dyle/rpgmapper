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
#include <vector>

// rpgmapper
#include <rpgmapper/changeable.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl


class A : public Changeable {

public:


    A() : Changeable{} {}


    bool isModified() const override {
        if (Changeable::isModified()) {
            return true;
        }
        for (auto const & c: v) {
            if (c->isModified()) {
                return true;
            }
        }
        return false;
    }


    void setModified(bool bModified) override {
        Changeable::setModified(bModified);
        for (auto & c: v) {
            c->setModified(bModified);
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
    assert(!cChangeable->isModified());

    cChangeable->setModified(true);
    assert(cChangeable->isModified());

    A a;
    assert(!a.isModified());
    for (auto & c: a.v) {
        assert(!c->isModified());
    }

    a.v[1]->setModified(true);
    assert(a.isModified());

    a.setModified(false);
    assert(!a.isModified());

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
