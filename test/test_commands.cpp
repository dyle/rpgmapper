/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018-2019, Oliver Maurhart, dyle71@gmail.com
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
#include <rpgmapper/command/set_map_grid_color.hpp>
#include <rpgmapper/command/set_map_name.hpp>
#include <rpgmapper/command/set_map_numeral_axis.hpp>
#include <rpgmapper/command/set_map_origin.hpp>
#include <rpgmapper/command/set_region_name.hpp>
#include <rpgmapper/atlas.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;
using namespace rpgmapper::model::command;


TEST(ProcessorTest, DoNopCommand) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    EXPECT_EQ(processor->modifications(), 0);
    EXPECT_TRUE(processor->getHistory().empty());
    processor->execute(CommandPointer{new Nop});
    EXPECT_NE(processor->modifications(), 0);

    EXPECT_EQ(processor->getHistory().size(), 1);
    processor->undo();
    EXPECT_EQ(processor->modifications(), 0);
    EXPECT_TRUE(processor->getHistory().empty());
    processor->redo();
    EXPECT_EQ(processor->getHistory().size(), 1);
    EXPECT_NE(processor->modifications(), 0);
}


TEST(ProcessorTest, SetAtlasName) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    auto atlas = session->getAtlas();

    atlas->setName("foo");

    processor->execute(CommandPointer{new SetAtlasName{"bar"}});
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(processor->getHistory().size(), 1);
    EXPECT_EQ(processor->getHistory().front()->getDescription().toStdString(), "Set atlas name to bar.");
    EXPECT_EQ(processor->getUndone().size(), 0);

    processor->undo();
    EXPECT_EQ(atlas->getName().toStdString(), "foo");
    EXPECT_EQ(processor->getHistory().size(), 0);
    EXPECT_EQ(processor->getUndone().size(), 1);
    EXPECT_EQ(processor->getUndone().front()->getDescription().toStdString(), "Set atlas name to bar.");

    processor->redo();
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(processor->getHistory().size(), 1);
    EXPECT_EQ(processor->getUndone().size(), 0);

    processor->undo();
    EXPECT_EQ(atlas->getName().toStdString(), "foo");
    EXPECT_EQ(processor->getHistory().size(), 0);
    EXPECT_EQ(processor->getUndone().size(), 1);

    processor->redo();
    EXPECT_EQ(atlas->getName().toStdString(), "bar");
    EXPECT_EQ(processor->getHistory().size(), 1);
    EXPECT_EQ(processor->getUndone().size(), 0);
}


TEST(ProcessorTest, NewCommandResetsUndoneList) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new SetAtlasName{"bar"}});
    processor->execute(CommandPointer{new SetAtlasName{"baz"}});
    processor->execute(CommandPointer{new SetAtlasName{"bam"}});
    processor->undo();
    processor->undo();
    EXPECT_EQ(processor->getUndone().size(), 2);

    processor->execute(CommandPointer{new SetAtlasName{"bag"}});
    EXPECT_EQ(processor->getUndone().size(), 0);
}


TEST(ProcessorTest, CreateRegion) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});

    auto regionNames = session->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());

    processor->undo();

    regionNames = session->getAllRegionNames();
    EXPECT_EQ(regionNames.find("foo"), regionNames.end());

    processor->redo();
    regionNames = session->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());

    EXPECT_TRUE(session->isModified());
}


TEST(ProcessorTest, CreateMap) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();

    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});

    auto regionNames = session->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());
    
    auto mapNames = session->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());
    
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());
    EXPECT_NE(region->getMapNames().find("bar"), region->getMapNames().end());

    processor->undo();

    mapNames = session->getAllMapNames();
    EXPECT_EQ(mapNames.find("bar"), mapNames.end());
    processor->redo();
    EXPECT_TRUE(session->isModified());
}


TEST(ProcessorTest, RemoveMap) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();

    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});

    auto mapNames = session->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());

    auto map = session->findMap("bar");
    processor->execute(CommandPointer{new RemoveMap{map}});

    mapNames = session->getAllMapNames();
    EXPECT_EQ(mapNames.find("bar"), mapNames.end());

    processor->undo();

    mapNames = session->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());
}


TEST(ProcessorTest, RemoveRegion) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();

    processor->execute(CommandPointer{new CreateRegion{"foo"}});

    auto regionNames = session->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());

    processor->execute(CommandPointer{new CreateMap{"foo", "bar"}});
    processor->execute(CommandPointer{new CreateMap{"foo", "baz"}});
    processor->execute(CommandPointer{new CreateMap{"foo", "bam"}});

    auto mapNames = session->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());
    EXPECT_NE(mapNames.find("baz"), mapNames.end());
    EXPECT_NE(mapNames.find("bam"), mapNames.end());

    auto region = session->findRegion("foo");
    processor->execute(CommandPointer{new RemoveRegion{region}});

    regionNames = session->getAllRegionNames();
    EXPECT_EQ(regionNames.find("foo"), regionNames.end());
    mapNames = session->getAllMapNames();
    EXPECT_EQ(mapNames.find("bar"), mapNames.end());
    EXPECT_EQ(mapNames.find("baz"), mapNames.end());
    EXPECT_EQ(mapNames.find("bam"), mapNames.end());

    processor->undo();

    regionNames = session->getAllRegionNames();
    EXPECT_NE(regionNames.find("foo"), regionNames.end());
    mapNames = session->getAllMapNames();
    EXPECT_NE(mapNames.find("bar"), mapNames.end());
    EXPECT_NE(mapNames.find("baz"), mapNames.end());
    EXPECT_NE(mapNames.find("bam"), mapNames.end());
}


TEST(ProcessorTest, SetRegionName) {
    
    Session::setCurrentSession(Session::init());
    auto session = Session::getCurrentSession();
    auto processor = session->getCommandProcessor();
    
    processor->execute(CommandPointer{new CreateRegion{"foo"}});
    auto region = session->findRegion("foo");
    EXPECT_TRUE(region->isValid());

    processor->execute(CommandPointer{new SetRegionName{region, "bar"}});
    region = session->findRegion("bar");
    ASSERT_TRUE(region->isValid());
    EXPECT_EQ(region->getName().toStdString(), "bar");
}
