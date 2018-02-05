/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_CONTROLLER_HPP
#define RPGMAPPER_MODEL_CONTROLLER_HPP


#include <memory>

#include <rpgmapper/types.hpp>
#include <rpgmapper/file.hpp>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


/**
 * This is the main rpgmapper controller instance
 */
class Controller {


public:


    /**
     * Get the current atlas
     *
     * @return  the current atlas instance
     */
    AtlasPointer & atlas();


    /**
     * The file we load/save the atlas from/to.
     *
     * @return  the file instance for load/save operations
     */
    File & file();


    /**
     * Get the singleton controller instance.
     *
     * @return  the singleton controller instance of rpgmapper.
     */
    static Controller & instance();


    /**
     * Load an atlas file, reset data.
     *
     * @param   sFileName       name of the file to load
     * @param   cLog            log of operations done
     * @return  true, for success
     */
    bool load(QString sFileName, QStringList & cLog);


    /**
     * Save an atlas file.
     *
     * @param   sFileName       name of the file to save
     * @param   cLog            log of operations done
     * @return  true, for success
     */
    bool save(QString sFileName, QStringList & cLog);


private:


    /**
     * Ctor.
     */
    Controller();


    class Controller_data;                              /**< internal data type */
    std::shared_ptr<Controller::Controller_data> d;     /**< internal data instance */
};


}
}

#endif
