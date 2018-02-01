/*
 * unitconverter.cpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


// ------------------------------------------------------------
// incs

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
