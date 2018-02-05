/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef MODEL_ALPHABETIC_HPP
#define MODEL_ALPHABETIC_HPP


// ------------------------------------------------------------
// incs

#include <QString>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * Convert a value to alphanumeric
 *
 * @param   nValue      the value
 * @param   bBig        big or small caps
 * @return  a string holding the value converted to alphabetic
 */
QString convertAlpha(int nValue, bool bBig);


}
}


#endif
