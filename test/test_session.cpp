/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <tuple>

#include <gtest/gtest.h>

#include <rpgmapper/atlas.hpp>
#include <rpgmapper/map.hpp>
#include <rpgmapper/map_name_validator.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/region_name_validator.hpp>
#include <rpgmapper/session.hpp>

using namespace rpgmapper::model;


TEST(SessionTest, InitAndSetSession) {
    
    auto session = Session::init();
    ASSERT_TRUE(session.data() != nullptr);
    
    auto atlas = session->getAtlas();
    EXPECT_TRUE(atlas->isValid());
    
    Session::setCurrentSession(session);
    EXPECT_EQ(Session::getCurrentSession().data(), session.data());
}


TEST(SessionTest, InitSession) {
    
    auto session = Session::init();
    auto atlas = session->getAtlas();
    
    EXPECT_EQ(atlas->getName().toStdString(), "New Atlas");
    ASSERT_EQ(atlas->getRegions().size(), 1);
    auto const region = (*atlas->getRegions().begin()).second;
    EXPECT_EQ(region->getName().toStdString(), "New Region 1");
    ASSERT_EQ(region->getMaps().size(), 1);
    auto const map = (*region->getMaps().begin()).second;
    EXPECT_EQ(map->getName().toStdString(), "New Map 1");
}


TEST(SessionTest, CommandProcessor) {
    
    auto session = Session::init();
    
    auto processor = session->getCommandProcessor();
    ASSERT_NE(processor.data(), nullptr);
}


TEST(SessionTest, NewRegionName) {
    
    auto session = Session::init();
    auto atlas = session->getAtlas();
    
    auto name1 = session->createNewRegionName();
    EXPECT_TRUE(RegionNameValidator::isValid(name1));
    
    atlas->addRegion(RegionPointer{new Region{name1}});
    EXPECT_TRUE(session->findRegion(name1)->isValid());
    
    auto name2 = session->createNewRegionName();
    EXPECT_TRUE(RegionNameValidator::isValid(name2));
    EXPECT_NE(name1.toStdString(), name2.toStdString());
}


TEST(SessionTest, NewMapName) {
    
    auto session = Session::init();
    auto atlas = session->getAtlas();
    auto region = atlas->getRegion(atlas->getRegions().begin()->second->getName());
    
    auto name1 = session->createNewMapName();
    EXPECT_TRUE(MapNameValidator::isValid(name1));
    
    region->addMap(MapPointer{new Map{name1}});
    EXPECT_TRUE(session->findMap(name1)->isValid());
    
    auto name2 = session->createNewMapName();
    EXPECT_TRUE(MapNameValidator::isValid(name2));
    EXPECT_NE(name1.toStdString(), name2.toStdString());
}


TEST(SessionTest, FindRegion) {
    
    auto session = Session::init();
    
    auto region = session->findRegion("New Region 1");
    EXPECT_TRUE(region->isValid());
    region = session->findRegion("NON EXISTENT REGION");
    EXPECT_FALSE(region->isValid());
}

TEST(SessionTest, FindMap) {
    
    auto session = Session::init();
    
    auto map = session->findMap("New Map 1");
    EXPECT_TRUE(map->isValid());
    map = session->findMap("NON EXISTENT MAP");
    EXPECT_FALSE(map->isValid());
}


TEST(SessionTest, AllRegionNames) {
    
    auto session = Session::init();
    auto atlas = session->getAtlas();
    
    std::list<QString> regionNames = {"regionA", "regionB", "regionC"};
    for (auto const & regionName : regionNames) {
        atlas->addRegion(RegionPointer{new Region{regionName}});
    }
    
    std::map<QString, std::set<QString>> mapNames = {
        {"regionA", {"map-A1", "map-A2"}},
        {"regionB", {"map-B1", "map-B2", "map-B3"}}
    };
    for (auto const & regionPair : mapNames) {
        auto region = atlas->getRegion(regionPair.first);
        for (auto const & mapName : regionPair.second) {
            region->addMap(MapPointer{new Map{mapName}});
        }
    }
    
    auto allRegionNames = session->getAllRegionNames();
    EXPECT_EQ(allRegionNames.size(), 4);
    for (auto const & regionName : {"New Region 1", "regionA", "regionB", "regionC"}) {
        ASSERT_TRUE(atlas->getRegion(regionName)->isValid());
    }
    
    std::set<QString> maps;
    EXPECT_EQ(atlas->getRegion("New Region 1")->getMaps().size(), 1);
    ASSERT_NE(allRegionNames.find("New Region 1"), allRegionNames.end());
    maps = allRegionNames["New Region 1"];
    ASSERT_EQ(maps.size(), 1);
    EXPECT_NE(maps.find("New Map 1"), maps.end());
    
    EXPECT_EQ(atlas->getRegion("regionA")->getMaps().size(), 2);
    ASSERT_NE(allRegionNames.find("regionA"), allRegionNames.end());
    maps = allRegionNames["regionA"];
    ASSERT_EQ(maps.size(), 2);
    EXPECT_NE(maps.find("map-A1"), maps.end());
    EXPECT_NE(maps.find("map-A2"), maps.end());

    EXPECT_EQ(atlas->getRegion("regionB")->getMaps().size(), 3);
    ASSERT_NE(allRegionNames.find("regionB"), allRegionNames.end());
    maps = allRegionNames["regionB"];
    ASSERT_EQ(maps.size(), 3);
    EXPECT_NE(maps.find("map-B1"), maps.end());
    EXPECT_NE(maps.find("map-B2"), maps.end());
    EXPECT_NE(maps.find("map-B3"), maps.end());
    
    EXPECT_EQ(atlas->getRegion("regionC")->getMaps().size(), 0);
    ASSERT_NE(allRegionNames.find("regionC"), allRegionNames.end());
    maps = allRegionNames["regionC"];
    ASSERT_EQ(maps.size(), 0);
}


TEST(SessionTest, AllMapNames) {
    
    auto session = Session::init();
    auto atlas = session->getAtlas();
    
    std::list<QString> regionNames = {"regionA", "regionB", "regionC"};
    for (auto const & regionName : regionNames) {
        atlas->addRegion(RegionPointer{new Region{regionName}});
    }
    
    std::map<QString, std::set<QString>> mapNames = {
            {"regionA", {"map-A1", "map-A2"}},
            {"regionB", {"map-B1", "map-B2", "map-B3"}}
    };
    for (auto const & regionPair : mapNames) {
        auto region = atlas->getRegion(regionPair.first);
        for (auto const & mapName : regionPair.second) {
            region->addMap(MapPointer{new Map{mapName}});
        }
    }
    
    auto allMapNames = session->getAllMapNames();
    EXPECT_EQ(allMapNames.size(), 6);
    for (auto const & mapName : {"New Map 1", "map-A1", "map-A2", "map-B1", "map-B2", "map-B3"}) {
        ASSERT_NE(allMapNames.find(mapName), allMapNames.end());
    }
    
    EXPECT_EQ(allMapNames["New Map 1"].toStdString(), "New Region 1");
    EXPECT_EQ(allMapNames["map-A1"].toStdString(), "regionA");
    EXPECT_EQ(allMapNames["map-A2"].toStdString(), "regionA");
    EXPECT_EQ(allMapNames["map-B1"].toStdString(), "regionB");
    EXPECT_EQ(allMapNames["map-B2"].toStdString(), "regionB");
    EXPECT_EQ(allMapNames["map-B3"].toStdString(), "regionB");
}


TEST(SessionTest, SelectRegion) {
    
    auto session = Session::init();
    auto atlas = session->getAtlas();
    
    std::list<QString> regionNames = {"regionA", "regionB", "regionC"};
    for (auto const &regionName : regionNames) {
        atlas->addRegion(RegionPointer{new Region{regionName}});
    }
    
    std::map<QString, std::set<QString>> mapNames = {
            {"regionA", {"map-A1", "map-A2"}},
            {"regionB", {"map-B1", "map-B2", "map-B3"}}
    };
    for (auto const &regionPair : mapNames) {
        auto region = atlas->getRegion(regionPair.first);
        for (auto const &mapName : regionPair.second) {
            region->addMap(MapPointer{new Map{mapName}});
        }
    }
    
    EXPECT_EQ(session->getCurrentRegionName(), QString::null);
    session->selectRegion("New Region 1");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "New Region 1");
    session->selectRegion("regionA");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionA");
    session->selectRegion("regionB");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionB");
    session->selectRegion("regionC");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionC");
}


TEST(SessionTest, SelectMap) {
    
    auto session = Session::init();
    auto atlas = session->getAtlas();
    
    std::list<QString> regionNames = {"regionA", "regionB", "regionC"};
    for (auto const &regionName : regionNames) {
        atlas->addRegion(RegionPointer{new Region{regionName}});
    }
    
    std::map<QString, std::set<QString>> mapNames = {
            {"regionA", {"map-A1", "map-A2"}},
            {"regionB", {"map-B1", "map-B2", "map-B3"}}
    };
    for (auto const &regionPair : mapNames) {
        auto region = atlas->getRegion(regionPair.first);
        for (auto const &mapName : regionPair.second) {
            region->addMap(MapPointer{new Map{mapName}});
        }
    }
    
    EXPECT_EQ(session->getCurrentMapName(), QString::null);
    session->selectMap("New Map 1");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "New Region 1");
    EXPECT_EQ(session->getCurrentMapName().toStdString(), "New Map 1");
    
    session->selectRegion("regionA");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionA");
    EXPECT_EQ(session->getCurrentMapName(), QString::null);
    
    session->selectMap("map-A1");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionA");
    EXPECT_EQ(session->getCurrentMapName().toStdString(), "map-A1");
    
    session->selectMap("map-A2");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionA");
    EXPECT_EQ(session->getCurrentMapName().toStdString(), "map-A2");
    
    session->selectMap("map-B1");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionB");
    EXPECT_EQ(session->getCurrentMapName().toStdString(), "map-B1");
    
    session->selectMap("map-B2");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionB");
    EXPECT_EQ(session->getCurrentMapName().toStdString(), "map-B2");
    
    session->selectMap("map-B3");
    EXPECT_EQ(session->getCurrentRegionName().toStdString(), "regionB");
    EXPECT_EQ(session->getCurrentMapName().toStdString(), "map-B3");
}
