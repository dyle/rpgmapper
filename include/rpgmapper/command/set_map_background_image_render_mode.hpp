/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#ifndef RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_RENDER_MODE_HPP
#define RPGMAPPER_MODEL_COMMAND_SET_MAP_BACKGROUND_IMAGE_RENDER_MODE_HPP


#include <QColor>

#include <rpgmapper/command/atlas_command.hpp>
#include <rpgmapper/layer/image_render_mode.hpp>


namespace rpgmapper {
namespace model {
namespace command {


class SetMapBackgroundImageRenderMode : public AtlasCommand {

    QString mapName;
    rpgmapper::model::ImageRenderMode newMode;
    rpgmapper::model::ImageRenderMode oldMode;

public:

    SetMapBackgroundImageRenderMode(AtlasPointer & atlas,
                                    QString const & mapName,
                                    rpgmapper::model::ImageRenderMode newMode);

    ~SetMapBackgroundImageRenderMode() override = default;

    void execute() override;

    QString getDescription() const override;

    void undo() override;
};


}
}
}


#endif
