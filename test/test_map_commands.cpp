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
#include <rpgmapper/command/set_map_margin.hpp>
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
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());
    
    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getName().toStdString(), "bar");
    
    processor->execute(CommandPointer{new SetMapName{"bar", "baz"}});
    map = session->findMap("baz");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getName().toStdString(), "baz");
}


TEST(MapCommand, ResizeMap) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());
    
    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getCoordinateSystem()->getSize().width(), 10);
    EXPECT_EQ(map->getCoordinateSystem()->getSize().height(), 10);
    
    processor->execute(CommandPointer{new ResizeMap{"bar", QSize{100, 50}}});
    EXPECT_EQ(map->getCoordinateSystem()->getSize().width(), 100);
    EXPECT_EQ(map->getCoordinateSystem()->getSize().height(), 50);
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getSize().width(), 10);
    EXPECT_EQ(map->getCoordinateSystem()->getSize().height(), 10);
}


TEST(MapCommand, SetMapOrigin) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());
    
    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
    
    processor->execute(CommandPointer{new SetMapOrigin{"bar",
                                                       rpgmapper::model::CoordinatesOrigin::topLeft}});
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::topLeft);
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
    
    processor->execute(CommandPointer{new SetMapOrigin{"bar",
                                                       rpgmapper::model::CoordinatesOrigin::topRight}});
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::topRight);
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
    
    processor->execute(CommandPointer{new SetMapOrigin{"bar",
                                                       rpgmapper::model::CoordinatesOrigin::bottomRight}});
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomRight);
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
    
    processor->execute(CommandPointer{new SetMapOrigin{"bar",
                                                       rpgmapper::model::CoordinatesOrigin::bottomLeft}});
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getOrigin(), rpgmapper::model::CoordinatesOrigin::bottomLeft);
}


TEST(MapCommand, SetMapGridColor) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());
    
    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());
    
    processor->execute(CommandPointer{new SetMapGridColor{"bar", QColor{"#FFAA88"}}});
    EXPECT_EQ(map->getLayers().getGridLayer()->getColor(), QColor{"#FFAA88"});
}


TEST(MapCommand, SetMapAxisFontColor) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());
    
    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());
    
    processor->execute(CommandPointer{new SetMapAxisFontColor{"bar", QColor{"#883311"}}});
    EXPECT_EQ(map->getLayers().getAxisLayer()->getColor(), QColor{"#883311"});
}


TEST(MapCommand, SetMapAxisFont) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());

    QFont font{"Arial", 16};
    processor->execute(CommandPointer{new SetMapAxisFont{"bar", font}});
    EXPECT_EQ(map->getLayers().getAxisLayer()->getFont().toString().toStdString(), font.toString().toStdString());
}


TEST(MapCommand, SetMapNumeralXAxis) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());

    auto defaultNumeral = map->getCoordinateSystem()->getNumeralXAxis()->getName();
    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", true, "alphaBig"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), "alphaBig");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", true, "alphaSmall"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), "alphaSmall");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", true, "roman"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), "roman");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", true, "numeric"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), "numeric");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());
}


TEST(MapCommand, SetMapNumeralYAxis) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());

    auto defaultNumeral = map->getCoordinateSystem()->getNumeralYAxis()->getName();
    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", false, "alphaBig"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), "alphaBig");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", false, "alphaSmall"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), "alphaSmall");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", false, "roman"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), "roman");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    processor->execute(CommandPointer{new SetMapNumeralAxis{"bar", false, "numeric"}});
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), "numeric");
    processor->undo();
    EXPECT_EQ(map->getCoordinateSystem()->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());
}


TEST(MapCommand, SetMapBackgroundColor) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());

    processor->execute(CommandPointer{new SetMapBackgroundColor{"bar", QColor{"#112233"}}});
    EXPECT_EQ(map->getLayers().getBackgroundLayer()->getColor(), QColor{"#112233"});
}


TEST(MapCommand, SetMapBackgroundRendering) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());

    processor->execute(CommandPointer{new SetMapBackgroundRendering{"bar", "color"}});
    EXPECT_TRUE(map->getLayers().getBackgroundLayer()->isColorRendered());
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isImageRendered());
    processor->execute(CommandPointer{new SetMapBackgroundRendering{"bar", "image"}});
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isColorRendered());
    EXPECT_TRUE(map->getLayers().getBackgroundLayer()->isImageRendered());
}


TEST(MapCommand, SetMapBackgroundImageRenderMode) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());

    processor->execute(CommandPointer{new SetMapBackgroundImageRenderMode{"bar", ImageRenderMode::plain}});
    EXPECT_TRUE(map->getLayers().getBackgroundLayer()->isImageRenderedPlain());
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isImageRenderedScaled());
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isImageRenderedTiled());

    processor->execute(CommandPointer{new SetMapBackgroundImageRenderMode{"bar", ImageRenderMode::scaled}});
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isImageRenderedPlain());
    EXPECT_TRUE(map->getLayers().getBackgroundLayer()->isImageRenderedScaled());
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isImageRenderedTiled());

    processor->execute(CommandPointer{new SetMapBackgroundImageRenderMode{"bar", ImageRenderMode::tiled}});
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isImageRenderedPlain());
    EXPECT_FALSE(map->getLayers().getBackgroundLayer()->isImageRenderedScaled());
    EXPECT_TRUE(map->getLayers().getBackgroundLayer()->isImageRenderedTiled());
}


TEST(MapCommand, SetMapMargins) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    auto map = session->findMap("bar");
    ASSERT_TRUE(map->isValid());

    processor->execute(CommandPointer{new SetMapMargin{"bar", 1.0}});
    auto margin = map->getCoordinateSystem()->getMargin();
    EXPECT_EQ(margin, 1.0);
    
    processor->execute(CommandPointer{new SetMapMargin{"bar", 0.0}});
    margin = map->getCoordinateSystem()->getMargin();
    EXPECT_EQ(margin, 0.0);
}
