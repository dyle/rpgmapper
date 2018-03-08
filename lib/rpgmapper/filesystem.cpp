/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <QFile>

#include <rpgmapper/filesystem.hpp>

using namespace rpgmapper::model;


QDir getPrefixPath();

QFile const & getProcessImageFile();


QDir rpgmapper::model::getApplicationDataSystemPath() {

    auto dataPath = getPrefixPath();

#ifdef __linux__
    dataPath.cd("share");
    dataPath.cd("rpgmapper");
#endif

#ifdef __WIN32__
    // the prefix path *is* the system application data path
#endif

    return dataPath;
}


QDir rpgmapper::model::getApplicationDataUserPath() {

    auto dataPath = QDir::home();

#ifdef __linux__
    if (!dataPath.mkpath(".local/share/rpgmapper")) {
        throw std::runtime_error("Unable to create local data user path.");
    }
    dataPath.cd(".local");
    dataPath.cd("share");
    dataPath.cd("rpgmapper");
#endif

#ifdef __WIN32__
    if (!dataPath.mkpath("AppData\\Local\\RPGMapper")) {
        throw std::runtime_error("Unable to create local data user path.");
    }
    dataPath.cd("AppData");
    dataPath.cd("Local");
    dataPath.cd("RPGMapper");
#endif

    return dataPath;
}


QDir getPrefixPath() {

    QDir prefixPath(getProcessImageFile().fileName());
    prefixPath.cdUp();

#ifdef __linux__
    // on Linux we might have "/usr/local/bin/rpgmapper"
    // therefore the prefix path is "/usr/local"
    prefixPath.cdUp();
#endif

#ifdef __WIN32__
    // on Windows we might have "C:\Program Files\RPGMapper\rpgmapper.exe"
    // therefore the prefix path is ""C:\Program Files\RPGMapper"
#endif

    return prefixPath;
}


QFile const & getProcessImageFile() {

    static QFile processImageFile;

    if (processImageFile.fileName().isEmpty()) {

#ifdef __linux__
        processImageFile.setFileName(QFile::symLinkTarget("/proc/self/exe"));
#endif

#ifdef __WIN32__
        char fileName[MAX_PATH];
        GetModuleFileName(GetModuleHandle(nullptr), fileName, MAX_PATH);
        processImageFile.setFileName(fileName);
#endif

    }

    return processImageFile;
}
