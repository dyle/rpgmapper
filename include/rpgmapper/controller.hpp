/*
 * controller.hpp
 *
 * Copyright (C) 2015-2018 Oliver Maurhart, <dyle71@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef CTRL_CONTROLLER_HPP
#define CTRL_CONTROLLER_HPP


// ------------------------------------------------------------
// incs

#include <memory>


// rpgmapper
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
