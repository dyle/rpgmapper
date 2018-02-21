/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP
#define RPGMAPPER_MODEL_COMMAND_REMOVE_REGION_HPP

#include <rpgmapper/command/composite_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class RemoveRegion : public CompositeCommand {

    QString regionName;

public:

    RemoveRegion(AtlasPointer & atlas, QString const & regionName);

    ~RemoveRegion() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
