/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHA_BIG_HPP
#define RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHA_BIG_HPP


#include <rpgmapper/numerals.hpp>


namespace rpgmapper {
namespace model {


class AlphaBigCapsConverter : public NumeralConverter {

public:

    AlphaBigCapsConverter() = default;

    QString convert(int value) const override;

};


}
}


#endif
