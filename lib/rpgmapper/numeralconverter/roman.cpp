/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// ------------------------------------------------------------
// incs

#include "roman.hpp"

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl


/**
 * Convert an integer to roman.
 *
 * @param   nValue      the value to convert
 * @return  the string holding the roman value
 */
static QString convertRoman(int nValue);


// ------------------------------------------------------------
// vars


/**
 * Lookup table.
 */
static std::map<int, QString> g_cLookupValues;            /**< Known cached values. */


// ------------------------------------------------------------
// code


/**
 * Convert the given value into the user units.
 *
 * @param   nValue      value to convert
 * @return  A string holding the user value
 */
QString RomanConverter::convert(int nValue) const {

    if (g_cLookupValues.empty()) {
        for (int n = 0; n <= 100; ++n) {
            g_cLookupValues[n] = convertRoman(n);
        }
    }

    auto iterLookup = g_cLookupValues.find(nValue);
    if (iterLookup != g_cLookupValues.end()) {
        return (*iterLookup).second;
    }

    auto res = convertRoman(nValue);
    g_cLookupValues[nValue] = res;

    return res;
}


/**
 * Convert an integer to roman.
 *
 * @param   nValue      the value to convert
 * @return  the string holding the roman value
 */
QString convertRoman(int nValue) {

    if (nValue < 0) {
        return QString("-") + convertRoman(-nValue);
    }
    if (nValue == 0) {
        return QString("O");
    }

    // derived by
    // https://stackoverflow.com/questions/12967896/converting-integers-to-roman-numerals-java

    QString res = "";

    while (nValue >= 1000) {
        res += "M";
        nValue -= 1000;
    }
    while (nValue >= 900) {
        res += "CM";
        nValue -= 900;
    }
    while (nValue >= 500) {
        res += "D";
        nValue -= 500;
    }
    while (nValue >= 400) {
        res += "CD";
        nValue -= 400;
    }
    while (nValue >= 100) {
        res += "C";
        nValue -= 100;
    }
    while (nValue >= 90) {
        res += "XC";
        nValue -= 90;
    }
    while (nValue >= 50) {
        res += "L";
        nValue -= 50;
    }
    while (nValue >= 40) {
        res += "XL";
        nValue -= 40;
    }
    while (nValue >= 10) {
        res += "X";
        nValue -= 10;
    }
    while (nValue >= 9) {
        res += "IX";
        nValue -= 9;
    }
    while (nValue >= 5) {
        res += "V";
        nValue -= 5;
    }
    while (nValue >= 4) {
        res += "IV";
        nValue -= 4;
    }
    while (nValue >= 1) {
        res += "I";
        nValue -= 1;
    }

    return res;
}
