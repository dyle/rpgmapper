/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/command/atlas_set_name.hpp>
#include <rpgmapper/command/nop.hpp>
#include <rpgmapper/command/prozessor.hpp>

using namespace rpgmapper::model::command;


TEST(ProzessorTest, DoNopCommand) {

    Prozessor prozessor;

    EXPECT_TRUE(prozessor.getList().empty());
    prozessor.execute(CommandPointer{new Nop});

    EXPECT_EQ(prozessor.getList().size(), 1);
    prozessor.undo();
    EXPECT_TRUE(prozessor.getList().empty());
    prozessor.redo();
    EXPECT_EQ(prozessor.getList().size(), 1);
}


TEST(ProzessorTest, SetAtlasName) {

    AtlasPointer atlas{new Atlas};
    atlas->setName("foo");

    atlas->getCommandProzessor()->execute(CommandPointer{new AtlasSetName{atlas, "bar"}});
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(atlas->getCommandProzessor()->getList().size(), 1);

    atlas->getCommandProzessor()->undo();
    EXPECT_EQ(atlas->getName().toStdString(), "foo");
    EXPECT_EQ(atlas->getCommandProzessor()->getList().size(), 0);

    atlas->getCommandProzessor()->redo();
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(atlas->getCommandProzessor()->getList().size(), 1);

    atlas->getCommandProzessor()->undo();
    EXPECT_EQ(atlas->getName().toStdString(), "foo");
    EXPECT_EQ(atlas->getCommandProzessor()->getList().size(), 0);

    atlas->getCommandProzessor()->redo();
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(atlas->getCommandProzessor()->getList().size(), 1);
}
