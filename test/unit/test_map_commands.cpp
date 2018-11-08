/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/command/create_map.hpp>
#include <rpgmapper/command/create_region.hpp>
#include <rpgmapper/command/nop.hpp>
#include <rpgmapper/command/processor.hpp>
#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/command/remove_region.hpp>
#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/command/set_atlas_name.hpp>
#include <rpgmapper/command/set_map_axis_font.hpp>
#include <rpgmapper/command/set_map_axis_font_color.hpp>
#include <rpgmapper/command/set_map_background_color.hpp>
#include <rpgmapper/command/set_map_background_image_render_mode.hpp>
#include <rpgmapper/command/set_map_background_rendering.hpp>
#include <rpgmapper/command/set_map_grid_color.hpp>
#include <rpgmapper/command/set_map_margins.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/command/set_map_numeral_axis.hpp>
#include <rpgmapper/command/set_map_origin.hpp>
#include <rpgmapper/command/set_region_name.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


TEST(MapCommand, SetMapName) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProzessor();
    
    using CommandPointer = QSharedPointer<rpgmapper::model::command::Command>;
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getName().toStdString(), "bar");

    atlas->getCommandProzessor()->execute(CommandPointer{new SetMapName{"bar", "baz"}});
    map = atlas->findMap("baz");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getName().toStdString(), "baz");
}


TEST(MapCommand, ResizeMap) {

    AtlasPointer atlas{new Atlas};
    atlas->getCommandProzessor()->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getSize().width(), 10);
    EXPECT_EQ(map->getSize().height(), 10);

    atlas->getCommandProzessor()->execute(CommandPointer{new ResizeMap{atlas, "bar", QSize{100, 50}}});
    EXPECT_EQ(map->getSize().width(), 100);
    EXPECT_EQ(map->getSize().height(), 50);
    atlas->getCommandProzessor()->undo();
    EXPECT_EQ(map->getSize().width(), 10);
    EXPECT_EQ(map->getSize().height(), 10);
}


TEST(MapCommand, SetMapOrigin) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);

    prozessor->execute(CommandPointer{new SetMapOrigin{atlas, "bar",
                                                       rpgmapper::model::CoordinatesOrigin::topLeft}});
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::topLeft);
    prozessor->undo();
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);

    prozessor->execute(CommandPointer{new SetMapOrigin{atlas, "bar",
                                                       rpgmapper::model::CoordinatesOrigin::topRight}});
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::topRight);
    prozessor->undo();
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);

    prozessor->execute(CommandPointer{new SetMapOrigin{atlas, "bar",
                                                       rpgmapper::model::CoordinatesOrigin::bottomRight}});
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomRight);
    prozessor->undo();
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);

    prozessor->execute(CommandPointer{new SetMapOrigin{atlas, "bar",
                                                       rpgmapper::model::CoordinatesOrigin::bottomLeft}});
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
    prozessor->undo();
    EXPECT_EQ(map->getCoordinateSystem().getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
}


TEST(MapCommand, SetMapGridColor) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    prozessor->execute(CommandPointer{new SetMapGridColor{atlas, "bar", QColor{"#FFAA88"}}});
    EXPECT_EQ(map->getGridLayer()->getColor(), QColor{"#FFAA88"});
}


TEST(MapCommand, SetMapAxisFontColor) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    prozessor->execute(CommandPointer{new SetMapAxisFontColor{atlas, "bar", QColor{"#883311"}}});
    EXPECT_EQ(map->getAxisLayer()->getColor(), QColor{"#883311"});
}


TEST(MapCommand, SetMapAxisFont) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    QFont font{"Arial", 16};
    prozessor->execute(CommandPointer{new SetMapAxisFont{atlas, "bar", font}});
    EXPECT_EQ(map->getAxisLayer()->getFont().toString().toStdString(), font.toString().toStdString());
}


TEST(MapCommand, SetMapNumeralXAxis) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    auto defaultNumeral = map->getNumeralXAxis()->getName();
    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "alphaBig"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "alphaBig");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "alphaSmall"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "alphaSmall");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "roman"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "roman");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "numeric"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "numeric");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());
}


TEST(MapCommand, SetMapNumeralYAxis) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    auto defaultNumeral = map->getNumeralYAxis()->getName();
    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "alphaBig"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "alphaBig");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "alphaSmall"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "alphaSmall");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "roman"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "roman");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "numeric"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "numeric");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());
}


TEST(MapCommand, SetMapBackgroundColor) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    prozessor->execute(CommandPointer{new SetMapBackgroundColor{atlas, "bar", QColor{"#112233"}}});
    EXPECT_EQ(map->getBackgroundLayer()->getColor(), QColor{"#112233"});
}


TEST(MapCommand, SetMapBackgroundRendering) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    prozessor->execute(CommandPointer{new SetMapBackgroundRendering{atlas, "bar", "color"}});
    EXPECT_TRUE(map->getBackgroundLayer()->isColorRendered());
    EXPECT_FALSE(map->getBackgroundLayer()->isImageRendered());
    prozessor->execute(CommandPointer{new SetMapBackgroundRendering{atlas, "bar", "image"}});
    EXPECT_FALSE(map->getBackgroundLayer()->isColorRendered());
    EXPECT_TRUE(map->getBackgroundLayer()->isImageRendered());
}


TEST(MapCommand, SetMapBackgroundImageRenderMode) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    prozessor->execute(CommandPointer{new SetMapBackgroundImageRenderMode{atlas, "bar", ImageRenderMode::plain}});
    EXPECT_TRUE(map->getBackgroundLayer()->isImageRenderedPlain());
    EXPECT_FALSE(map->getBackgroundLayer()->isImageRenderedScaled());
    EXPECT_FALSE(map->getBackgroundLayer()->isImageRenderedTiled());

    prozessor->execute(CommandPointer{new SetMapBackgroundImageRenderMode{atlas, "bar", ImageRenderMode::scaled}});
    EXPECT_FALSE(map->getBackgroundLayer()->isImageRenderedPlain());
    EXPECT_TRUE(map->getBackgroundLayer()->isImageRenderedScaled());
    EXPECT_FALSE(map->getBackgroundLayer()->isImageRenderedTiled());

    prozessor->execute(CommandPointer{new SetMapBackgroundImageRenderMode{atlas, "bar", ImageRenderMode::tiled}});
    EXPECT_FALSE(map->getBackgroundLayer()->isImageRenderedPlain());
    EXPECT_FALSE(map->getBackgroundLayer()->isImageRenderedScaled());
    EXPECT_TRUE(map->getBackgroundLayer()->isImageRenderedTiled());
}


TEST(MapCommand, SetMapMargins) {

    AtlasPointer atlas{new Atlas};
    auto & prozessor = atlas->getCommandProzessor();
    prozessor->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    prozessor->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());

    prozessor->execute(CommandPointer{new SetMapMargins{atlas, "bar", QMargins{11, 22, 33, 44}}});
    auto margins = map->getBackgroundLayer()->getMargins();
    EXPECT_EQ(margins.left(), 11);
    EXPECT_EQ(margins.top(), 22);
    EXPECT_EQ(margins.right(), 33);
    EXPECT_EQ(margins.bottom(), 44);

    prozessor->execute(CommandPointer{new SetMapMargins{atlas, "bar", QMargins{9, 8, 7, 6}}});
    margins = map->getBackgroundLayer()->getMargins();
    EXPECT_EQ(margins.left(), 9);
    EXPECT_EQ(margins.top(), 8);
    EXPECT_EQ(margins.right(), 7);
    EXPECT_EQ(margins.bottom(), 6);

    prozessor->execute(CommandPointer{new SetMapMargins{atlas, "bar", QMargins{0, 0, 0, 0}}});
    margins = map->getBackgroundLayer()->getMargins();
    EXPECT_EQ(margins.left(), 0);
    EXPECT_EQ(margins.top(), 0);
    EXPECT_EQ(margins.right(), 0);
    EXPECT_EQ(margins.bottom(), 0);
}
