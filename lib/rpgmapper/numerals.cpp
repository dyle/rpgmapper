/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/numerals.hpp>
#include "numeralconverter/alpha_big.hpp"
#include "numeralconverter/alpha_small.hpp"
#include "numeralconverter/numeric.hpp"
#include "numeralconverter/roman.hpp"

using namespace rpgmapper::model;


QSharedPointer<NumeralConverter> NumeralConverter::create(Numerals numeral) {

    switch (numeral) {

        case Numerals::Numeric:
            return QSharedPointer<NumeralConverter>(new NumericConverter);

        case Numerals::AlphaSmall
            return QSharedPointer<NumeralConverter>(new AlphabeticSmallCapsConverter);

        case Numerals::AlphaBig:
            return QSharedPointer<NumeralConverter>(new AlphabeticBigCapsConverter);

        case Numerals::Roman:
            return QSharedPointer<NumeralConverter>(new RomanConverter);
    }
}
