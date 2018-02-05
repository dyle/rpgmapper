/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef MODEL_ROMANCONVERTER_HPP
#define MODEL_ROMANCONVERTER_HPP


// ------------------------------------------------------------
// incs

#include <rpgmapper/unitconverter.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A collection of maps based on a name.
 */
class RomanConverter : public UnitConverter {


public:


    /**
     * Ctor.
     */
    RomanConverter() = default;


    /**
     * Convert the given value into the user units.
     *
     * @param   nValue      value to convert
     * @return  A string holding the user value
     */
    QString convert(int nValue) const override;


};


}
}


#endif
