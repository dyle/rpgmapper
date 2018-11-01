/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/field.hpp>

using namespace rpgmapper::model;


TEST(FieldTest, FieldIndexValues) {

    EXPECT_EQ(Field::getIndex(0, 0), 0);
    EXPECT_EQ(Field::getIndex(10, 0), 10);
    EXPECT_EQ(Field::getIndex(999, 0), 999);
    EXPECT_EQ(Field::getIndex(0, 1), 1000);
    EXPECT_EQ(Field::getIndex(1, 1), 1001);
    EXPECT_EQ(Field::getIndex(10, 10), 10010);
}
