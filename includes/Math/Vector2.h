/*
 * File: Vector2.h
 * Author: Axel Coezard (hello@axelcoezard.com)
 * -----
 * File Created: Wednesday, 8th March 2023 8:28:15 am
 * Last Modified: Wednesday, 8th March 2023 9:24:54 am
 * Modified By: Axel Coezard (hello@axelcoezard.com>)
 */

#pragma once

class Vector2 {
	private:
		float m_x;
		float m_y;

	public:
		Vector2(void);
		Vector2(float value);
		Vector2(const Vector2& copy);
		Vector2(float x, float y);
		Vector2& operator=(const Vector2& copy);

		Vector2& Set(float x, float y);

		float GetX(void);
		float GetY(void);
		float operator[](unsigned int index);

		bool Equals(const Vector2& b) const;
		static bool Compare(const Vector2& a, const Vector2& b);

		Vector2& Scale(float scale);
		static Vector2& Scale(const Vector2& vector, float scale);

		Vector2& GetNormalized(void);
		static Vector2& GetNormalized(const Vector2& vector);

		float Dot(const Vector2& b) const;
		static float Dot(const Vector2& a, const Vector2& b);

		Vector2& Cross(const Vector2& b) const;
		static Vector2& Cross(const Vector2& a, const Vector2& b);

		float Angle(const Vector2& b) const;
		static float Angle(const Vector2& a, const Vector2& b);

		float Magnitude(void) const;
		static float Magnitude(const Vector2& a);

		float Distance(const Vector2& b) const;
		static float Distance(const Vector2& a, const Vector2& b);

		Vector2& Min(const Vector2& b) const;
		static Vector2& Min(const Vector2& a, const Vector2& b);

		Vector2& Max(const Vector2& b) const;
		static Vector2& Max(const Vector2& a, const Vector2& b);

		Vector2& Add(float x, float y);
		Vector2& Add(Vector2& b);
		static Vector2& Add(const Vector2& a, float x, float y);
		static Vector2& Add(const Vector2& a, const Vector2& b);


		Vector2& Sub(float x, float y);
		Vector2& Sub(Vector2& b);
		static Vector2& Sub(const Vector2& a, float x, float y);
		static Vector2& Sub(const Vector2& a, const Vector2& b);

		bool operator==(const Vector2& rhs);
		bool operator!=(const Vector2& rhs);
		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
		Vector2& operator*=(const float& rhs);
		Vector2& operator+(const Vector2& rhs);
		Vector2& operator-(const Vector2& rhs);
		Vector2& operator*(const float& rhs);
};
