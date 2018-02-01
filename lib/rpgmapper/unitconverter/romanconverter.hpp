/*
 * romanconverter.hpp
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
