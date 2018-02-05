/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


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
