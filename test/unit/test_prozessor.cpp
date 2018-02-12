/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

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
