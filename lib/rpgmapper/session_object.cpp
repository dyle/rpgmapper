/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <rpgmapper/exception/invalid_session.hpp>
#include <rpgmapper/session_object.hpp>

using namespace rpgmapper::model;


SessionObject::SessionObject(QSharedPointer<Session> session) : session{session} {
    if (!session) {
        throw exception::invalid_session();
    }
}

