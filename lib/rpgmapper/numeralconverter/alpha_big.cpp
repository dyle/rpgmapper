/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <iostream>
#include "alphabetic.hpp"
#include "alpha_big.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// vars


/**
 * Lookup table.
 */
static std::map<int, QString> g_cLookupValues;            /**< Known cached values. */


// ------------------------------------------------------------
// code


/**
 * Convert the given value into the user units.
 *
 * @param   nValue      value to convert
 * @return  A string holding the user value
 */
QString AlphabeticBigCapsConverter::convert(int nValue) const {

    if (g_cLookupValues.empty()) {
        for (int n = 0; n <= 100; ++n) {
            g_cLookupValues[n] = convertAlpha(n, true);
        }
    }

    auto iterLookup = g_cLookupValues.find(nValue);
    if (iterLookup != g_cLookupValues.end()) {
        return (*iterLookup).second;
    }

    auto res = convertAlpha(nValue, true);
    g_cLookupValues[nValue] = res;

    return res;
}
