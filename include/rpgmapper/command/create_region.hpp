/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_CREATE_REGION_HPP
#define RPGMAPPER_MODEL_COMMAND_CREATE_REGION_HPP

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class CreateRegion : public AtlasCommand {

    QString name;

public:

    CreateRegion(AtlasPointer & atlas, QString const & name);

    ~CreateRegion() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
