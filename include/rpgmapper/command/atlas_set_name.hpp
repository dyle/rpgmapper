/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_ATLAS_SET_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_ATLAS_SET_NAME_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class AtlasSetName : public AtlasCommand {

    QString newName;
    QString oldName;

public:

    AtlasSetName(AtlasPointer & atlas, QString const & name);

    ~AtlasSetName() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
