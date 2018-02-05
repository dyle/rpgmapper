/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// incs

#include "numericconverter.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Convert the given value into the user units.
 *
 * @param   nValue      value to convert
 * @return  A string holding the user value
 */
QString NumericConverter::convert(int nValue) const {
    return QString::number(nValue);
}
