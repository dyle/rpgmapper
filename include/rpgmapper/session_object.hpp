/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_SESSION_OBJECT_HPP
#define RPGMAPPER_MODEL_SESSION_OBJECT_HPP


namespace rpgmapper {
namespace model {


// fwd
class Session;


/**
 * A Session object is aware of the parent sessio this object belongs to.
 */
class SessionObject {

    Session * session;

public:

    /**
     * Constructor
     *
     * @param   session         the parent session
     */
    SessionObject(Session * session);

    /**
     * Get the session this object belongs to.
     *
     * @return  the session the layer belongs to.
     */
    Session * getSession() {
        return session;
    }

    /**
     * Get the session this object belongs to (const version).
     *
     * @return  the session the layer belongs to.
     */
    Session const * getSession() const {
        return session;
    }
};
    

}
}


#endif
