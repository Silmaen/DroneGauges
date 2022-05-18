/**
 * @file vector_test.cpp
 * @author damien.lachouette 
 * @date 18/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "math/Vector.h"
#include "gtest/gtest.h"

using namespace dg::core::math;

TEST(Vector, Base) {
    Vector f;
    EXPECT_TRUE(f == Vector(0, 0, 0));
    EXPECT_FALSE(f == Vector(0, 1, 0));
    EXPECT_FALSE(f == Vector(0, 0, 1));
    EXPECT_FALSE(f == Vector(1, 0, 0));
    // EXPECT_FALSE(f != Vector(0, 0, 0));
    //EXPECT_TRUE(f != Vector(0, 1, 0));
    //EXPECT_TRUE(f != Vector(0, 0, 1));
    // EXPECT_TRUE(f != Vector(1, 0, 0));
}
