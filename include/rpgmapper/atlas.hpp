/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_ATLAS_HPP
#define RPGMAPPER_MODEL_ATLAS_HPP

#include <QJsonArray>
#include <QJsonObject>
#include <QSharedPointer>

#include <rpgmapper/nameable.hpp>


namespace rpgmapper {
namespace model {


/**
 * This is the main class.
 *
 * An atlas as a set of regions, each with a set of maps.
 */
class Atlas : public Nameable {

    Q_OBJECT
    
public:

    /**
     * Applies a JSON to this instance.
     *
     * @param   json    the JSON.
     * @return  true, if the found values in the JSON data has been applied.
     */
    bool applyJSON(QJsonObject json);
    
    /**
     * Create a JSON structure from oourselves.
     *
     * @return      a valid JSON  structure from ooourselves.
     */
    QJsonObject getJSON() const override;

    /**
     * Checks if the given name is valid.
     *
     * @param   name        a potential name of an atlas.
     * @return  true, if the name can be used for an atlas.
     */
    static bool isNameValid(QString name);
    
    /**
     * Checks if this is a valid atlas.
     *
     * @return  returns true, if this is a valid atlas.
     */
    virtual bool isValid() const {
        return true;
    }
    
    /**
     * Returns the invalid null atlas pointer.
     *
     * [null object pattern]
     *
     * @return  an invalid null atlas.
     */
    static QSharedPointer<Atlas> const & null();
    
    /**
     * Sets a new name for the atlas.
     *
     * @param   name    a new name for the atlas.
     */
    void setName(QString name) override;

private:
    
    /**
     * Applies the regions defined in the JSON array.
     *
     * @param   jsonRegions     the array of regions.
     * @return  true, if the values found have been applied.
     */
    bool applyJSONRegionsArray(QJsonArray const & jsonRegions);

};


/**
 * An invalid Atlas.
 */
class InvalidAtlas final : public Atlas {

public:
    
    /**
     * Constructor.
     */
    InvalidAtlas()
            : Atlas{} {
    }
    
    /**
     * Checks if this is a valid atlas.
     *
     * @return  always false.
     */
    bool isValid() const override {
        return false;
    }
};


}
}


#endif
