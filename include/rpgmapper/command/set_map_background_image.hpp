/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_HPP


#include <QImage>

#include <rpgmapper/command/atlas_command.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapBackgroundImage : public AtlasCommand {

    QString mapName;
    QImage newImage;
    QImage oldImage;

public:

    SetMapBackgroundImage(AtlasPointer & atlas, QString const & mapName, QImage newImage);

    ~SetMapBackgroundImage() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
