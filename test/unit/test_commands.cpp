/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/command/atlas_set_name.hpp>
#include <rpgmapper/command/create_region.hpp>
#include <rpgmapper/command/nop.hpp>

using namespace rpgmapper::model::command;


TEST(ProzessorTest, DoNopCommand) {

    Prozessor prozessor;

    EXPECT_TRUE(prozessor.getHistory().empty());
    prozessor.execute(CommandPointer{new Nop});

    EXPECT_EQ(prozessor.getHistory().size(), 1);
    prozessor.undo();
    EXPECT_TRUE(prozessor.getHistory().empty());
    prozessor.redo();
    EXPECT_EQ(prozessor.getHistory().size(), 1);
}


TEST(ProzessorTest, AtlasChanged) {

    AtlasPointer atlas{new Atlas};
    EXPECT_FALSE(atlas->isModified());

    atlas->getCommandProzessor()->execute(CommandPointer{new AtlasSetName{atlas, "foo"}});
    EXPECT_TRUE(atlas->isModified());

    atlas->getCommandProzessor()->undo();
    EXPECT_FALSE(atlas->isModified());

    atlas->getCommandProzessor()->redo();
    EXPECT_TRUE(atlas->isModified());
}


TEST(ProzessorTest, SetAtlasName) {

    AtlasPointer atlas{new Atlas};
    atlas->setName("foo");

    atlas->getCommandProzessor()->execute(CommandPointer{new AtlasSetName{atlas, "bar"}});
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

    atlas->getCommandProzessor()->execute(CommandPointer{new AtlasSetName{atlas, "bar"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new AtlasSetName{atlas, "baz"}});
    atlas->getCommandProzessor()->execute(CommandPointer{new AtlasSetName{atlas, "bam"}});
    atlas->getCommandProzessor()->undo();
    atlas->getCommandProzessor()->undo();
    EXPECT_EQ(atlas->getCommandProzessor()->getUndone().size(), 2);

    atlas->getCommandProzessor()->execute(CommandPointer{new AtlasSetName{atlas, "bag"}});
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
}
