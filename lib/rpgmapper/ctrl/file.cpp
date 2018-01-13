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

#include <boost/filesystem.hpp>

#include <minizip/unzip.h>
#include <minizip/zip.h>

// rpgmapper
#include <rpgmapper/common_macros.h>
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

    auto zf = unzOpen64(sFileName.c_str());
    if (!zf) {
        return false;
    }

    m_cData.clear();

    char sName[1024];
    auto nZipIter = unzGoToFirstFile(zf);
    while (nZipIter == UNZ_OK) {

        memset(sName, 0, 1024);
        unz_file_info64 zfi = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, {0, 0, 0, 0, 0, 0}};
        unzGetCurrentFileInfo64(zf, &zfi, sName, 1024, nullptr, 0, nullptr, 0);
        auto nSize = static_cast<unsigned int>(zfi.uncompressed_size);

        QByteArray cData;
        cData.resize(nSize);

        char t[1024];
        UNUSED int err = unzReadCurrentFile(zf, t, nSize);
        auto s = std::string(t);

        unzCloseCurrentFile(zf);


        m_cData.insert(std::make_pair(sName, cData));

        nZipIter = unzGoToNextFile(zf);
    }

    return true;
}


/**
 * Save a file.
 *
 * @param   sFileName       name of the file to save
 * @return  true, for success
 */
bool File::save(std::string sFileName) const {

    auto zf = zipOpen64(sFileName.c_str(), APPEND_STATUS_CREATE);
    if (!zf) {
        return false;
    }

    for (auto const & cEntry: m_cData) {
        zip_fileinfo zfi = { {0, 0, 0, 0, 0, 0}, 0, 0, 0};
        zipOpenNewFileInZip64(zf,
                              cEntry.first.c_str(),
                              &zfi,
                              nullptr,
                              0,
                              nullptr,
                              0,
                              nullptr,
                              0,
                              Z_DEFAULT_COMPRESSION,
                              1);
        zipWriteInFileInZip(zf, cEntry.second.constData(), cEntry.second.size());
        zipCloseFileInZip(zf);
    }
    zipClose(zf, nullptr);

    return true;
}
