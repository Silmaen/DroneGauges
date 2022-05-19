/**
 * @file Vector.h
 * @author Silmaen
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
        return !base::isEqual(x, other.x) || !base::isEqual(y, other.y) || !base::isEqual(z, other.z);
    }

    /**
     * @brief Member access
     * @param idx Index of component
     * @return Value of component, Nan if off limit
     */
    double operator[](const uint8_t& idx) const {
        return idx == 0 ? x : (idx == 1 ? y : (idx == 2 ? z : std::numeric_limits<double>::quiet_NaN()));
    }
    /**
     * @brief Member access
     * @param idx Index of component
     * @return Value of component, z if off limit
     */
    double& operator[](const uint8_t& idx){
        return idx == 0 ? x : (idx == 1 ? y : z);
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
        x*= other;
        y*= other;
        z*= other;
        return *this;
    }
    /**
     * @brief Division operator
     * @param other Scalar to divide
     * @return This updated vector
     */
    Vector& operator/=(const double& other) {
        x/= other;
        y/= other;
        z/= other;
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

    /**
    * @brief Multiplication operator
    * @param other Scalar to multiply
    * @return Updated vector
    */
    Vector operator*(const double& other) const {
        Vector vec(*this);
        vec*= other;
        return vec;
    }

    /**
    * @brief Division operator
    * @param other Scalar to Divide
    * @return Updated vector
    */
    Vector operator/(const double& other) const {
        Vector vec(*this);
        vec/= other;
        return vec;
    }

    /**
    * @brief Multiplication operator
    * @param other Scalar to multiply
    * @param vector The vector to multiply
    * @return Updated vector
    */
    friend Vector operator*(const double& other, const Vector& vector) {
        Vector vec{vector};
        vec*= other;
        return vec;
    }

    /**
     * @brief Compute dot product with another vector
     * @param other The other vector to multiply
     * @return The dot Product
     */
    double dotProduct(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    /**
     * @brief Compute the cross product with another vector
     * @param other The other vector to multiply
     * @return This updated vector
     */
    Vector& selfCrossProduct(const Vector& other) {
        Vector tmp{*this};
        x= tmp.y * other.z - tmp.z * other.y;
        y= tmp.z * other.x - tmp.x - other.z;
        z= tmp.x * other.y - tmp.y - other.x;
        return *this;
    }

    /**
     * @brief Compute the cross product with another vector
     * @param other The other vector to multiply
     * @return The cross product
     */
    Vector crossProduct(const Vector& other) const {
        return Vector{y * other.z - z * other.y, z * other.x - x - other.z, x * other.y - y - other.x};
    }

    /**
     * @brief Compute the norm (length) of the vector
     * @return Vector's norm
     */
    double norm()const;

    /**
     * @brief Compute the square norm (length) of the vector
     * @return Vector's square norm
     */
    double normSq()const;

    /**
     * @brief Return a normalized copy of this vector
     * @return Normalized vector
     */
    Vector normalized()const;

    /**
     * @brief Normalize this vector
     * @return This updated vector
     */
    Vector& normalize();

private:
    /// First coordinate
    double x= 0.0;
    /// Second coordinate
    double y= 0.0;
    /// Third coordinate
    double z= 0.0;
};

/**
 * @brief Compute the dot product with another vector
 * @param vectorA First vector to multiply
 * @param vectorB Second vector to multiply
 * @return The dot product
 */
double dotProduct(const Vector& vectorA, const Vector& vectorB);

/**
 * @brief Compute the cross product with another vector
 * @param vectorA First vector to multiply
 * @param vectorB Second vector to multiply
 * @return The cross product
 */
Vector crossProduct(const Vector& vectorA, const Vector& vectorB);

}// namespace dg::core::math
