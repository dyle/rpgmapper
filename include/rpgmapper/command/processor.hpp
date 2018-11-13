/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_PROZESSOR_HPP
#define RPGMAPPER_MODEL_COMMAND_PROZESSOR_HPP

#include <memory>

#include <QObject>
#include <QString>
#include <QSharedPointer>

#include <rpgmapper/command/command_pointer.hpp>
#include <rpgmapper/command/commands.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * The Processor class is capable of executing, redo and undo commands.
 *
 * Pattern: Command (https://en.wikipedia.org/wiki/Command_pattern)
 */
class Processor : public QObject {

    Q_OBJECT

    class Impl;                         /**< Implementation class. */
    std::shared_ptr<Impl> impl;         /**< Pimpl C++ idiom. */

public:
    
    /**
     * Constructor
     *
     * @param   parent      parent QObject.
     */
    explicit Processor(QObject * parent = nullptr);

    /**
     * Destructor.
     */
    ~Processor() override = default;

    /**
     * Execute a single command and put it into our history.
     *
     * @param   command     the command to execute.
     */
    void execute(CommandPointer command);

    /**
     * Returns the list of commands executed so far.
     *
     * @return  a list of commands, oldest on front.
     */
    Commands const & getHistory() const;
    
    /**
     * Returns the list of commands we have currently undone.
     *
     * @return  a list of commands, which we have undone recently. Oldest on front.
     */
    Commands const & getUndone() const;

    /**
     * Returns the amount of modifications we applied since the last saved state.
     *
     * @return  number of changes to the world, since last save state.
     */
    int modifications() const;

    /**
     * Redoes the latest command undone.
     */
    void redo();

    /**
     * Declare the current state as good.
     */
    void resetModifications();

    /**
     * Undoes the last command executed.
     */
    void undo();

signals:

    /**
     * A command has been executed.
     */
    void commandExecuted();

};



}
}
}


#endif
