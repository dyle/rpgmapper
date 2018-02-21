/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <rpgmapper/numerals.hpp>
#include "alpha_big.hpp"
#include "alpha_small.hpp"
#include "numeric.hpp"
#include "roman.hpp"

using namespace rpgmapper::model;


QSharedPointer<NumeralConverter> const & NumeralConverter::create(QString const & method) {

    static std::map<QString, QSharedPointer<NumeralConverter>> const converters{
        {"Numeric", QSharedPointer<NumeralConverter>{new NumericConverter}},
        {"AlphaSmall", QSharedPointer<NumeralConverter>{new AlphaSmallCapsConverter}},
        {"AlphaBig", QSharedPointer<NumeralConverter>{new AlphaBigCapsConverter}},
        {"Roman", QSharedPointer<NumeralConverter>{new RomanConverter}}
    };

    auto iter = converters.find(method);
    if (iter == converters.end()) {
        return nullConverter();
    }

    return (*iter).second;
}


QSharedPointer<NumeralConverter> const & NumeralConverter::nullConverter() {
    static QSharedPointer<NumeralConverter> invalidConverter{new InvalidNumeralConverter};
    return invalidConverter;
}

