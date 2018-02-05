/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
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


class Controller;


/**
 * This is the class managing rpgmapper files.
 *
 * Actually it is a mere wrapper around working on gzipped tarballs.
 */
class File {


    friend class rpgmapper::model::Controller;


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
     * Extract the atlas file and apply it to the controller atlas instance.
     */
    void extractAtlasFile();


    /**
     * Load a file, reset data.
     *
     * @param   sFileName       name of the file to load
     * @param   cLog            log of operations done
     * @return  true, for success
     */
    bool load(QString & sFileName, QStringList & cLog);


    /**
     * Save all internal files into a single file.
     *
     * @param   sFileName       name of the file to save
     * @param   cLog            log of operations done
     * @return  true, for success
     */
    bool save(QString & sFileName, QStringList & cLog);


    std::map<QString, QByteArray> m_cFiles;         /**< Data hold by this file. */
    QString m_sFileName;                            /**< Most recent filename used (either load or save). */
};


}
}

#endif
