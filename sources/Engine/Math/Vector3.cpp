/*
 * File: Vector3.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Wednesday, 8th March 2023 3:18:28 pm
 * Last Modified: Wednesday, 8th March 2023 3:18:37 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <stdexcept>
#include <cmath>
#include "Math/Vector3.h"

Vector3::Vector3(void): m_x(0.0f), m_y(0.0f), m_z(0.0f) {}

Vector3::Vector3(float value): m_x(value), m_y(value), m_z(value) {}

Vector3::Vector3(float x, float y, float z): m_x(x), m_y(y), m_z(z) {}

Vector3::Vector3(const Vector3& copy) {
	*this = copy;
}

Vector3& Vector3::operator=(const Vector3& copy) {
	if (*this != copy) {
		m_x = copy.m_x;
		m_y = copy.m_y;
		m_z = copy.m_z;
	}
	return *this;
}

Vector3& Vector3::Set(float x, float y, float z) {
	m_x = x;
	m_y = y;
	m_z = z;
	return *this;
}

float Vector3::GetX(void) {
	return m_x;
}

float Vector3::GetY(void) {
	return m_y;
}

float Vector3::GetZ(void) {
	return m_z;
}

float Vector3::operator[](unsigned int index) {
	if (index > 2) {
		throw new std::runtime_error("Color index out of bounds exception");
	}
	return m_values[index];
}

Vector3& Vector3::Normalize(void) {
	float invMagnitude = 1.0f / this->Magnitude();
	m_x *= invMagnitude;
	m_y *= invMagnitude;
	m_z *= invMagnitude;
	return *this;
}

Vector3& Vector3::GetNormalized(const Vector3& vector) {
	return Vector3(vector).Normalize();
}

float Vector3::Dot(const Vector3& b) const {
	return m_x * b.m_x + m_y * b.m_y + m_z * b.m_z;
}

float Vector3::Angle(const Vector3& b) const {
	return acosf(this->Dot(b) / this->Magnitude() / b.Magnitude());
}

float Vector3::Magnitude(void) const {
	return sqrtf(this->Dot(*this));
}

float Vector3::Distance(const Vector3& b) const {
	return (*this - b).Magnitude();
}

Vector3& Vector3::Cross(const Vector3& b) const {
	return *(&Vector3(
		m_y * b.m_z - m_z * b.m_y,
		m_z * b.m_x - m_x * b.m_z,
		m_x * b.m_y - m_y * b.m_x
	));
}

Vector3& Vector3::Min(const Vector3& a, const Vector3& b) {
	return *(&Vector3(
		a.m_x > b.m_x ? b.m_x : a.m_x,
		a.m_y > b.m_y ? b.m_y : a.m_y,
		a.m_z > b.m_z ? b.m_z : a.m_z
	));
}

Vector3& Vector3::Max(const Vector3& a, const Vector3& b) {
	return *(&Vector3(
		a.m_x < b.m_x ? b.m_x : a.m_x,
		a.m_y < b.m_y ? b.m_y : a.m_y,
		a.m_z < b.m_z ? b.m_z : a.m_z
	));
}

Vector3& Vector3::Add(float x, float y, float z) {
	return (*this += Vector3(x, y, z));
}

Vector3& Vector3::Add(Vector3& b) {
	return (*this += b);
}

Vector3& Vector3::Add(const Vector3& a, float x, float y, float z) {
	return (a + Vector3(x, y, z));
}

Vector3& Vector3::Sub(float x, float y, float z) {
	return (*this -= Vector3(x, y, z));
}

Vector3& Vector3::Sub(Vector3& b) {
	return (*this -= b);
}

Vector3& Vector3::Sub(const Vector3& a, float x, float y, float z) {
	return (a - Vector3(x, y, z));
}

Vector3& Vector3::operator+=(const Vector3& b) {
	m_x += b.m_x;
	m_y += b.m_y;
	m_z += b.m_z;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& b) {
	m_x -= b.m_x;
	m_y -= b.m_y;
	m_z -= b.m_z;
	return *this;
}

Vector3& Vector3::operator*=(const float b) {
	m_x *= b;
	m_y *= b;
	m_z *= b;
	return *this;
}

bool operator==(const Vector3& a, const Vector3& b) {
	return (a.m_x == b.m_x && a.m_y == b.m_y && a.m_z == b.m_z);
}

bool operator!=(const Vector3& a, const Vector3& b) {
	return (a.m_x != b.m_x || a.m_y != b.m_y || a.m_z != b.m_z);
}

Vector3& operator+(const Vector3& a, const Vector3& b) {
	return *(&Vector3(a.m_x + b.m_x, a.m_y + b.m_y, a.m_z + b.m_z));
}

Vector3& operator-(const Vector3& a, const Vector3& b) {
	return *(&Vector3(a.m_x - b.m_x, a.m_y - b.m_y, a.m_z - b.m_z));
}

Vector3& operator*(const Vector3& a, const float b) {
	return *(&Vector3(a.m_x * b, a.m_y * b, a.m_z * b));
}

Vector3& operator*(const float a, const Vector3& b) {
	return *(&Vector3(a * b.m_x, a * b.m_y, a * b.m_z));
}
