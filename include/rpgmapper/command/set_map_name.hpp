/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_NAME_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapName : public AtlasCommand {

    QString newName;
    QString oldName;

public:

    SetMapName(AtlasPointer & atlas, QString const & oldName, QString const & newName);

    ~SetMapName() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
