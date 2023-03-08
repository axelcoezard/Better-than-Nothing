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
		union {
			struct {
				float m_x;
				float m_y;
				float m_z;
			};
			float m_coords[2];
		};

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
		Vector3(float x, float y, float z);
		Vector3(const Vector3& copy);
		Vector3& operator=(const Vector3& copy);

		Vector3& Set(float x, float y, float z);

		float GetX(void);
		float GetY(void);
		float GetZ(void);
		float operator[](unsigned int index);

		Vector3& Normalize(void);
		static Vector3& GetNormalized(const Vector3& vector);

		float Dot(const Vector3& b) const;
		Vector3& Cross(const Vector3& b) const;
		float Angle(const Vector3& b) const;
		float Magnitude(void) const;
		float Distance(const Vector3& b) const;

		static Vector3& Min(const Vector3& a, const Vector3& b);
		static Vector3& Max(const Vector3& a, const Vector3& b);

		Vector3& Add(float x, float y, float z);
		Vector3& Add(Vector3& b);
		static Vector3& Add(const Vector3& a, float x, float y, float z);


		Vector3& Sub(float x, float y, float z);
		Vector3& Sub(Vector3& b);
		static Vector3& Sub(const Vector3& a, float x, float y, float z);

		Vector3& operator+=(const Vector3& b);
		Vector3& operator-=(const Vector3& b);
		Vector3& operator*=(const float& b);

		friend bool operator==(const Vector3& a, const Vector3& b);
		friend bool operator!=(const Vector3& a, const Vector3& b);
		friend Vector3& operator+(const Vector3& a, const Vector3& b);
		friend Vector3& operator-(const Vector3& a, const Vector3& b);

		friend Vector3& operator*(const Vector3& a, const float b);
		friend Vector3& operator*(const float a, const Vector3& b);
};
