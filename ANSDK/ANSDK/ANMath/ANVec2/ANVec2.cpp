#include "../../ANSDK.h"

anVec2::anVec2() : x(0.f), y(0.f)
{

}

anVec2::anVec2(float all)
{
	this->x = this->y = all;
}

anVec2::anVec2(float X, float Y) : x(X), y(Y)
{

}

anVec2::~anVec2()
{

}

bool anVec2::operator==(anVec2 o)
{
	return this->x == o.x && this->y == o.y;
}

bool anVec2::operator!=(anVec2 o)
{
	return !operator==(o);
}

anVec2& anVec2::operator=(anVec2 o)
{
	this->x = o.x;
	this->y = o.y;

	return *this;
}

anVec2& anVec2::operator=(float o)
{
	this->x = this->y = o;

	return *this;
}

anVec2 anVec2::operator+(anVec2 o)
{
	return anVec2(this->x + o.x, this->y + o.y);
}

anVec2& anVec2::operator+=(anVec2 o)
{
	this->x += o.x;
	this->y += o.y;

	return *this;
}

anVec2& anVec2::operator+=(float o)
{
	this->x += o;
	this->y += o;

	return *this;
}

anVec2 anVec2::operator+(float o)
{
	return anVec2(this->x + o, this->y + o);
}

anVec2 anVec2::operator-(anVec2 o)
{
	return anVec2(this->x - o.x, this->y - o.y);
}

anVec2& anVec2::operator-=(anVec2 o)
{
	this->x -= o.x;
	this->y -= o.y;

	return *this;
}

anVec2& anVec2::operator-=(float o)
{
	this->x -= o;
	this->y -= o;

	return *this;
}

anVec2 anVec2::operator-(float o)
{
	return anVec2(this->x - o, this->y - o);
}

anVec2 anVec2::operator*(anVec2 o)
{
	return anVec2(this->x * o.x, this->y * o.y);
}

anVec2& anVec2::operator*=(anVec2 o)
{
	this->x *= o.x;
	this->y *= o.y;

	return *this;
}

anVec2& anVec2::operator*=(float o)
{
	this->x *= o;
	this->y *= o;

	return *this;
}

anVec2 anVec2::operator*(float o)
{
	return anVec2(this->x * o, this->y * o);
}

anVec2 anVec2::operator/(anVec2 o)
{
	return anVec2(this->x / o.x, this->y / o.y);
}

anVec2& anVec2::operator/=(anVec2 o)
{
	this->x /= o.x;
	this->y /= o.y;

	return *this;
}

anVec2& anVec2::operator/=(float o)
{
	this->x /= o;
	this->y /= o;

	return *this;
}

anVec2 anVec2::operator/(float o)
{
	return anVec2(this->x / o, this->y / o);
}

anVec2 anVec2::Inverse()
{
	return anVec2(-this->x, -this->y);
}

void anVec2::Clear()
{
	this->x = this->y = 0.f;
}
