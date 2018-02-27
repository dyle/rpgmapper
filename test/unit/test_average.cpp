/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <thread>

#include <gtest/gtest.h>

#include <rpgmapper/average.hpp>

using namespace rpgmapper::model;


TEST(Average, EmptyAverage) {

    Average<float> average(10);
    EXPECT_EQ(average.average(), 0.0);
}


TEST(Average, FloatAverage) {

    Average<float> average(10);
    average.add(5).add(4).add(3).add(2).add(1).add(0);
    EXPECT_EQ(average.average(), 2.5);
}


TEST(Average, IntAverage) {

    Average<int> average(10);
    average.add(5).add(4).add(3).add(2).add(1).add(0);
    EXPECT_EQ(average.average(), 2);
}


TEST(Average, FloatAverage10) {

    Average<float> average(10);
    average.add(12).add(11).add(10).add(9).add(8).add(7);
    average.add(6).add(5).add(4).add(3).add(2).add(1);
    EXPECT_EQ(average.average(), 5.5);
}


TEST(Average, FloatAverage20) {

    Average<float> average(20);
    average.add(24).add(23).add(22).add(21).add(20).add(19);
    average.add(18).add(17).add(16).add(15).add(14).add(13);
    average.add(12).add(11).add(10).add(9).add(8).add(7);
    average.add(6).add(5).add(4).add(3).add(2).add(1);
    EXPECT_EQ(average.average(), 10.5);
}


TEST(Average, FloatAverageTime1Sec) {

    Average<float> average(0, std::chrono::seconds{1});
    average.add(5).add(4).add(3).add(2).add(1);
    EXPECT_EQ(average.average(), 3.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1001));
    EXPECT_EQ(average.average(), 0.0);
}
