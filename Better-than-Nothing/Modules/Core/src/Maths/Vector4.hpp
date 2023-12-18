#pragma once

#include "BetterThanNothing.hpp"

namespace BetterThanNothing
{
	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;

		Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
		Vector4(float value) : x(value), y(value), z(value), w(value) { }
		Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) { }
		Vector4(Vector2& vector) : x(vector.x), y(vector.y), z(0.0f), w(0.0f) { }
		Vector4(Vector3& vector) : x(vector.x), y(vector.y), z(vector.z), w(0.0f) { }
		Vector4(Vector4& vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) { }

		static float Dot(const Vector4& left, const Vector4& right)
		{
			return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
		}

		static f32 Magnitude(const Vector4& right)
		{
			return sqrtf(Dot(right, right));
		}

		static Vector4 Normalize(const Vector4& right)
		{
			f32 magnitude = Magnitude(right);
			return { right.x / magnitude, right.y / magnitude, right.z / magnitude, right.w / magnitude };
		}

		static f32 Distance(const Vector4& left, const Vector4& right)
		{
			return sqrtf(left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w);
		}
	};
};
