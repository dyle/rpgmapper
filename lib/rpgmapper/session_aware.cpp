/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/session_aware.hpp>

using namespace rpgmapper::model;


SessionAware::SessionAware() {
}


void SessionAware::setSession(QSharedPointer<Session> session) {
    this->session = session;
}
