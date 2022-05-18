/**
 * @file Vector.h
 * @author damien.lachouette 
 * @date 18/05/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include "base/base.h"

/**
 * @brief Math namespace
 */
namespace dg::core::math {

/**
 * @brief Class Vector
 */
class Vector {
public:
    /**
     * @brief Default copy constructor
     */
    Vector(const Vector&)= default;
    /**
     * @brief Default move constructor
     */
    Vector(Vector&&)= default;
    /**
     * @brief Constructor by coordinates
     * @param _x First coordinate
     * @param _y Second coordinate
     * @param _z Third coordinate
     */
    Vector(const double& _x= 0, const double& _y= 0, const double& _z= 0):
        x{_x}, y{_y}, z{_z} {}
    /**
     * @brief Default copy assignation
     * @return this
     */
    Vector& operator=(const Vector&)= default;
    /**
     * @brief Default move assignation
     * @return this
     */
    Vector& operator=(Vector&&)= default;
    /**
     * @brief Destructor.
     */
    ~Vector()= default;//---UNCOVER---
    /**
     * @brief Comparison operator
     * @param other Vector to compare
     * @return True if same vectors
     */
    bool operator==(const Vector& other) const {
        return base::isEqual(x, other.x) && base::isEqual(y, other.y) && base::isEqual(z, other.z);
    }
    /**
     * @brief Comparison operator
     * @param other Vector to compare
     * @return True if different vectors
     */
    bool operator!=(const Vector& other) const {
        return !base::isEqual(x, other.x) || !base::isEqual(y, other.y) || base::isEqual(z, other.z);
    }

    /**
     * @brief Addition operator
     * @param other Vector to add
     * @return This updated vector
     */
    Vector& operator+=(const Vector& other) {
        x+= other.x;
        y+= other.y;
        z+= other.z;
        return *this;
    }
    /**
     * @brief Subtract operator
     * @param other Vector to sub
     * @return This updated vector
     */
    Vector& operator-=(const Vector& other) {
        x-= other.x;
        y-= other.y;
        z-= other.z;
        return *this;
    }
    /**
     * @brief Multiplication operator
     * @param other Scalar to multiply
     * @return This updated vector
     */
    Vector& operator*=(const double& other) {
        x+= other;
        y+= other;
        z+= other;
        return *this;
    }

    /**
    * @brief Addition operator
    * @param other Vector to add
    * @return Updated vector
    */
    Vector operator+(const Vector& other) const {
        Vector vec(*this);
        vec+= other;
        return vec;
    }
    /**
    * @brief Subtract operator
    * @param other Vector to sub
    * @return Updated vector
    */
    Vector operator-(const Vector& other) const {
        Vector vec(*this);
        vec-= other;
        return vec;
    }

private:
    /// First coordinate
    double x= 0.0;
    /// Second coordinate
    double y= 0.0;
    /// Third coordinate
    double z= 0.0;
};

}// namespace dg::core::math
