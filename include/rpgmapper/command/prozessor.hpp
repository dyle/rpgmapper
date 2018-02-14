/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_PROZESSOR_HPP
#define RPGMAPPER_MODEL_COMMAND_PROZESSOR_HPP


#include <memory>

#include <QString>
#include <QSharedPointer>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class Prozessor {

    class Impl;
    std::shared_ptr<Impl> impl;

public:

    Prozessor();

    void execute(CommandPointer command);

    Commands const & getHistory() const;

    Commands const & getUndone() const;

    void redo();

    void undo();

};

using ProzessorPointer = QSharedPointer<Prozessor>;


}
}
}


#endif