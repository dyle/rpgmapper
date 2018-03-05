/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/command/create_map.hpp>
#include <rpgmapper/command/create_region.hpp>
#include <rpgmapper/command/nop.hpp>
#include <rpgmapper/command/remove_map.hpp>
#include <rpgmapper/command/remove_region.hpp>
#include <rpgmapper/command/resize_map.hpp>
#include <rpgmapper/command/set_atlas_name.hpp>
#include <rpgmapper/command/set_map_axis_font.hpp>
#include <rpgmapper/command/set_map_axis_font_color.hpp>
#include <rpgmapper/command/set_map_grid_color.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/command/set_map_numeral_axis.hpp>
#include <rpgmapper/command/set_map_origin.hpp>
#include <rpgmapper/command/set_region_name.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


TEST(MapCommand, SetMapName) {

    AtlasPointer atlas{new Atlas};
    atlas->getCommandProzessor()->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    auto map = atlas->findMap("bar");
    ASSERT_TRUE(map->isValid());
    EXPECT_EQ(map->getName().toStdString(), "bar");

    atlas->getCommandProzessor()->execute(CommandPointer{new SetMapName{atlas, "bar", "baz"}});
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
    EXPECT_EQ(map->getGridLayer()->getGridColor(), QColor{"#FFAA88"});
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
    EXPECT_EQ(map->getAxisLayer()->getAxisFontColor(), QColor{"#883311"});
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
    EXPECT_EQ(map->getAxisLayer()->getAxisFont().toString().toStdString(), font.toString().toStdString());
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
    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "AlphaBig"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "AlphaBig");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "AlphaSmall"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "AlphaSmall");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "Roman"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "Roman");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", true, "Numeric"}});
    EXPECT_EQ(map->getNumeralXAxis()->getName().toStdString(), "Numeric");
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
    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "AlphaBig"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "AlphaBig");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "AlphaSmall"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "AlphaSmall");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "Roman"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "Roman");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());

    prozessor->execute(CommandPointer{new SetMapNumeralAxis{atlas, "bar", false, "Numeric"}});
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), "Numeric");
    prozessor->undo();
    EXPECT_EQ(map->getNumeralYAxis()->getName().toStdString(), defaultNumeral.toStdString());
}
