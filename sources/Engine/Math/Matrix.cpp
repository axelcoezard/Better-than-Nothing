/*
 * File: Matrix.cpp
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Wednesday, 8th March 2023 3:32:32 pm
 * Last Modified: Wednesday, 8th March 2023 3:32:39 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#include <stdexcept>
#include <cmath>
#include "Math/Matrix.h"

Matrix::Matrix(void) {

}

Matrix::Matrix(const float copy[16]) {

}

Matrix::Matrix(float m00, float m01, float m02, float m03,
				float m04, float m05, float m06, float m07,
				float m08, float m09, float m10, float m11,
				float m12, float m13, float m14, float m15) {
	this->Set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
}

Matrix::Matrix(const Matrix& copy) {
	*this = copy;
}

Matrix& Matrix::operator=(const Matrix& copy) {
	this->Set(copy.m_values);
}

void Matrix::Set(const float copy[16]) {
	m_values[0] = copy[0];
	m_values[1] = copy[1];
	m_values[2] = copy[2];
	m_values[3] = copy[3];
	m_values[4] = copy[4];
	m_values[5] = copy[5];
	m_values[6] = copy[6];
	m_values[7] = copy[7];
	m_values[8] = copy[8];
	m_values[9] = copy[9];
	m_values[10] = copy[10];
	m_values[11] = copy[11];
	m_values[12] = copy[12];
	m_values[13] = copy[13];
	m_values[14] = copy[14];
	m_values[15] = copy[15];
}

void Matrix::Set(float m00, float m01, float m02, float m03,
				float m04, float m05, float m06, float m07,
				float m08, float m09, float m10, float m11,
				float m12, float m13, float m14, float m15) {
	m_values[0] = m00;
	m_values[1] = m01;
	m_values[2] = m02;
	m_values[3] = m03;
	m_values[4] = m04;
	m_values[5] = m05;
	m_values[6] = m06;
	m_values[7] = m07;
	m_values[8] = m08;
	m_values[9] = m09;
	m_values[10] = m10;
	m_values[11] = m11;
	m_values[12] = m12;
	m_values[13] = m13;
	m_values[14] = m14;
	m_values[15] = m15;
}

void Matrix::Set(unsigned int index, float value) {
	if (index > 15) {
		throw new std::runtime_error("Matrix index out of bounds exception");
	}
	m_values[index] = value;
}

void Matrix::Set(unsigned int column, unsigned int row, float value) {
	this->Set(column + 4 * row, value);
}

void Matrix::SetColumn(unsigned int index, const Vector3& column) {
	m_values[index * 4]     = column.m_x;
	m_values[index * 4 + 1] = column.m_y;
	m_values[index * 4 + 2] = column.m_z;
}

float Matrix::Get(unsigned int index) const {
	if (index > 15) {
		throw new std::runtime_error("Matrix index out of bounds exception");
	}
	return m_values[index];
}

float Matrix::Get(unsigned int column, unsigned int row) const {
	return this->Get(column + 4 * row);
}

float Matrix::operator[](unsigned int index) const {
	return this->Get(index);
}

void Matrix::Identity(Matrix& matrix) {
	matrix.m_values[0]  = 1.0f;
	matrix.m_values[1]  = 0.0f;
	matrix.m_values[2]  = 0.0f;
	matrix.m_values[3]  = 0.0f;

	matrix.m_values[4]  = 0.0f;
	matrix.m_values[5]  = 1.0f;
	matrix.m_values[6]  = 0.0f;
	matrix.m_values[7]  = 0.0f;

	matrix.m_values[8]  = 0.0f;
	matrix.m_values[9]  = 0.0f;
	matrix.m_values[10] = 1.0f;
	matrix.m_values[11] = 0.0f;

	matrix.m_values[12] = 0.0f;
	matrix.m_values[13] = 0.0f;
	matrix.m_values[14] = 0.0f;
	matrix.m_values[15] = 1.0f;
}

Matrix& Matrix::Transpose(void) const {
	// TODO: Transpose current Matrix without for loop
}

Matrix& Matrix::GetTransposed(const Matrix& matrix) {
	// TODO: Transpose arg Matrix without for loop
}

Matrix& Matrix::Reverse(void) const {
	// TODO: Reverse current Matrix without for loop
}

Matrix& Matrix::GetReversed(const Matrix& matrix) {
	// TODO: Reverse arg Matrix without for loop
}

Matrix& Matrix::RotateX(float angle) {
	float s = sinf(angle);
	float c = cosf(angle);

	float m1 = m_values[1];
	float m2 = m_values[2];
	float m5 = m_values[5];
	float m6 = m_values[6];
	float m9 = m_values[9];
	float m10 = m_values[10];
	float m13 = m_values[13];
	float m14 = m_values[14];

	m_values[1] = m1 * c + m2 * -s;
	m_values[2] = m1 * s + m2 * c;
	m_values[5] = m5 * c + m6 * -s;
	m_values[6] = m5 * s + m6 * c;
	m_values[9] = m9 * c + m10 * -s;
	m_values[10] = m9 * s + m10 * c;
	m_values[13] = m13 * c + m14 * -s;
	m_values[14] = m13 * s + m14 * c;
	return *this;
}

Matrix& Matrix::RotateY(float angle) {
	float s = sinf(angle);
	float c = cosf(angle);

	float m0 = m_values[0];
	float m2 = m_values[2];
	float m4 = m_values[4];
	float m6 = m_values[6];
	float m8 = m_values[8];
	float m10 = m_values[10];
	float m12 = m_values[12];
	float m14 = m_values[14];

	m_values[0] = m0 * c + m2 * s;
	m_values[2] = m0 * -s + m2 * c;
	m_values[4] = m4 * c + m6 * s;
	m_values[6] = m4 * -s + m6 * c;
	m_values[8] = m8 * c + m10 * s;
	m_values[10] = m8 * -s + m10 * c;
	m_values[12] = m12 * c + m14 * s;
	m_values[14] = m12 * -s + m14 * c;
	return *this;
}

Matrix& Matrix::RotateZ(float angle) {
	float s = sinf(angle);
	float c = cosf(angle);

	float m0 = m_values[0];
	float m1 = m_values[1];
	float m4 = m_values[4];
	float m5 = m_values[5];
	float m8 = m_values[8];
	float m9 = m_values[9];
	float m12 = m_values[12];
	float m13 = m_values[13];

	m_values[0] = m0 * c + m1 * -s;
	m_values[1] = m0 * s + m1 * c;
	m_values[4] = m4 * c + m5 * -s;
	m_values[5] = m4 * s + m5 * c;
	m_values[8] = m8 * c + m9 * -s;
	m_values[9] = m8 * s + m9 * c;
	m_values[12] = m12 * c + m13 * -s;
	m_values[13] = m12 * s + m13 * c;
	return *this;
}

Matrix& Matrix::Scale(float scaleX, float scaleY, float scaleZ) {
	m_values[0]  *= scaleX;
	m_values[4]  *= scaleX;
	m_values[8]  *= scaleX;
	m_values[12] *= scaleX;
	m_values[1]  *= scaleY;
	m_values[5]  *= scaleY;
	m_values[9]  *= scaleY;
	m_values[13] *= scaleY;
	m_values[2]  *= scaleZ;
	m_values[6]  *= scaleZ;
	m_values[10] *= scaleZ;
	m_values[14] *= scaleZ;
	return *this;
}

Matrix& Matrix::Translate(float x, float y, float z) {
	m_values[0]  += m_values[3]  * x;
	m_values[4]  += m_values[7]  * x;
	m_values[8]  += m_values[11] * x;
	m_values[12] += m_values[15] * x;
	m_values[1]  += m_values[3]  * y;
	m_values[5]  += m_values[7]  * y;
	m_values[9]  += m_values[11] * y;
	m_values[13] += m_values[15] * y;
	m_values[2]  += m_values[3]  * z;
	m_values[6]  += m_values[7]  * z;
	m_values[10] += m_values[11] * z;
	m_values[14] += m_values[15] * z;
	return *this;
}

Matrix& Matrix::LookAt(Vector3& position, Vector3& target, Vector3& up) {
	Vector3 eyeDirection = (target - position).Normalize();
	Vector3 leftDirection = up.Cross(eyeDirection).Normalize();
	Vector3 upDirection = eyeDirection.Cross(leftDirection).Normalize();

	Matrix lookAt;
	lookAt.SetColumn(0, leftDirection);
	lookAt.SetColumn(1, upDirection);
	lookAt.SetColumn(2, eyeDirection);
	lookAt.SetColumn(3, position);
	return lookAt;
}

Matrix& Matrix::GetFrustrum(float left, float right, float bottom, float top, float near, float far) {
	Matrix matrix;
	matrix.m_values[0]  = 2.0f * near / (right - left);
	matrix.m_values[5]  = 2.0f * near / (top - bottom);
	matrix.m_values[8]  = (right + left) / (right - left);
	matrix.m_values[9]  = (top + bottom) / (top - bottom);
	matrix.m_values[10] = -(far + near) / (far - near);
	matrix.m_values[11] = -1.0f;
	matrix.m_values[14] = -(2.0f * far * near) / (far - near);
	matrix.m_values[15] = 0.0f;
	return matrix;
}

Matrix& Matrix::GetOrtho(float left, float right, float bottom, float top, float near, float far) {
	Matrix matrix;
	matrix.m_values[0]  = 2.0f / (right - left);
	matrix.m_values[5]  = 2.0f / (top - bottom);
	matrix.m_values[10] = -2.0f / (far - near);
	matrix.m_values[12] = -(right + left) / (right - left);
	matrix.m_values[13] = -(top + bottom) / (top - bottom);
	matrix.m_values[14] = -(far + near) / (far - near);
	return matrix;
}

Matrix& Matrix::GetPerspective(float fov, float aspect, float near, float far) {
	float tangent = tanf(fov / 2.0f);
	float height = near * tangent;
	float width = height * aspect;
	return GetFrustrum(-width, width, -height, height, near, far);
}

Matrix& Matrix::operator+=(const Matrix& b) {
	return *this = *this + b;
}

Matrix& Matrix::operator-=(const Matrix& b) {
	return *this = *this - b;
}

Matrix& Matrix::operator*=(const float b) {
	return *this = *this * b;
}

Matrix& Matrix::operator*=(const Matrix& b) {
	return *this = *this * b;
}

bool operator==(const Matrix& a, const Matrix& b) {
	return  a[0] == b[0]  &&  a[1] ==  a[1] &&  a[2] == a[2]  &&  a[3] == a[3]
		&&  a[4] == b[4]  &&  a[5] ==  a[5] &&  a[6] == a[6]  &&  a[7] == a[7]
		&&  a[8] == b[8]  &&  a[9] ==  a[9] && a[10] == a[10] && a[11] == a[11]
		&& a[12] == b[12] && a[13] == a[13] && a[14] == a[14] && a[15] == a[15];
}

bool operator!=(const Matrix& a, const Matrix& b) {
	return  a[0] != b[0]  ||  a[1] !=  a[1] ||  a[2] != a[2]  ||  a[3] != a[3]
		||  a[4] != b[4]  ||  a[5] !=  a[5] ||  a[6] != a[6]  ||  a[7] != a[7]
		||  a[8] != b[8]  ||  a[9] !=  a[9] || a[10] != a[10] || a[11] != a[11]
		|| a[12] != b[12] || a[13] != a[13] || a[14] != a[14] || a[15] != a[15];
}

Matrix& operator+(const Matrix& a, const Matrix& b) {
	return *(&Matrix(
		a[0]  +  b[0],  a[1] +  a[1],  a[2] +  a[2],  a[3] +  a[3],
		a[4]  +  b[4],  a[5] +  a[5],  a[6] +  a[6],  a[7] +  a[7],
		a[8]  +  b[8],  a[9] +  a[9], a[10] + a[10], a[11] + a[11],
		a[12] + b[12], a[13] + a[13], a[14] + a[14], a[15] + a[15]
	));
}

Matrix& operator-(const Matrix& a, const Matrix& b) {
	return *(&Matrix(
		a[0]  -  b[0],  a[1] -  a[1],  a[2] -  a[2],  a[3] -  a[3],
		a[4]  -  b[4],  a[5] -  a[5],  a[6] -  a[6],  a[7] -  a[7],
		a[8]  -  b[8],  a[9] -  a[9], a[10] - a[10], a[11] - a[11],
		a[12] - b[12], a[13] - a[13], a[14] - a[14], a[15] - a[15]
	));
}

Matrix& operator*(const Matrix& a, const float b) {
	return *(&Matrix(
		a[0]  * b,  a[1] * b,  a[2] * b,  a[3] * b,
		a[4]  * b,  a[5] * b,  a[6] * b,  a[7] * b,
		a[8]  * b,  a[9] * b, a[10] * b, a[11] * b,
		a[12] * b, a[13] * b, a[14] * b, a[15] * b
	));
}

Matrix& operator*(const float a, const Matrix& b) {
	*(&Matrix(
		a * b[0],  a * b[1],  a * b[2],  a * b[3],
		a * b[4],  a * b[5],  a * b[6],  a * b[7],
		a * b[8],  a * b[9],  a * b[10], a * b[11],
		a * b[12], a * b[13], a * b[14], a * b[15]
	));
}

Matrix& operator*(const Matrix& a, const Matrix& b) {
	return *(&Matrix(
		a[0] * b[0]  + a[4] * b[1]  + a[8]  * b[2]  + a[12] * b[3],
		a[1] * b[0]  + a[5] * b[1]  + a[9]  * b[2]  + a[13] * b[3],
		a[2] * b[0]  + a[6] * b[1]  + a[10] * b[2]  + a[14] * b[3],
		a[3] * b[0]  + a[7] * b[1]  + a[11] * b[2]  + a[15] * b[3],
		a[0] * b[4]  + a[4] * b[5]  + a[8]  * b[6]  + a[12] * b[7],
		a[1] * b[4]  + a[5] * b[5]  + a[9]  * b[6]  + a[13] * b[7],
		a[2] * b[4]  + a[6] * b[5]  + a[10] * b[6]  + a[14] * b[7],
		a[3] * b[4]  + a[7] * b[5]  + a[11] * b[6]  + a[15] * b[7],
		a[0] * b[8]  + a[4] * b[9]  + a[8]  * b[10] + a[12] * b[11],
		a[1] * b[8]  + a[5] * b[9]  + a[9]  * b[10] + a[13] * b[11],
		a[2] * b[8]  + a[6] * b[9]  + a[10] * b[10] + a[14] * b[11],
		a[3] * b[8]  + a[7] * b[9]  + a[11] * b[10] + a[15] * b[11],
		a[0] * b[12] + a[4] * b[13] + a[8]  * b[14] + a[12] * b[15],
		a[1] * b[12] + a[5] * b[13] + a[9]  * b[14] + a[13] * b[15],
		a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15],
		a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15]
	));
}
