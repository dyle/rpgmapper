/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include "numeric.hpp"

using namespace rpgmapper::model;


QString NumericConverter::convert(int nValue) const {
    return QString::number(nValue);
}
