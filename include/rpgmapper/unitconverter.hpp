/*
 * unitconverter.hpp
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
