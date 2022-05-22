/**
 * @file base_test.cpp
 * @author argawaen
 * @date 19/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "CoreTestHelper.h"
#include "base/base.h"

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
    EXPECT_TRUE(isEqualA(100, 100));
    EXPECT_FALSE(isEqualA(100, 101));
    EXPECT_TRUE(isEqualR(100, 100));
    EXPECT_FALSE(isEqualR(100, 101));
}

TEST(Base, Clamp) {
    EXPECT_EQ(clamp(100, 0, 200), 100);
    EXPECT_EQ(clamp(100, 110, 200), 110);
    EXPECT_EQ(clamp(100, 0, 90), 90);
    EXPECT_EQ(clamp(100, 90, 0), 0);
}
