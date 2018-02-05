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
#include <rpgmapper/atlas.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code

int test() {

    Atlas cAtlas;
    assert(!cAtlas.isModified());
    cAtlas.setModified(false);
    assert(!cAtlas.isModified());

    cAtlas.setName("bar");
    assert(cAtlas.isModified());
    cAtlas.setModified(false);
    assert(!cAtlas.isModified());

    auto cRegion = cAtlas.createRegion();
    assert(cAtlas.isModified());
    cAtlas.setModified(false);
    assert(!cAtlas.isModified());

    cRegion->setName("foobar");
    assert(cAtlas.isModified());

    return 0;
}

int main(UNUSED int argc, UNUSED char ** argv) {
    return test();
}
