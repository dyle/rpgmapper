/*
 * file.hpp
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


#ifndef CTRL_FILE_HPP
#define CTRL_FILE_HPP


// ------------------------------------------------------------
// incs

#include <map>

#include <QByteArray>
#include <QString>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace ctrl {


/**
 * This is the class managing rpgmapper files.
 *
 * Actually it is a mere wrapper around working on gzipped tarballs.
 */
class File {


public:


    /**
     * Ctor.
     */
    File() = default;


    /**
     * All the internal byte arrays managed by this instance.
     *
     * @return  all byte arrays of this object instance.
     */
    std::map<QString, QByteArray> & list() { return m_cData; }


    /**
     * Load a file.
     *
     * @param   sFileName       name of the file to load
     * @return  true, for success
     */
    bool load(QString sFileName);


    /**
     * Save a file.
     *
     * @param   sFileName       name of the file to save
     * @return  true, for success
     */
    bool save(QString sFileName) const;


private:


    /**
     * Data hold by this file.
     */
    std::map<QString, QByteArray> m_cData;
};


}
}

#endif
