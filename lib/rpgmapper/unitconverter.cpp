/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/unitconverter.hpp>
#include "unitconverter/alphabeticbigcapsconverter.hpp"
#include "unitconverter/alphabeticsmallcapsconverter.hpp"
#include "unitconverter/numericconverter.hpp"
#include "unitconverter/romanconverter.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// code


/**
 * Get a unit converter instance.
 *
 * @param   eConverterType      the type of the converter
 * @return  an instance of a unit converter
 */
QSharedPointer<UnitConverter> UnitConverter::create(UnitConverter::converter_type eConverterType) {

    switch (eConverterType) {

        case numeric:
            return QSharedPointer<UnitConverter>(new NumericConverter);

        case alphabeticalSmallCaps:
            return QSharedPointer<UnitConverter>(new AlphabeticSmallCapsConverter);

        case alphabeticalBigCaps:
            return QSharedPointer<UnitConverter>(new AlphabeticBigCapsConverter);

        case roman:
            return QSharedPointer<UnitConverter>(new RomanConverter);
    }

    throw std::runtime_error("Unknown unit converter enumeration.");
}
