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
	protected:
		union {
			struct {
				float m_x;
				float m_y;
			};
			float m_values[2];
		};

	public:
		Vector2(void);
		Vector2(float value);
		Vector2(float x, float y);
		Vector2(const Vector2& copy);
		Vector2& operator=(const Vector2& copy);

		Vector2& Set(float x, float y);

		float GetX(void);
		float GetY(void);
		float operator[](unsigned int index);

		Vector2& Normalize(void);
		static Vector2& GetNormalized(const Vector2& vector);

		float Dot(const Vector2& b) const;
		float Angle(const Vector2& b) const;
		float Magnitude(void) const;
		float Distance(const Vector2& b) const;

		static Vector2& Min(const Vector2& a, const Vector2& b);
		static Vector2& Max(const Vector2& a, const Vector2& b);

		Vector2& Add(float x, float y);
		Vector2& Add(Vector2& b);
		static Vector2& Add(const Vector2& a, float x, float y);


		Vector2& Sub(float x, float y);
		Vector2& Sub(Vector2& b);
		static Vector2& Sub(const Vector2& a, float x, float y);

		Vector2& operator+=(const Vector2& b);
		Vector2& operator-=(const Vector2& b);
		Vector2& operator*=(const float b);

		friend bool operator==(const Vector2& a, const Vector2& b);
		friend bool operator!=(const Vector2& a, const Vector2& b);
		friend Vector2& operator+(const Vector2& a, const Vector2& b);
		friend Vector2& operator-(const Vector2& a, const Vector2& b);

		friend Vector2& operator*(const Vector2& a, const float b);
		friend Vector2& operator*(const float a, const Vector2& b);
};
