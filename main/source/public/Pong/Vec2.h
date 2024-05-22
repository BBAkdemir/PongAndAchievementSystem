#pragma once

// determines the normal vector of the collision state
enum class CollisionType
{
	None,
	Top,
	Middle,
	Bottom,
	Left,
	Right
};

// keeps data of a collision situation
struct Contact
{
	CollisionType type;
	// In case of collision, it keeps the amount of objects intertwined and corrects the position accordingly.
	float penetration;
};

// The 2D Vector class we wrote was written to facilitate 2D Vector operations.
class Vec2
{
public:
	Vec2() : x(0.0f), y(0.0f) {}

	Vec2(float x, float y) : x(x), y(y) {}

	Vec2 operator+(Vec2 const& rhs)
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2& operator+=(Vec2 const& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vec2 operator*(float rhs)
	{
		return Vec2(x * rhs, y * rhs);
	}

	float x, y;
};