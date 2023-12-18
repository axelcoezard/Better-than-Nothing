#pragma once

#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	struct Vector3
	{
		float x;
		float y;
		float z;

		Vector3() : x(0.0f), y(0.0f), z(0.0f) { }
		Vector3(float value) : x(value), y(value), z(value) { }
		Vector3(float x, float y, float z) : x(x), y(y), z(z) { }
		Vector3(Vector2& vector) : x(vector.x), y(vector.y), z(0.0f) { }
		Vector3(Vector3& vector) : x(vector.x), y(vector.y), z(vector.z) { }

		static float Dot(const Vector3& left, const Vector3& right)
		{
			return left.x * right.x + left.y * right.y + left.z * right.z;
		}

		static Vector3 Cross(const Vector3& left, const Vector3& right)
		{
			return { left.y * right.z - left.z * right.y, left.z * right.x - left.x * right.z, left.x * right.y - left.y * right.x };
		}

		static f32 Magnitude(const Vector3& right)
		{
			return sqrtf(Dot(right, right));
		}

		static Vector3 Normalize(const Vector3& right)
		{
			f32 magnitude = Magnitude(right);
			return { right.x / magnitude, right.y / magnitude, right.z / magnitude };
		}

		static f32 Distance(const Vector3& left, const Vector3& right)
		{
			return sqrtf(left.x * right.x + left.y * right.y + left.z * right.z);
		}
	};
};
