/*
 * alphabetic.hpp
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

#include "alphabetic.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Convert a value to alphanumeric
 *
 * @param   nValue      the value
 * @param   bBig        big or small caps
 * @return  a string holding the value converted to alphabetic
 */
QString rpgmapper::model::convertAlpha(int nValue, bool bBig) {

    // derived from
    // https://stackoverflow.com/a/30259745/8754067

    if (nValue < 0) {
        return QString("-") + convertAlpha(-nValue, bBig);
    }

    int nQuotient = nValue / 26;
    int nRemainder = nValue % 26;

    auto sChar = QString(static_cast<char>(nRemainder + (bBig ? 'A' : 'a')));
    if (nQuotient == 0) {
        return sChar;
    }

    return convertAlpha(nQuotient - 1, bBig) + sChar;
}
