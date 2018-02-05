/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef MODEL_UNITCONVERTER_HPP
#define MODEL_UNITCONVERTER_HPP


// ------------------------------------------------------------
// incs

#include <QString>
#include <QSharedPointer>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * A collection of maps based on a name.
 */
class UnitConverter {


public:


    enum converter_type {
        numeric = 0,                        /**< Unit is a number. */
        alphabeticalSmallCaps = 1,          /**< Unit is alphabetical, small caps: a, b, c, ... */
        alphabeticalBigCaps = 2,            /**< Unit is alphabetical, big caps: A, B, C, ... */
        roman = 4                           /**< Unit is roman: I, II, III, IV, ... X, ... M, ... */
    };


    /**
     * Get a unit converter instance.
     *
     * @param   eConverterType      the type of the converter
     * @return  an instance of a unit converter
     */
    static QSharedPointer<UnitConverter> create(UnitConverter::converter_type eConverterType);


    /**
     * Convert the given value into the user units.
     *
     * @param   nValue      value to convert
     * @return  A string holding the user value
     */
    virtual QString convert(int nValue) const = 0;


protected:


    /**
     * Ctor.
     */
    UnitConverter() = default;

};


}
}


#endif
