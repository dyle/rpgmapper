/*
 * file.cpp
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


// ------------------------------------------------------------
// incs

#include <iostream>

#include <quazip/quazip.h>
#include <quazip/quazipfile.h>

// rpgmapper
#include <rpgmapper/ctrl/file.hpp>

using namespace rpgmapper::ctrl;


// ------------------------------------------------------------
// code


/**
 * Load a file.
 *
 * @param   sFileName       name of the file to load
 * @return  true, for success
 */
bool File::load(std::string sFileName) {

    QuaZip cQuaZip;
    cQuaZip.setZipName(sFileName.c_str());
    if (!cQuaZip.open(QuaZip::mdUnzip)) {
        return false;
    }

    for (auto bFilePresent = cQuaZip.goToFirstFile(); bFilePresent; bFilePresent = cQuaZip.goToNextFile()) {

        QuaZipFileInfo zfi;
        if (!cQuaZip.getCurrentFileInfo(&zfi)) {
            return false;
        }

        QuaZipFile zf(&cQuaZip);
        if (!zf.open(QIODevice::ReadOnly)) {
            return false;
        }

        QByteArray cData;
        cData.resize(zfi.uncompressedSize);
        zf.read(cData.data(), zfi.uncompressedSize);

        m_cData.insert(std::make_pair(zf.getActualFileName().toStdString(), cData));
    }

    cQuaZip.close();

    return true;
}


/**
 * Save a file.
 *
 * @param   sFileName       name of the file to save
 * @return  true, for success
 */
bool File::save(std::string sFileName) const {

    QuaZip cQuaZip;

    cQuaZip.setZipName(sFileName.c_str());
    cQuaZip.setFileNameCodec("UTF-8");
    if (!cQuaZip.open(QuaZip::mdCreate, nullptr)) {
        return false;
    }

    for (auto const & cEntry: m_cData) {

        QuaZipFile zf(&cQuaZip);
        QuaZipNewInfo zfi(cEntry.first.c_str());

        if (!zf.open(QIODevice::WriteOnly, zfi)) {
            return false;
        }
        zf.write(cEntry.second.data(), cEntry.second.size());
    }

    cQuaZip.close();

    return true;
}
