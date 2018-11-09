/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_NUMERALS_HPP
#define RPGMAPPER_MODEL_NUMERALS_HPP

#include <QJsonObject>
#include <QString>
#include <QSharedPointer>


namespace rpgmapper {
namespace model {


/**
 * This class can convert one axis numeral to another.
 *
 * The most important method convert() which returns a string representing the number.
 *
 * E.g.:
 *      auto nc = NumeralConverter::create("roman")
 *      std::cout << nc.convert(7) << std::endl;        // will yield "VII"
 */
class NumeralConverter {

public:

    /**
     * Destructor.
     */
    virtual ~NumeralConverter() = default;

    /**
     * Factory method for numeral converters.
     *
     * Current known methods:
     *
     *      "alphaBig" ........ big alphabetical letters: "A", "B", "C", ...
     *      "alphaSmall" ...... small alphabetical letters: "a", "b", "c", ...
     *      "numeric" ......... numeric arabci numbers: "1", "2", "3", ...
     *      "roman" ........... roman number letters: "I", "II", "III", "IV", ...
     *
     * @param   method      the numeral converter known
     * @return  an instance of the numeral converter specified by the method name
     */
    static QSharedPointer<NumeralConverter> const & create(QString method);

    /**
     * Converts the given number to a string representation.
     *
     * @param   value       the value to convert.
     * @return  a string describing the value with the current method.
     */
    virtual QString convert(int value) const = 0;

    /**
     * Gets the name of the conversion method.
     *
     * @return  a human readable name of the conversion method.
     */
    virtual QString getName() const = 0;
    
    /**
     * Checks if this is a valid converter.
     *
     * [Null object pattern]
     *
     * @return  true, if this instance is a valid converter.
     */
    virtual bool isValid() const {
        return true;
    }
    
    /**
     * The invalid null converter.
     *
     * [null object pattern]
     *
     * @return  the invalid null converter.
     */
    static QSharedPointer<NumeralConverter> const & nullConverter();

protected:

    /**
     * Constructor.
     */
    NumeralConverter() = default;

};


/**
 * This class represents the invalid numeral converter.
 */
class InvalidNumeralConverter final : public NumeralConverter {

public:

    /**
     * Converts the value to a string.
     *
     * @return  always returns the null string.
     */
    QString convert(int) const override {
        return QString::null;
    }

    /**
     * Gets the name of the invalid converter.
     *
     * @return  "Invalid".
     */
    QString getName() const override {
        return "Invalid";
    }

    /**
     * Checks if this is a valid converter.
     *
     * @return  always false.
     */
    bool isValid() const override {
        return false;
    }
};


/**
 * Coordinates of a single point, but described as numerals.
 */
struct NumeralCoordinates {
    QString x;
    QString y;
};


}
}


#endif
