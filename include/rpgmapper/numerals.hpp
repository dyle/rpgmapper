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


class NumeralConverter {

public:

    virtual ~NumeralConverter() = default;

    static QSharedPointer<NumeralConverter> const & create(QString const & method);

    virtual QString convert(int value) const = 0;

    virtual bool isValid() const { return true; }

    virtual QString name() const = 0;

protected:

    NumeralConverter() = default;

};

class InvalidNumeralConverter final : public NumeralConverter {

public:

    QString convert(int) const override { return QString::null; }

    bool isValid() const override { return false; }

    QString name() const override { return "Invalid"; }
};


}
}


#endif
