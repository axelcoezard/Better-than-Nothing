#pragma once

namespace BetterThanNoting
{
	typedef Vector<2, f32> Vector2;
	typedef Vector<3, f32> Vector3;
	typedef Vector<4, f32> Vector4;

	template<u32 size, typename type>
	class Vector
	{
	protected:
		type m_data[size];

	public:
		Vector()
		{
			for (u32 i = 0; i < size; i++)
				m_data[i] = 0;
		}

		Vector(type value)
		{
			for (u32 i = 0; i < size; i++)
				m_data[i] = value;
		}

		Vector(type* data)
		{
			for (u32 i = 0; i < size; i++)
				m_data[i] = data[i];
		}

		Vector(const Vector<size, type>& vector)
		{
			this->operator=(vector);
		}

		Vector<size, type>& operator=(const Vector<size, type>& vector)
		{
			for (u32 i = 0; i < size; i++)
				m_data[i] = vector.m_data[i];
			return *this;
		}

		Vector<size, type>& operator+=(const Vector<size, type>& vector)
		{
			for (u32 i = 0; i < size; i++)
				m_data[i] += vector.m_data[i];
			return *this;
		}

		Vector<size, type>& operator-=(const Vector<size, type>& vector)
		{
			for (u32 i = 0; i < size; i++)
				m_data[i] -= vector.m_data[i];
			return *this;
		}

		f32 Length() const
		{
			f32 result = 0;
			for (u32 i = 0; i < size; i++)
				result += m_data[i] * m_data[i];
			return sqrt(result);
		}

		Vector<size, type>& Normalize()
		{
			f32 length = Length();
			for (u32 i = 0; i < size; i++)
				m_data[i] /= length;
			return *this;
		}

		static f32 Dot(const Vector<size, type>& left, const Vector<size, type>& right)
		{
			f32 result = 0;
			for (u32 i = 0; i < size; i++)
				result += left.m_data[i] * right.m_data[i];
			return result;
		}

		static f32 Angle(const Vector<size, type>& left, const Vector<size, type>& right)
		{
			return acos(Dot(left, right) / (size * size));
		}

		static Vector<size, type> Cross(const Vector<size, type>& left, const Vector<size, type>& right)
		{
			Vector<size, type> result;
			for (u32 i = 0; i < size; i++)
				result.m_data[i] = left.m_data[(i + 1) % size] * right.m_data[(i + 2) % size] - left.m_data[(i + 2) % size] * right.m_data[(i + 1) % size];
			return result;
		}


	};

	template<u32 size, typename type>
	Vector<size, type> operator+(const Vector<size, type>& left, const Vector<size, type>& right)
	{
		return Vector<size, type>(left) += right;
	}

	template<u32 size, typename type>
	Vector<size, type> operator-(const Vector<size, type>& left, const Vector<size, type>& right)
	{
		return Vector<size, type>(left) -= right;
	}

	template<u32 size, typename type>
	Vector<size, type> operator*(const Vector<size, type>& left, const Vector<size, type>& right)
	{
		return Vector<size, type>(left) *= right;
	}

	template<u32 size, typename type>
	bool operator==(const Vector<size, type>& left, const Vector<size, type>& right)
	{
		for (u32 i = 0; i < size; i++)
			if (left.m_data[i] != right.m_data[i])
				return false;
		return true;
	}
};
