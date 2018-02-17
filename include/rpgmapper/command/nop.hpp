/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_NOP_HPP
#define RPGMAPPER_MODEL_COMMAND_NOP_HPP


#include <memory>

#include <QString>
#include <QSharedPointer>

#include <rpgmapper/command/command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class Nop : public Command {

public:

    ~Nop() override = default;

    void execute() override {}

    QString getDescription() const override { return "No operation."; }

    void undo() override {}
};


}
}
}


#endif
