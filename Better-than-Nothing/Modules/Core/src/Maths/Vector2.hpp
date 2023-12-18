#pragma once

namespace BetterThanNoting
{
	struct Vector2
	{
		float x;
		float y;

		Vector2() : x(0.0f), y(0.0f) { }
		Vector2(float value) : x(value), y(value) { }
		Vector2(float x, float y) : x(x), y(y) { }
		Vector2(Vector2& vector) : x(vector.x), y(vector.y) { }

		static float Dot(const Vector2& left, const Vector2& right)
		{
			return left.x * right.x + left.y * right.y;
		}

		static Vector2 Cross(const Vector2& left, const Vector2& right)
		{
			return { left.y * right.x - left.x * right.y, left.x * right.y - left.y * right.x };
		}

		static f32 Magnitude(const Vector2& right)
		{
			return sqrtf(Dot(right, right));
		}

		static Vector2 Normalize(const Vector2& right)
		{
			f32 magnitude = Magnitude(right);
			return { right.x / magnitude, right.y / magnitude };
		}

		static f32 Distance(const Vector2& left, const Vector2& right)
		{
			return sqrtf(left.x * right.x + left.y * right.y);
		}
	};
};
