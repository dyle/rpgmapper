/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/map.hpp>
#include <rpgmapper/region.hpp>
#include <rpgmapper/region_name_validator.hpp>

using namespace rpgmapper::model;


TEST(RegionTest, CreateRegionIsValid) {
    Region region{"foo"};
    ASSERT_TRUE(region.isValid());
}


TEST(RegionTest, RegionGetAndSetName) {
    
    Region region{"foo"};
    EXPECT_EQ(region.getName().toStdString(), "foo");
    region.setName("bar");
    EXPECT_EQ(region.getName().toStdString(), "bar");
}


TEST(RegionTest, GetAllMapNames) {
    
    Region region{"foo"};
    region.addMap(MapPointer{new Map{"map 1"}});
    region.addMap(MapPointer{new Map{"map 2"}});
    region.addMap(MapPointer{new Map{"map 3"}});
    region.addMap(MapPointer{new Map{"map 4"}});
    std::set<QString> mapNamesExpected{"map 1", "map 2", "map 3", "map 4" };
    EXPECT_TRUE(mapNamesExpected == region.getMapNames());
}


TEST(RegionTest, CreateAndRemoveMaps) {
    
    Region region{"foo"};
    std::vector<QString> maps{"map 1", "map 2", "map 3", "map 4", "map 5"};

    int numberOfMaps = 0;
    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      region.addMap(MapPointer{new Map{name}});
                      EXPECT_EQ(region.getMapNames().size(), ++numberOfMaps);
                  });

    std::for_each(std::begin(maps),
                  std::end(maps),
                  [&](auto & name) {
                      region.removeMap(name);
                      EXPECT_EQ(region.getMapNames().size(), --numberOfMaps);
                  });
}


TEST(RegionTest, ValidNames) {

    EXPECT_TRUE(RegionNameValidator::isValid("Middleearth"));
    EXPECT_TRUE(RegionNameValidator::isValid("A land far far away"));
    EXPECT_TRUE(RegionNameValidator::isValid("Asgard!"));
    EXPECT_FALSE(RegionNameValidator::isValid("This is: invalid"));
    EXPECT_FALSE(RegionNameValidator::isValid("This is also \\ invalid"));
    EXPECT_FALSE(RegionNameValidator::isValid("This is invalid * as well"));
    EXPECT_FALSE(RegionNameValidator::isValid("And this ? is also invalid"));
}
