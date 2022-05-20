/**
 * @file Vector.cpp
 * @author Silmean
 * @date 18/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "math/Vector.h"
#include <cmath>

namespace dg::core::math {

double dotProduct(const Vector& vectorA, const Vector& vectorB) {
    return vectorA.dotProduct(vectorB);
}

Vector crossProduct(const Vector& vectorA, const Vector& vectorB) {
    return vectorA.crossProduct(vectorB);
}

double Vector::norm() const {
    return std::sqrt(normSq());
}
double Vector::normSq() const {
    return x * x + y * y + z * z;
}
Vector Vector::normalized() const {
    return Vector(*this) / norm();
}
Vector& Vector::normalize() {
    double n= norm();
    x/= n;
    y/= n;
    z/= n;
    return *this;
}

}// namespace dg::core::math
