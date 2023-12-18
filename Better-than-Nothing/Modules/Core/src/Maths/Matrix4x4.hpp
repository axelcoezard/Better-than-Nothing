#pragma once

#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	struct Matrix4x4
	{
		float m00, m01, m02, m03; // mRowColumn
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;

		Matrix4x4()
			:	m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f),
				m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f),
				m20(0.0f), m21(0.0f), m22(1.0f), m23(0.0f),
				m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f) {}

		Matrix4x4(float m00, float m01, float m02, float m03,
				  float m10, float m11, float m12, float m13,
				  float m20, float m21, float m22, float m23,
				  float m30, float m31, float m32, float m33)
			:	m00(m00), m01(m01), m02(m02), m03(m03),
				m10(m10), m11(m11), m12(m12), m13(m13),
				m20(m20), m21(m21), m22(m22), m23(m23),
				m30(m30), m31(m31), m32(m32), m33(m33) {}

		Matrix4x4(const Matrix4x4& other)
			:	m00(other.m00), m01(other.m01), m02(other.m02), m03(other.m03),
				m10(other.m10), m11(other.m11), m12(other.m12), m13(other.m13),
				m20(other.m20), m21(other.m21), m22(other.m22), m23(other.m23),
				m30(other.m30), m31(other.m31), m32(other.m32), m33(other.m33) {}

		Matrix4x4 operator*(const Matrix4x4& other) const
		{
			return {
				m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30,
				m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31,
				m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32,
				m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33,
				m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30,
				m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31,
				m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32,
				m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33,
				m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30,
				m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31,
				m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32,
				m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33,
				m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30,
				m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31,
				m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32,
				m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33
			};
		}

		static Matrix4x4 Identity()
		{
			return { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
		}

		static Matrix4x4 Zero()
		{
			return { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
		}

		static Matrix4x4 Translate(float x, float y, float z)
		{
			return {
				1.0f, 0.0f, 0.0f, x,
				0.0f, 1.0f, 0.0f, y,
				0.0f, 0.0f, 1.0f, z,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		static Matrix4x4 Translate(Vector3& translation)
		{
			return Translate(translation.x, translation.y, translation.z);
		}

		static Matrix4x4 Translate(const Matrix4x4& matrix, float x, float y, float z)
		{
			return matrix * Translate(x, y, z);
		}

		static Matrix4x4 Translate(const Matrix4x4& matrix, Vector3& translation)
		{
			return matrix * Translate(translation);
		}

		static Matrix4x4 Scale(float x, float y, float z)
		{
			return {
				x, 0.0f, 0.0f, 0.0f,
				0.0f, y, 0.0f, 0.0f,
				0.0f, 0.0f, z, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
			};
		}

		static Matrix4x4 Scale(float uniformScale)
		{
			return Scale(uniformScale, uniformScale, uniformScale);
		}


		static Matrix4x4 Scale(Vector3& scale)
		{
			return Scale(scale.x, scale.y, scale.z);
		}

		static Matrix4x4 Scale(const Matrix4x4& matrix, float x, float y, float z)
		{
			return matrix * Scale(x, y, z);
		}

		static Matrix4x4 Scale(const Matrix4x4& matrix, Vector3& scale)
		{
			return matrix * Scale(scale);
		}

	};
};
