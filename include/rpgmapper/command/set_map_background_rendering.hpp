/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_RENDERING_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_RENDERING_HPP


#include <QColor>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapBackgroundRendering : public AtlasCommand {

    QString mapName;
    QString newRendering;
    QString oldRendering;

public:

    SetMapBackgroundRendering(AtlasPointer & atlas, QString const & mapName, QString newRendering);

    ~SetMapBackgroundRendering() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
