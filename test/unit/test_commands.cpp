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
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/command/set_map_origin.hpp>
#include <rpgmapper/command/set_region_name.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


TEST(ProzessorTest, DoNopCommand) {

    Prozessor prozessor;

    EXPECT_EQ(prozessor.modifications(), 0);
    EXPECT_TRUE(prozessor.getHistory().empty());
    prozessor.execute(CommandPointer{new Nop});
    EXPECT_NE(prozessor.modifications(), 0);

    EXPECT_EQ(prozessor.getHistory().size(), 1);
    prozessor.undo();
    EXPECT_EQ(prozessor.modifications(), 0);
    EXPECT_TRUE(prozessor.getHistory().empty());
    prozessor.redo();
    EXPECT_EQ(prozessor.getHistory().size(), 1);
    EXPECT_NE(prozessor.modifications(), 0);
}


TEST(ProzessorTest, AtlasChanged) {

    AtlasPointer atlas{new Atlas};
    EXPECT_FALSE(atlas->isModified());

    atlas->getCommandProzessor()->execute(CommandPointer{new SetAtlasName{atlas, "foo"}});
    EXPECT_TRUE(atlas->isModified());

    atlas->getCommandProzessor()->undo();
    EXPECT_FALSE(atlas->isModified());

    atlas->getCommandProzessor()->redo();
    EXPECT_TRUE(atlas->isModified());
}


TEST(ProzessorTest, SetAtlasName) {

    AtlasPointer atlas{new Atlas};
    atlas->setName("foo");

    atlas->getCommandProzessor()->execute(CommandPointer{new SetAtlasName{atlas, "bar"}});
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(atlas->getCommandProzessor()->getHistory().size(), 1);
    EXPECT_EQ(atlas->getCommandProzessor()->getHistory().front()->getDescription().toStdString(),
              "Set atlas name to bar.");
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 0);

    atlas->getCommandProzessor()->undo();
    EXPECT_EQ(atlas->getName().toStdString(), "foo");
    EXPECT_EQ(atlas->getCommandProzessor()->getHistory().size(), 0);
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 1);
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().front()->getDescription().toStdString(),
              "Set atlas name to bar.");

    atlas->getCommandProzessor()->redo();
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(atlas->getCommandProzessor()->getHistory().size(), 1);
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 0);

    atlas->getCommandProzessor()->undo();
    EXPECT_EQ(atlas->getName().toStdString(), "foo");
    EXPECT_EQ(atlas->getCommandProzessor()->getHistory().size(), 0);
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 1);

    atlas->getCommandProzessor()->redo();
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(atlas->getCommandProzessor()->getHistory().size(), 1);
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 0);
}


TEST(ProzessorTest, NewCommandResetsUndoneList) {

    AtlasPointer atlas{new Atlas};
    atlas->setName("foo");

    atlas->getCommandProzessor()->execute(CommandPointer{new SetAtlasName{atlas, "bar"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new SetAtlasName{atlas, "baz"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new SetAtlasName{atlas, "bam"}});
    atlas->getCommandProzessor()->undo();
    atlas->getCommandProzessor()->undo();
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 2);

    atlas->getCommandProzessor()->execute(CommandPointer{new SetAtlasName{atlas, "bag"}});
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 0);
}


TEST(ProzessorTest, CreateRegion) {

    AtlasPointer atlas{new Atlas};

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateRegion{atlas, "foo"}});

    auto regionNames = atlas->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());

    atlas->getCommandProzessor()->undo();

    regionNames = atlas->getAllRegionNames();
    EXPECT_EQ(regionNames.find("foo"), regionNames.end());

    atlas->getCommandProzessor()->redo();
    regionNames = atlas->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());

    EXPECT_TRUE(atlas->isModified());
}


TEST(ProzessorTest, CreateMap) {

    AtlasPointer atlas{new Atlas};

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});

    auto regionNames = atlas->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());

    auto mapNames = atlas->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());

    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());
    auto map = region->findMap("bar");
    EXPECT_TRUE(map->isValid());

    atlas->getCommandProzessor()->undo();

    mapNames = atlas->getAllMapNames();
    EXPECT_EQ(mapNames.find("bar"), mapNames.end());

    atlas->getCommandProzessor()->redo();

    EXPECT_TRUE(atlas->isModified());
}


TEST(ProzessorTest, RemoveMap) {

    AtlasPointer atlas{new Atlas};

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});

    auto mapNames = atlas->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());

    atlas->getCommandProzessor()->execute(CommandPointer{new RemoveMap{atlas, "foo", "bar"}});

    mapNames = atlas->getAllMapNames();
    EXPECT_EQ(mapNames.find("bar"), mapNames.end());

    atlas->getCommandProzessor()->undo();

    mapNames = atlas->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());
}

TEST(ProzessorTest, RemoveRegion) {

    AtlasPointer atlas{new Atlas};

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateRegion{atlas, "foo"}});

    auto regionNames = atlas->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());

    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{atlas, "foo", "bar"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{atlas, "foo", "baz"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new CreateMap{atlas, "foo", "bam"}});

    auto mapNames = atlas->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());
    EXPECT_NE(mapNames.find("baz"), mapNames.end());
    EXPECT_NE(mapNames.find("bam"), mapNames.end());

    atlas->getCommandProzessor()->execute(CommandPointer{new RemoveRegion{atlas, "foo"}});

    regionNames = atlas->getAllRegionNames();
    EXPECT_EQ(regionNames.find("foo"), regionNames.end());
    mapNames = atlas->getAllMapNames();
    EXPECT_EQ(mapNames.find("bar"), mapNames.end());
    EXPECT_EQ(mapNames.find("baz"), mapNames.end());
    EXPECT_EQ(mapNames.find("bam"), mapNames.end());

    atlas->getCommandProzessor()->undo();

    regionNames = atlas->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());
    mapNames = atlas->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());
    EXPECT_NE(mapNames.find("baz"), mapNames.end());
    EXPECT_NE(mapNames.find("bam"), mapNames.end());
}


TEST(ProzessorTest, SetRegionName) {

    AtlasPointer atlas{new Atlas};
    atlas->getCommandProzessor()->execute(CommandPointer{new CreateRegion{atlas, "foo"}});
    auto region = atlas->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    atlas->getCommandProzessor()->execute(CommandPointer{new SetRegionName{atlas, "foo", "bar"}});
    region = atlas->findRegion("bar");
    ASSERT_TRUE(region->isValid());
    EXPECT_EQ(region->getName().toStdString(), "bar");
}


TEST(ProzessorTest, SetMapName) {

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


TEST(ProzessorTest, ResizeMap) {

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


TEST(ProzessorTest, SetMapOrigin) {

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
