#pragma once

class Vec2
{
public:
	float x = 0;
	float y = 0;

	Vec2();
	Vec2(float _x, float _y);

	bool operator == (const Vec2& rhs) const;
	Vec2 operator + (const Vec2& rhs) const;
	Vec2 operator * (const float& val) const;
	void operator += (const Vec2& rhs);
};

