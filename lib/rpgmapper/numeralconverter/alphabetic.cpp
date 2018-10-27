/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include "alphabetic.hpp"

using namespace rpgmapper::model;


QString rpgmapper::model::convertToAlphabetic(int value, bool bigCaps) {

    // derived from
    // https://stackoverflow.com/a/30259745/8754067

    if (value < 0) {
        return QString("-") + convertToAlphabetic(-value, bigCaps);
    }

    int nQuotient = value / 26;
    int nRemainder = value % 26;

    auto sChar = QString(static_cast<char>(nRemainder + (bigCaps ? 'A' : 'a')));
    if (nQuotient == 0) {
        return sChar;
    }

    return convertToAlphabetic(nQuotient - 1, bigCaps) + sChar;
}
