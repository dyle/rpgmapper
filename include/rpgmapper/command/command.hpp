/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_COMMAND_HPP
#define RPGMAPPER_MODEL_COMMAND_COMMAND_HPP

#include <list>

#include <QSharedPointer>
#include <QString>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This class implements the Command pattern including undo functionality.
 *
 * Pattern: Command (https://en.wikipedia.org/wiki/Command_pattern)
 *
 * This is an pure abstract class. Derived classes to implement concrete command actions.
 */
class Command {

public:

    /**
     * Destructor.
     */
    virtual ~Command() = default;

    /**
     * Run/execute this command.
     */
    virtual void execute() = 0;

    /**
     * Give a human readable description of this command.
     */
    virtual QString getDescription() const = 0;

    /**
     * Undo the action, reverse the current state.
     */
    virtual void undo() = 0;
};


/**
 * A series of Command instances.
 */
using Commands = std::list<QSharedPointer<Command>>;


}
}
}


#endif
