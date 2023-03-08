/*
 * File: Vector3.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Wednesday, 8th March 2023 8:28:08 am
 * Last Modified: Wednesday, 8th March 2023 8:31:03 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

class Vector3 {
	private:
		float m_x;
		float m_y;
		float m_z;

	public:
		static Vector3 Zero;
		static Vector3 One;
		static Vector3 Forward;
		static Vector3 Backward;
		static Vector3 Up;
		static Vector3 Down;
		static Vector3 Left;
		static Vector3 Right;

		Vector3(void);
		Vector3(float value);
		Vector3(const Vector3& copy);
		Vector3(float x, float y, float z);
		Vector3& operator=(const Vector3& copy);

		Vector3& Set(float x, float y, float z);

		float GetX(void);
		float GetY(void);
		float GetZ(void);
		float operator[](unsigned int index);

		bool Equals(const Vector3& b) const;
		static bool Compare(const Vector3& a, const Vector3& b);

		Vector3& Scale(float scale);
		static Vector3& Scale(const Vector3& vector, float scale);

		Vector3& GetNormalized(void);
		static Vector3& GetNormalized(const Vector3& vector);

		float Dot(const Vector3& b) const;
		static float Dot(const Vector3& a, const Vector3& b);

		Vector3& Cross(const Vector3& b) const;
		static Vector3& Cross(const Vector3& a, const Vector3& b);

		float Angle(const Vector3& b) const;
		static float Angle(const Vector3& a, const Vector3& b);

		float Magnitude(void) const;
		static float Magnitude(const Vector3& a);

		float Distance(const Vector3& b) const;
		static float Distance(const Vector3& a, const Vector3& b);

		Vector3& Min(const Vector3& b) const;
		static Vector3& Min(const Vector3& a, const Vector3& b);

		Vector3& Max(const Vector3& b) const;
		static Vector3& Max(const Vector3& a, const Vector3& b);

		Vector3& Add(float x, float y, float z);
		Vector3& Add(Vector3& b);
		static Vector3& Add(const Vector3& a, float x, float y, float z);
		static Vector3& Add(const Vector3& a, const Vector3& b);


		Vector3& Sub(float x, float y, float z);
		Vector3& Sub(Vector3& b);
		static Vector3& Sub(const Vector3& a, float x, float y, float z);
		static Vector3& Sub(const Vector3& a, const Vector3& b);

		bool operator==(const Vector3& rhs);
		bool operator!=(const Vector3& rhs);
		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const float& rhs);
		Vector3& operator+(const Vector3& rhs);
		Vector3& operator-(const Vector3& rhs);
		Vector3& operator*(const float& rhs);
};
