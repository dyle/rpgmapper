/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_REGION_NAME_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_REGION_NAME_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetRegionName : public AtlasCommand {

    QString newName;
    QString oldName;

public:

    SetRegionName(AtlasPointer & atlas, QString const & oldName, QString const & newName);

    ~SetRegionName() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
