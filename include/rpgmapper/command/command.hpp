/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_COMMAND_HPP
#define RPGMAPPER_MODEL_COMMAND_COMMAND_HPP

#include <list>

#include <QString>
#include <QSharedPointer>


namespace rpgmapper {
namespace model {
namespace command {


class Command {

public:

    virtual ~Command() = default;

    virtual void execute() = 0;

    virtual QString getDescription() const = 0;

    virtual void undo() = 0;
};

using CommandPointer = QSharedPointer<Command>;

using Commands = std::list<CommandPointer>;


}
}
}


#endif
