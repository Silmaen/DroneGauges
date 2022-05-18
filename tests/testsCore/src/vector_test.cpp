/**
 * @file vector_test.cpp
 * @author damien.lachouette 
 * @date 18/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "gtest/gtest.h"
#include "Vector.h"

TEST(Vector, Base){
    dg::core::math::Vector f;
    EXPECT_EQ(f, dg::core::math::Vector(0,0,0));

}
