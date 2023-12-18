#pragma once

namespace BetterThanNoting
{
	struct Vector2
	{
		float x;
		float y;

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
	};

	Vector2 operator*(float scale, const Vector2& vector)
	{
		return { vector.x * scale, vector.y * scale };
	}

	Vector2 operator*(const Vector2& vector, float scale)
	{
		return { vector.x * scale, vector.y * scale };
	}

	Vector2 operator/(const Vector2& vector, float scale)
	{
		return { vector.x / scale, vector.y / scale };
	}

	Vector2 operator+(const Vector2& left, const Vector2& right)
	{
		return { left.x + right.x, left.y + right.y };
	}

	Vector2 operator-(const Vector2& left, const Vector2& right)
	{
		return { left.x - right.x, left.y - right.y };
	}

	struct Vector3
	{
		float x;
		float y;
		float z;

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
	};

	Vector3 operator*(float scale, const Vector3& vector)
	{
		return { vector.x * scale, vector.y * scale, vector.z * scale };
	}

	Vector3 operator*(const Vector3& vector, float scale)
	{
		return { vector.x * scale, vector.y * scale, vector.z * scale };
	}

	Vector3 operator/(const Vector3& vector, float scale)
	{
		return { vector.x / scale, vector.y / scale, vector.z / scale };
	}

	Vector3 operator+(const Vector3& left, const Vector3& right)
	{
		return { left.x + right.x, left.y + right.y, left.z + right.z };
	}

	Vector3 operator-(const Vector3& left, const Vector3& right)
	{
		return { left.x - right.x, left.y - right.y, left.z - right.z };
	}

	struct Vector4
	{
		float x;
		float y;
		float z;
		float w;

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
	};
};
