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


