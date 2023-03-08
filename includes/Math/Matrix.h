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
	private:
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

		float operator[](unsigned int index) const;
		float Get(unsigned int index) const;
		float Get(unsigned int column, unsigned int row) const;

		bool Equals(const Matrix& other) const;

		static void Identity(Matrix& matrix);

		Matrix& GetTransposed(void) const;
		static Matrix& GetTransposed(const Matrix& matrix);

		Matrix& GetReversed(void) const;
		static Matrix& GetReversed(const Matrix& matrix);

		Matrix& GetCopy(void) const;
		static Matrix& GetCopy(const Matrix& matrix);

		Matrix& Add(const Matrix& b);
		static Matrix& Add(const Matrix& a, const Matrix& b);

		Matrix& Sub(const Matrix& b);
		static Matrix& Sub(const Matrix& a, const Matrix& b);

		Matrix& Mul(const Matrix& b);
		static Matrix& Mul(const Matrix& a, const Matrix& b);

		Matrix& RotateX(float angle);
		static void RotateX(Matrix& matrix, float angle);

		Matrix& RotateY(float angle);
		static void RotateY(Matrix& matrix, float angle);

		Matrix& RotateZ(float angle);
		static void RotateZ(Matrix& matrix, float angle);

		Matrix& Scale(const float s);
		static void Scale(Matrix& matrix, float scale);
		static void Scale(Matrix& matrix, float scaleX, float scaleY, float scaleZ);

		Matrix& Translate(float x, float y, float z);
		static void Translate(Matrix& matrix, float x, float y, float z);
		static Matrix LookAt(Vector3& position, Vector3& target, Vector3& up);

		static Matrix& GetFrustrum(float left, float right, float bottom, float top, float near, float far);
		static Matrix& GetOrtho(float left, float right, float bottom, float top, float near, float far);
		static Matrix& GetPerspective(float fov, float aspect, float near, float far);

		bool operator==(const Matrix& rhs);
		bool operator!=(const Matrix& rhs);
		Matrix& operator+(const Matrix& rhs);
		Matrix& operator-(const Matrix& rhs);
		Matrix& operator*(const Matrix& rhs);
};
