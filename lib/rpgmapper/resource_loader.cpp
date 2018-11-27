/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <QApplication>
#include <QDateTime>
#include <QTimer>

#include <rpgmapper/resource_loader.hpp>

using namespace rpgmapper::model;


/**
 * Appends a single entry to the log, keeps formatting with timestamps.
 *
 * @param   log         the log to fill.
 * @param   entry       the entry to add
 */
static void appendLog(QStringList & log, QString entry);


ResourceLoader::ResourceLoader(QObject * parent) : QObject{parent} {
}


void ResourceLoader::load(QStringList & log) {
    
    appendLog(log, "Staring up...");
    
    ResourceLoadingEvent event = {"Blah", 12, 24};
    emit loading(event);
    QApplication::processEvents();
    
    QTimer::singleShot(2000, this, &ResourceLoader::done);
}


void appendLog(QStringList & log, QString entry) {
    auto now = QDateTime::currentDateTime();
    log.append(QString{"%1 - %2"}.arg(now.toString(Qt::ISODate)).arg(entry));
}
