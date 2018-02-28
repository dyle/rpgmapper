/*
 * This file is part of rpgmapper.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <chrono>
#include <thread>

#include <gtest/gtest.h>

#include <rpgmapper/average.hpp>

using namespace rpgmapper::model;


TEST(Average, EmptyAverage) {

    AverageOverSize<float> average(10);
    EXPECT_EQ(average.average(), 0.0);
}


TEST(Average, FloatAverage) {

    AverageOverSize<float> average(10);
    average << 5 << 4 << 3 << 2 << 1 << 0;
    EXPECT_EQ(average.average(), 2.5);
    EXPECT_EQ(average.items().size(), 6);
    EXPECT_EQ(average.sum(), 15);
}


TEST(Average, IntAverage) {

    AverageOverSize<int> average(10);
    average << 5 << 4 << 3 << 2 << 1 << 0;
    EXPECT_EQ(average.average(), 2);
}


TEST(Average, FloatAverage10) {

    AverageOverSize<float> average(10);
    average << 12 << 11 << 10 << 9 << 8 << 7;
    average << 6 << 5 << 4 << 3 << 2 << 1;
    EXPECT_EQ(average.average(), 5.5);
}


TEST(Average, FloatAverage20) {

    AverageOverSize<float> average(20);
    average << 24 << 23 << 22 << 21 << 20 << 19;
    average << 18 << 17 << 16 << 15 << 14 << 13;
    average << 12 << 11 << 10 << 9 << 8 << 7;
    average << 6 << 5 << 4 << 3 << 2 << 1;
    EXPECT_EQ(average.average(), 10.5);
}


TEST(Average, FloatAverageTime1Sec) {

    AverageOverTime<float> average(std::chrono::seconds{1});
    average << 5 << 4 << 3 << 2 << 1;
    EXPECT_EQ(average.average(), 3.0);

    std::this_thread::sleep_for(std::chrono::milliseconds(1001));
    EXPECT_EQ(average.average(), 0.0);
}
