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
#include <QStringList>


// ------------------------------------------------------------
// decl


namespace rpgmapper {
namespace model {


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
     * Get the most recent filename used.
     *
     * @return  the most recent filename
     */
    QString const & filename() const { return m_sFileName; }


    /**
     * All the internal files as arrays managed by this instance.
     *
     * @return  all byte arrays of this object instance.
     */
    std::map<QString, QByteArray> & files() { return m_cFiles; }


    /**
     * Load a file, reset data.
     *
     * @param   sFileName       name of the file to load
     * @param   cLog            log of operations done
     * @return  true, for success
     */
    bool load(QString sFileName, QStringList & cLog);


    /**
     * Save all internal files into a single file.
     *
     * @param   sFileName       name of the file to save
     * @param   cLog            log of operations done
     * @return  true, for success
     */
    bool save(QString sFileName, QStringList & cLog);


private:


    /**
     * Get the file name to save.
     * If the given filename is set, then we remember this one in
     * future calls. If the given filename is empty, this method
     * places the once remembered filename in the passed parameter.
     *
     * @param   sFileName   will be the new filename to save/load
     * @return  true, if we have a valid filename
     */
    bool acquireFileName(QString & sFileName);


    /**
     * Gather the internal atlas file.
     */
    void collectAtlasFile();


    /**
     * Collect all necessary internal files.
     */
    void collectInternalFiles();


    std::map<QString, QByteArray> m_cFiles;         /**< Data hold by this file. */
    mutable QString m_sFileName;                    /**< Most recent filename used (either load or save). */
};


}
}

#endif
