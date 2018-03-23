/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHA_SMALL_HPP
#define RPGMAPPER_MODEL_NUMERALCONVERTER_ALPHA_SMALL_HPP


#include <rpgmapper/numerals.hpp>


namespace rpgmapper {
namespace model {


class AlphaSmallCapsConverter : public NumeralConverter {

public:

    AlphaSmallCapsConverter() = default;

    QString convert(int value) const override;

    QString getName() const override {
        return "alphaSmall";
    }
};


}
}


#endif
