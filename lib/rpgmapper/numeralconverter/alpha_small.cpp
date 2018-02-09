/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <iostream>
#include "alphabetic.hpp"
#include "alpha_small.hpp"

using namespace rpgmapper::model;


static void initCachedValues(std::map<int, QString> & cache);


QString AlphaSmallCapsConverter::convert(int value) const {

    static std::map<int, QString> cachedValues;
    if (cachedValues.empty()) {
        initCachedValues(cachedValues);
    }

    auto iter = cachedValues.find(value);
    if (iter != cachedValues.end()) {
        return (*iter).second;
    }

    auto res = convertToAlphabetic(value, false);
    cachedValues[value] = res;

    return res;
}


void initCachedValues(std::map<int, QString> & cache) {
    for (int n = 0; n <= 100; ++n) {
        cache[n] = convertToAlphabetic(n, false);
    }
}
