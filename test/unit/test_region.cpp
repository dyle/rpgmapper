/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <gtest/gtest.h>

#include <rpgmapper/region.hpp>

using namespace rpgmapper::model;


TEST(RegionTest, CreateRegionIsValid) {

    Region region{"foo"};

    ASSERT_TRUE(region.isValid());
}


TEST(RegionTest, CreateRegionPointerIsValid) {

    RegionPointer region{new Region{"foo"}};

    EXPECT_NE(region.data(), nullptr);
    EXPECT_TRUE(region->isValid());
}


TEST(RegionTest, CreateInvalidRegionIsNotValid) {
    EXPECT_FALSE(InvalidRegion{}.isValid());
}


TEST(RegionTest, CreateInvalidRegionPointerIsNotValid) {

    RegionPointer region{new InvalidRegion{}};

    EXPECT_NE(region.data(), nullptr);
    EXPECT_FALSE(region->isValid());
}


TEST(RegionTest, RegionGetAndSetName) {

    Region region{"foo"};
    EXPECT_EQ(region.getName().toStdString(), "foo");

    region.setName("bar");
    EXPECT_EQ(region.getName().toStdString(), "bar");
}


TEST(RegionTest, FindMap) {

    Region region{"foo"};
    region.createMap("bar");
    auto map = region.findMap("bar");

    EXPECT_TRUE(map->isValid());
}


TEST(RegionTest, FindInvalidMap) {

    Region region{"foo"};
    region.createMap("bar");
    auto map = region.findMap("baz");

    EXPECT_FALSE(map->isValid());
}


TEST(RegionTest, GetAllMapNames) {

    Region region("foo");
    region.createMap("map 1");
    region.createMap("map 2");
    region.createMap("map 3");
    region.createMap("map 4");
    region.createMap("map 4");
    region.createMap("map 3");
    region.createMap("map 3");
    std::set<QString> mapNamesExpected{"map 1", "map 2", "map 3", "map 4" };

    EXPECT_TRUE(mapNamesExpected == region.getMapNames());
}


TEST(RegionTest, CreateMap) {

    Region region{"foo"};
    auto map = region.createMap("bar");

    EXPECT_TRUE(map->isValid());
    EXPECT_EQ(map->getRegion(), &region);
    EXPECT_EQ(map->getName(), "bar");
}


TEST(RegionTest, CreateAndRemoveMaps) {

    std::vector<QString> maps{"Map 1",
                              "Map 2",
                              "Map 3",
                              "Map 4",
                              "Map 5"};

    Region region{"foo"};

    int numberOfMaps = 0;
    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      region.createMap(name);
                      EXPECT_EQ(region.getMaps().size(), ++numberOfMaps);
                  });

    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      region.removeMap(name);
                      EXPECT_EQ(region.getMaps().size(), --numberOfMaps);
                  });
}


TEST(RegionTest, CreateAndRemoveIdenticalMaps) {

    std::vector<QString> maps{"Map 1",
                              "Map 1",
                              "Map 1",
                              "Map 1",
                              "Map 1"};

    Region region{"foo"};

    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      region.createMap(name);
                      EXPECT_EQ(region.getMaps().size(), 1);
                  });

    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      region.removeMap(name);
                      EXPECT_TRUE(region.getMaps().empty());
                  });
}


TEST(RegionTest, DeleteMap) {

    Region region{"foo"};
    region.createMap("bar");

    EXPECT_TRUE(region.findMap("bar")->isValid());
    region.removeMap("bar");
    EXPECT_FALSE(region.findMap("bar")->isValid());
}
