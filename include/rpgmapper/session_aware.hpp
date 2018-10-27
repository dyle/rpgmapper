/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_SESSION_AWARE_HPP
#define RPGMAPPER_MODEL_SESSION_AWARE_HPP

#include <QSharedPointer>


namespace rpgmapper {
namespace model {


// Foward declaration of a session.
class Session;


/**
 * A Session aware object knows the session it belongs to.
 */
class SessionAware {

    QWeakPointer<rpgmapper::model::Session> session;

public:
    
    /**
     * Constructor
     */
    explicit SessionAware();
    
    /**
     * Gets the current session.
     *
     * @return  the session this object belongs to.
     */
    QSharedPointer<Session> getSession() {
        return session.toStrongRef();
    }
    
    /**
     * Gets the current session (const version).
     *
     * @return  the session this object belongs to.
     */
    QSharedPointer<Session> const getSession() const {
        return session.toStrongRef();
    }
    
    /**
     * Sets a new session.
     *
     * @param   session     the new session instance.
     */
    virtual void setSession(QSharedPointer<Session> session);
};


}
}


#endif
