/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_COMPOSITE_COMMAND_HPP
#define RPGMAPPER_MODEL_COMMAND_COMPOSITE_COMMAND_HPP


#include <memory>

#include <QString>
#include <QSharedPointer>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class CompositeCommand : public AtlasCommand {

    Commands commands;

public:

    CompositeCommand(rpgmapper::model::AtlasPointer & atlas) : AtlasCommand{atlas} {}

    ~CompositeCommand() override = default;

    void execute() override;

    void undo() override;

protected:

    void addCommand(CommandPointer command);

    void clearCommands();
};


}
}
}


#endif
