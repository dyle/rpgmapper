/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_IO_RESULT_HPP
#define RPGMAPPER_MODEL_IO_RESULT_HPP

#include <QStringList>
#include <utility>


namespace rpgmapper {
namespace model {
namespace io {


/**
 * This is the result of of an I/O operation.
 */
class Result {
    
    bool success = false;           /**< Success information. */
    QStringList log;                /**< This field contains the history of operatoins. */

public:
    
    /**
     * Constructor.
     *
     * @param   success     has the operation succeeded flag
     */
    explicit Result(bool success = false)
            : Result{success, QStringList{}} {
    }
    
    /**
     * Constructor.
     *
     * @param   success     has the operation succeeded flag
     * @param   log         history of operations performed as human readable strings.
     */
    Result(bool success, QStringList log)
            : success{success},
              log{std::move(log)} {
    }
    
    /**
     * Destructor.
     */
    virtual ~Result() = default;
    
    /**
     * Gets the history performed.
     *
     * @return  the history of operations as human readable strings.
     */
    QStringList & getLog() {
        return log;
    }
    
    /**
     * Gets the history performed (const version).
     *
     * @return  the history of operations as human readable strings.
     */
    QStringList const & getLog() const {
        return log;
    }
    
    /**
     * Checks if the operation was successful.
     *
     * @return  True, if the operation was successful.
     */
    bool hasSuccess() const {
        return success;
    }
};


}
}
}

#endif
