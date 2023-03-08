/*
 * File: Vector2.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Wednesday, 8th March 2023 2:23:49 pm
 * Last Modified: Wednesday, 8th March 2023 2:23:51 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include <stdexcept>
#include <cmath>
#include "Math/Vector2.h"

Vector2::Vector2(void): m_x(0.0f), m_y(0.0f) {}

Vector2::Vector2(float value): m_x(value), m_y(value) {}

Vector2::Vector2(float x, float y): m_x(x), m_y(y) {}

Vector2::Vector2(const Vector2& copy) {
	*this = copy;
}

Vector2& Vector2::operator=(const Vector2& copy) {
	if (*this != copy) {
		m_x = copy.m_x;
		m_y = copy.m_y;
	}
	return *this;
}

Vector2& Vector2::Set(float x, float y) {
	m_x = x;
	m_y = y;
	return *this;
}

float Vector2::GetX(void) {
	return m_x;
}

float Vector2::GetY(void) {
	return m_y;
}

float Vector2::operator[](unsigned int index) {
	if (index > 1) {
		throw new std::runtime_error("Color index out of bounds exception");
	}
	return m_coords[index];
}

Vector2& Vector2::Normalize(void) {
	float invMagnitude = 1.0f / this->Magnitude();
	m_x *= invMagnitude;
	m_y *= invMagnitude;
	return *this;
}

Vector2& Vector2::GetNormalized(const Vector2& vector) {
	return Vector2(vector).Normalize();
}

float Vector2::Dot(const Vector2& b) const {
	return m_x * b.m_x + m_y * b.m_y;
}

float Vector2::Angle(const Vector2& b) const {
	return acosf(this->Dot(b) / this->Magnitude() / b.Magnitude());
}

float Vector2::Magnitude(void) const {
	return sqrtf(this->Dot(*this));
}

float Vector2::Distance(const Vector2& b) const {
	return (*this - b).Magnitude();
}

Vector2& Vector2::Min(const Vector2& a, const Vector2& b) {
	return *(&Vector2(a.m_x > b.m_x ? b.m_x : a.m_x, a.m_y > b.m_y ? b.m_y : a.m_y));
}

Vector2& Vector2::Max(const Vector2& a, const Vector2& b) {
	return *(&Vector2(a.m_x < b.m_x ? b.m_x : a.m_x, a.m_y < b.m_y ? b.m_y : a.m_y));
}

Vector2& Vector2::Add(float x, float y) {
	return (*this += Vector2(x, y));
}

Vector2& Vector2::Add(Vector2& b) {
	return (*this += b);
}

Vector2& Vector2::Add(const Vector2& a, float x, float y) {
	return (a + Vector2(x, y));
}

Vector2& Vector2::Sub(float x, float y) {
	return (*this -= Vector2(x, y));
}

Vector2& Vector2::Sub(Vector2& b) {
	return (*this -= b);
}

Vector2& Vector2::Sub(const Vector2& a, float x, float y) {
	return (a - Vector2(x, y));
}

Vector2& Vector2::operator+=(const Vector2& b) {
	m_x += b.m_x;
	m_y += b.m_y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& b) {
	m_x -= b.m_x;
	m_y -= b.m_y;
	return *this;
}

Vector2& Vector2::operator*=(const float& b) {
	m_x *= b;
	m_y *= b;
	return *this;
}

bool operator==(const Vector2& a, const Vector2& b) {
	return (a.m_x == b.m_x && a.m_y == b.m_y);
}

bool operator!=(const Vector2& a, const Vector2& b) {
	return (a.m_x != b.m_x || a.m_y != b.m_y);
}

Vector2& operator+(const Vector2& a, const Vector2& b) {
	return *(&Vector2(a.m_x + b.m_x, a.m_y + b.m_y));
}

Vector2& operator-(const Vector2& a, const Vector2& b) {
	return *(&Vector2(a.m_x - b.m_x, a.m_y - b.m_y));
}

Vector2& operator*(const Vector2& a, const float b) {
	return *(&Vector2(a.m_x * b, a.m_y * b));
}

Vector2& operator*(const float a, const Vector2& b) {
	return *(&Vector2(a * b.m_x, a * b.m_y));
}
