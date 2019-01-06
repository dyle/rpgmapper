/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHA_SMALL_HPP
#define RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHA_SMALL_HPP

#include <rpgmapper/numerals.hpp>


namespace rpgmapper {
namespace model {


/**
 * Numeralconverter for small alphabetic letters.
 */
class AlphaSmallCapsConverter : public NumeralConverter {

public:
    
    /**
     * Constructor.
     */
    AlphaSmallCapsConverter() = default;
    
    /**
     * Converts the given number to a string representation.
     *
     * @param   value       the value to convert.
     * @return  a string describing the value with the current method.
     */
    QString convert(int value) const override;
    
    /**
     * Gets the name of the conversion method.
     *
     * @return  "alphaSmall".
     */
    QString getName() const override {
        return "alphaSmall";
    }
};


}
}


#endif
