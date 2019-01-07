/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_NAMEABLE_HPP
#define RPGMAPPER_MODEL_NAMEABLE_HPP

#include <QJsonObject>
#include <QObject>
#include <QString>

#include <rpgmapper/json/json_io.hpp>
#include <rpgmapper/base.hpp>


namespace rpgmapper::model {


/**
 * An instance of this class can be assigned a name and read/writes it form/to JSON instances.
 */
class Nameable : public QObject, public Base, public json::JSONIO {
    
    Q_OBJECT
    
    QString name;           /**< The name itself. */

public:

    /**
     * Constructor.
     *
     * @param   name        the name of the object.
     */
    explicit Nameable(QString name = QString::null);
    
    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON  holding  the name.
     * @return  true, if the name has been found and has been applied.
     */
    bool applyJSON(QJsonObject const & json) override;

    /**
     * Zap the name.
     */
    void clear();
    
    /**
     * Create a JSON object.
     *
     * @return  the JSON describing this instance.
     */
    QJsonObject getJSON() const override;

    /**
     * Gettor the the name.
     *
     * @return  the name of this object.
     */
    QString const & getName() const {
        return name;
    }

    /**
     * Sets a new name for this instance.
     *
     * @param   name    a new name of this object.
     */
    virtual void setName(QString name);

protected:
    
    /**
     * Collects all fields of this object as JSON members.
     *
     * @return  a JSON string of all member fields.
     */
    std::string json() const override;

signals:
    
    /**
     * The name of the instance has changed.
     *
     * @param   oldName     the old name
     * param    newName     the new name
     */
    void nameChanged(QString oldName, QString newName);
};


}


#endif
