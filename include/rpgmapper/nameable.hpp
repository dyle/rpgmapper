/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_NAMEABLE_HPP
#define RPGMAPPER_MODEL_NAMEABLE_HPP


#include <QJsonObject>
#include <QObject>
#include <QString>

#include <rpgmapper/changeable.hpp>
#include <rpgmapper/types.hpp>


namespace rpgmapper {
namespace model {


class NameableInstance : public Changeable {

    Q_OBJECT

    QString name;

public:

    explicit NameableInstance(QObject * parent = nullptr);

    QString const & getName() const { return name;}

    static Nameable load(QJsonObject const & json);

    virtual void save(QJsonObject & json) const;

    void setName(QString name);

signals:

    void changedName();
};


}
}


#endif
