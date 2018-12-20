/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <gtest/gtest.h>

#include <rpgmapper/field.hpp>

using namespace rpgmapper::model;


TEST(FieldTest, ValidField) {
    EXPECT_TRUE(Field(0, 0).isValid());
}


TEST(FieldTest, InvalidField) {
    EXPECT_FALSE(Field::nullField().isValid());
}


TEST(FieldTest, FieldIndexInstances) {

    EXPECT_EQ(Field(0, 0).getIndex(), 0);
    EXPECT_EQ(Field(10, 0).getIndex(), 10);
    EXPECT_EQ(Field(999, 0).getIndex(), 999);
    EXPECT_EQ(Field(0, 1).getIndex(), 1000000);
    EXPECT_EQ(Field(1, 1).getIndex(), 1000001);
    EXPECT_EQ(Field(10, 10).getIndex(), 10000010);
}


TEST(FieldTest, FieldIndexPoints) {

    EXPECT_EQ(Field::getIndex(QPoint(0, 0)), 0);
    EXPECT_EQ(Field::getIndex(QPoint(10, 0)), 10);
    EXPECT_EQ(Field::getIndex(QPoint(999, 0)), 999);
    EXPECT_EQ(Field::getIndex(QPoint(0, 1)), 1000000);
    EXPECT_EQ(Field::getIndex(QPoint(1, 1)), 1000001);
    EXPECT_EQ(Field::getIndex(QPoint(10, 10)), 10000010);
}


TEST(FieldTest, FieldIndexValues) {

    EXPECT_EQ(Field::getIndex(0, 0), 0);
    EXPECT_EQ(Field::getIndex(10, 0), 10);
    EXPECT_EQ(Field::getIndex(999, 0), 999);
    EXPECT_EQ(Field::getIndex(0, 1), 1000000);
    EXPECT_EQ(Field::getIndex(1, 1), 1000001);
    EXPECT_EQ(Field::getIndex(10, 10), 10000010);
}


TEST(FieldTest, GetPositionFromIndex) {
    
    EXPECT_EQ(Field::getPositionFromIndex(0), QPoint(0, 0));
    EXPECT_EQ(Field::getPositionFromIndex(1), QPoint(0, 1));
    EXPECT_EQ(Field::getPositionFromIndex(1000000), QPoint(1, 0));
    EXPECT_EQ(Field::getPositionFromIndex(1000001), QPoint(1, 1));
    EXPECT_EQ(Field::getPositionFromIndex(10000010), QPoint(10, 10));
}


TEST(FieldTest, GetTiles) {

    auto field = Field(1, 1);
    EXPECT_EQ(field.getTiles().size(), 0);
}

