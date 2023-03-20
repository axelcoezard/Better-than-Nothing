/*
 * File: Matrix.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Tuesday, 7th March 2023 10:44:10 pm
 * Last Modified: Tuesday, 7th March 2023 10:44:21 pm
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

#include "Math/Vector3.h"

class Matrix {
	protected:
		float m_values[16];

	public:
		Matrix(void);
		Matrix(const float copy[16]);
		Matrix(float m00, float m01, float m02, float m03,
				float m04, float m05, float m06, float m07,
				float m08, float m09, float m10, float m11,
				float m12, float m13, float m14, float m15);
		Matrix(const Matrix& copy);
		Matrix& operator=(const Matrix& copy);

		void Set(const float copy[16]);
		void Set(float m00, float m01, float m02, float m03,
				float m04, float m05, float m06, float m07,
				float m08, float m09, float m10, float m11,
				float m12, float m13, float m14, float m15);

		void Set(unsigned int index, float value);
		void Set(unsigned int column, unsigned int row, float value);
		void SetColumn(unsigned int index, const Vector3& column);

		float Get(unsigned int index) const;
		float Get(unsigned int column, unsigned int row) const;
		float operator[](unsigned int index) const;

		static void Identity(Matrix& matrix);

		Matrix& Transpose(void) const;
		static Matrix& GetTransposed(const Matrix& matrix);

		Matrix& Reverse(void) const;
		static Matrix& GetReversed(const Matrix& matrix);

		Matrix& RotateX(float angle);
		Matrix& RotateY(float angle);
		Matrix& RotateZ(float angle);

		Matrix& Scale(float scaleX, float scaleY, float scaleZ);
		Matrix& Translate(float x, float y, float z);

		static Matrix& LookAt(Vector3& position, Vector3& target, Vector3& up);
		static Matrix& GetFrustrum(float left, float right, float bottom, float top, float near, float far);
		static Matrix& GetOrtho(float left, float right, float bottom, float top, float near, float far);
		static Matrix& GetPerspective(float fov, float aspect, float near, float far);

		Matrix& operator+=(const Matrix& b);
		Matrix& operator-=(const Matrix& b);
		Matrix& operator*=(const float b);
		Matrix& operator*=(const Matrix& b);

		friend bool operator==(const Matrix& a, const Matrix& b);
		friend bool operator!=(const Matrix& a, const Matrix& b);
		friend Matrix& operator+(const Matrix& a, const Matrix& b);
		friend Matrix& operator-(const Matrix& a, const Matrix& b);

		friend Matrix& operator*(const Matrix& a, const float b);
		friend Matrix& operator*(const float a, const Matrix& b);
		friend Matrix& operator*(const Matrix& a, const Matrix& b);
};
