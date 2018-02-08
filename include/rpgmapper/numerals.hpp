/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_NUMERALS_HPP
#define RPGMAPPER_MODEL_NUMERALS_HPP


#include <QString>
#include <QSharedPointer>


namespace rpgmapper {
namespace model {


enum class Numerals {
    Numeric,
    AlphaBig,
    AlphaSmall,
    Roman
};


class NumeralConverter {

public:


    static QSharedPointer<NumeralConverter> create(Numerals numeral);


    virtual QString convert(int nValue) const = 0;

protected:

    NumeralConverter() = default;

};


}
}


#endif
