/*
 * alphabeticbigcapsconverter.cpp
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


// ------------------------------------------------------------
// incs

#include <iostream>
#include "alphabetic.hpp"
#include "alphabeticbigcapsconverter.hpp"

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
