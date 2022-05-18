/**
 * @file base_test.cpp
 * @author argawaen
 * @date 19/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "base/base.h"
#include "gtest/gtest.h"

using namespace dg::core::base;

TEST(Base, FloatOperation) {
    EXPECT_TRUE(isZero(0.0));
    EXPECT_FALSE(isZero(1.0));
    EXPECT_TRUE(isEqual(0, 0));
    EXPECT_TRUE(isEqual(10, 10));
    EXPECT_FALSE(isEqual(0, 0.1));
    EXPECT_FALSE(isEqual(-0.1, 0));
    EXPECT_TRUE(isEqual(100, 100));
    EXPECT_FALSE(isEqual(100, 101));
}
