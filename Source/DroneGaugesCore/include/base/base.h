/**
 * @file base.h
 * @author Silmean
 * @date 17/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <cstdint>
#include <limits>

/**
 * @namespace dg
 * @brief Base namespace for DroneGauges project
 */

/**
  * @namespace dg::core
  * @brief Core library namespace
  */

/**
  * @brief base namespace
  */
namespace dg::core::base {

/// Value of the absolute accuracy
constexpr double absoluteAccuracy= 1.e-6;
/// Value of the relative accuracy
constexpr double relativeAccuracy= 1.e-3;

/**
 * @brief Quick definition of absolute value
 * @param a The input float
 * @return The absolute value of a
 */
constexpr double abs(const double& a) { return a > 0 ? a : -a; }

/**
 * @brief Check near equality to 0
 * @param a Float to check
 * @return True if near ly equal to zero
 */
inline constexpr bool isZero(const double& a) {
    return abs(a) < absoluteAccuracy;
}
/**
 * @brief Check float equality
 * @param a first float
 * @param b second float
 * @return True if nearly equal
 */
inline constexpr bool isEqual(const double& a, const double& b) {
    double diff= abs(a - b);
    double aa  = abs(a);
    double ab  = abs(b);
    if(aa < absoluteAccuracy || ab < absoluteAccuracy || diff < relativeAccuracy) {
        return diff < absoluteAccuracy;
    } else {
        return diff / (aa + ab) < relativeAccuracy;
    }
}

/**
 * @brief Check float equality with absolute accuracy
 * @param a First float
 * @param b Second float
 * @param absAccuracy Absolute accuracy
 * @return True if nearly equal
 */
inline constexpr bool isEqualA(const double& a, const double& b, const double& absAccuracy= absoluteAccuracy) {
    return abs(a - b) < absAccuracy;
}

/**
 * @brief Check float equality with relative accuracy
 * @param a First float
 * @param b Second float
 * @param relAccuracy Absolute accuracy
 * @return True if nearly equal
 */
inline constexpr bool isEqualR(const double& a, const double& b, const double& relAccuracy= relativeAccuracy) {
    return abs(a - b) / (abs(a) + abs(b)) < relAccuracy;
}

}// namespace dg::core::base
