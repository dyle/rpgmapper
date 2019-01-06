/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#include <QRegExp>

#include <rpgmapper/region_name_validator.hpp>

using namespace rpgmapper::model;


bool RegionNameValidator::isValid(QString name) {
    
    static QString const INVALID_CHARACTERS = R"raw(:\\*\?/)raw";
    QRegExp regExp{QString{"[%1]"}.arg(INVALID_CHARACTERS)};
    
    return (!name.isEmpty()) && (regExp.indexIn(name) == -1);
}
