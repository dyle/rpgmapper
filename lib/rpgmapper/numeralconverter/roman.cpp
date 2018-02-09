/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include "roman.hpp"

using namespace rpgmapper::model;


static QString convertToRoman(int value);

static void initCachedValues(std::map<int, QString> & cache);


QString RomanConverter::convert(int value) const {

    static std::map<int, QString> cachedValues;
    if (cachedValues.empty()) {
        initCachedValues(cachedValues);
    }

    auto iter = cachedValues.find(value);
    if (iter != cachedValues.end()) {
        return (*iter).second;
    }

    auto res = convertToRoman(value);
    cachedValues[value] = res;

    return res;
}


QString convertToRoman(int value) {

    if (value < 0) {
        return QString("-") + convertToRoman(-value);
    }
    if (value == 0) {
        return QString("O");
    }

    // derived by
    // https://stackoverflow.com/questions/12967896/converting-integers-to-roman-numerals-java

    QString res = "";

    while (value >= 1000) {
        res += "M";
        value -= 1000;
    }
    while (value >= 900) {
        res += "CM";
        value -= 900;
    }
    while (value >= 500) {
        res += "D";
        value -= 500;
    }
    while (value >= 400) {
        res += "CD";
        value -= 400;
    }
    while (value >= 100) {
        res += "C";
        value -= 100;
    }
    while (value >= 90) {
        res += "XC";
        value -= 90;
    }
    while (value >= 50) {
        res += "L";
        value -= 50;
    }
    while (value >= 40) {
        res += "XL";
        value -= 40;
    }
    while (value >= 10) {
        res += "X";
        value -= 10;
    }
    while (value >= 9) {
        res += "IX";
        value -= 9;
    }
    while (value >= 5) {
        res += "V";
        value -= 5;
    }
    while (value >= 4) {
        res += "IV";
        value -= 4;
    }
    while (value >= 1) {
        res += "I";
        value -= 1;
    }

    return res;
}


void initCachedValues(std::map<int, QString> & cache) {
    for (int n = 0; n <= 100; ++n) {
        cache[n] = convertToRoman(n);
    }
}
