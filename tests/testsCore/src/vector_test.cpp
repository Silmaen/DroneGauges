/**
 * @file vector_test.cpp
 * @author Silmean
 * @date 18/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "CoreTestHelper.h"
#include "math/Vector.h"
#include <cmath>

using namespace dg::core::math;

TEST(Vector, Base) {
    Vector f;
    EXPECT_TRUE(f == Vector(0, 0, 0));
    EXPECT_FALSE(f == Vector(0, 1, 0));
    EXPECT_FALSE(f == Vector(0, 0, 1));
    EXPECT_FALSE(f == Vector(1, 0, 0));

    EXPECT_FALSE(f != Vector(0, 0, 0));
    EXPECT_TRUE(f != Vector(0, 1, 0));
    EXPECT_TRUE(f != Vector(0, 0, 1));
    EXPECT_TRUE(f != Vector(1, 0, 0));
    Vector f2{f};
    EXPECT_EQ(f, f2);
    f2= 3 * Vector(1, 0, 0) + Vector(1, 0, 0) - Vector(0, 0, 1) * 4;
    EXPECT_EQ(f2, Vector(4, 0, -4));
    EXPECT_EQ(f2 / 2, Vector(2, 0, -2));
}

TEST(Vector, Access) {
    const Vector f{8, 5, -6};
    EXPECT_EQ(8, f[0]);
    EXPECT_EQ(5, f[1]);
    EXPECT_EQ(-6, f[2]);
    EXPECT_TRUE(std::isnan(f[3]));
    Vector f2;
    f2[0]= 78;
    f2[1]= -89;
    f2[2]= 999;
    EXPECT_EQ(78, f2[0]);
    EXPECT_EQ(-89, f2[1]);
    EXPECT_EQ(999, f2[2]);
    EXPECT_EQ(999, f2[3]);
}

TEST(Vector, Products) {
    Vector f(1, 2, 3);
    Vector f2(4, 5, 6);
    EXPECT_EQ(dotProduct(f, f2), 32);
    Vector f3= crossProduct(f, f2);
    EXPECT_EQ(f3, Vector(-3, 5, -1));
    f.selfCrossProduct(f2);
    EXPECT_EQ(f3, f);
}

TEST(Vector, Norms) {
    Vector f(1, 2, 3);
    EXPECT_TRUE(dg::core::base::isEqual(f.norm(), 3.7416573867739413));
    Vector fn= f.normalized();
    EXPECT_TRUE(dg::core::base::isEqual(fn.norm(), 1.0));
    f.normalize();
    EXPECT_EQ(fn, f);
}
