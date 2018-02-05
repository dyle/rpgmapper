/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


// rpgmapper
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/controller.hpp>

using namespace rpgmapper::model;


// ------------------------------------------------------------
// decl

namespace rpgmapper {
namespace model {

/**
 * Internal data of an Atlas object.
 */
class Controller::Controller_data {

public:

    Controller_data() = default;

    AtlasPointer m_cAtlas;              /**< The atlas managed by this controller. */
    File m_cFile;                       /**< The file management instance. */
};

}
}

// ------------------------------------------------------------
// code


/**
 * Ctor.
 */
Controller::Controller() {
    d = std::make_shared<Controller::Controller_data>();
    d->m_cAtlas = AtlasPointer{new Atlas};
}


/**
 * Get the current atlas
 *
 * @return  the current atlas instance
 */
AtlasPointer & Controller::atlas() {
    return d->m_cAtlas;
}


/**
 * The file we load/save the atlas from/to.
 *
 * @return  the file instance for load/save operations
 */
File & Controller::file() {
    return d->m_cFile;
}


/**
 * Get the singleton controller instance.
 *
 * @return  the singleton controller instance of rpgmapper.
 */
Controller & Controller::instance() {
    static Controller cController;
    return cController;
}


/**
 * Load an atlas file, reset data.
 *
 * @param   sFileName       name of the file to load
 * @param   cLog            log of operations done
 * @return  true, for success
 */
bool Controller::load(QString sFileName, QStringList & cLog) {

    File cFile;
    bool bLoaded = cFile.load(sFileName, cLog);
    if (bLoaded) {
        file() = cFile;
        file().extractAtlasFile();
        atlas()->setModified(false);
    }

    return bLoaded;
}


/**
 * Save an atlas file.
 *
 * @param   sFileName       name of the file to save
 * @param   cLog            log of operations done
 * @return  true, for success
 */
bool Controller::save(QString sFileName, QStringList & cLog) {
    bool bSaved = file().save(sFileName, cLog);
    if (bSaved) {
        atlas()->setModified(false);
    }
    return bSaved;
}
