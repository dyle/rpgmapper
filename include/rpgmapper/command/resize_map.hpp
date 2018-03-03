/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_RESIZE_MAP_HPP
#define RPGMAPPER_MODEL_COMMAND_RESIZE_MAP_HPP

#include <QSize>
#include <QString>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class ResizeMap : public AtlasCommand {

    QString mapName;
    QSize newSize;
    QSize oldSize;

public:

    ResizeMap(AtlasPointer & atlas, QString const & mapName, QSize newSize);

    ~ResizeMap() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
