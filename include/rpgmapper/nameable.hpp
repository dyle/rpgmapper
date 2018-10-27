/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_NAMEABLE_HPP
#define RPGMAPPER_MODEL_NAMEABLE_HPP

#include <QObject>
#include <QString>

#include <rpgmapper/json/json_io.hpp>


namespace rpgmapper {
namespace model {


/**
 * An instance of this class can be assigned a name and read/writes it form/to JSON instances.
 */
class Nameable : public rpgmapper::model::json::JSONIO {
    
    Q_OBJECT
    
    QString name;           /**< The name itself. */

public:

    /**
     * Constructor.
     */
    Nameable() = default;

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
    void setName(QString const & name);
    
    
signals:
    
    /**
     * The name of the instance has changed.
     */
    void nameChanged();
};


}
}


#endif
