/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef RPGMAPPER_MODEL_COMMAND_NOP_HPP
#define RPGMAPPER_MODEL_COMMAND_NOP_HPP

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


/**
 * This is command which does nothing: NOP - No operation.
 */
class Nop : public Command {

public:

    /**
     * Destructor.
     */
    ~Nop() override = default;

    /**
     * Executes this command.
     */
    void execute() override {}

    /**
     * Returns a human readable string for this command.
     *
     * @return  a string describing this command.
     */
    QString getDescription() const override {
        return "No operation.";
    }

    /**
     * Undoes the command.
     */
    void undo() override {}
};


}
}
}


#endif
