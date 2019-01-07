/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHABETIC_HPP
#define RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHABETIC_HPP

#include <QString>


namespace rpgmapper::model {


/**
 * Convert a value to its alphabetic equivalent (like Excel columns).
 *
 * @param   value       the value to convert.
 * @param   bigCaps     true, for big letters.
 * @return  the string holding the value
 */
QString convertToAlphabetic(int value, bool bigCaps);


}


#endif
