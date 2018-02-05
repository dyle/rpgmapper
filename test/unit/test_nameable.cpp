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
#include <rpgmapper/nameable.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    Nameable cNameable;
    assert(!cNameable.isModified());
    assert(cNameable.name().isNull());

    cNameable.setName("foo");
    assert(cNameable.isModified());
    assert(cNameable.name() == "foo");

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
