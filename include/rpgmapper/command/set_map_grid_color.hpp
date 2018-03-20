/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_GRID_COLOR_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_GRID_COLOR_HPP


#include <QColor>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapGridColor : public AtlasCommand {

    QString mapName;
    QColor newColor;
    QColor oldColor;

public:

    SetMapGridColor(AtlasPointer & atlas, QString const & mapName, QColor newColor);

    ~SetMapGridColor() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif