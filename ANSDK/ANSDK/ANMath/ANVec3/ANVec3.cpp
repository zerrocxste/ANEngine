#include "../../ANSDK.h"

anVec3::anVec3() : x(0.f), y(0.f), z(0.f)
{

}

anVec3::anVec3(float all)
{
	this->x = this->y = this->z = all;
}

anVec3::anVec3(float X, float Y, float Z) : x(X), y(Y), z(Z)
{

}

anVec3::~anVec3()
{

}

bool anVec3::operator==(anVec3 o)
{
	return this->x == o.x && this->y == o.y && this->z == o.z;
}

bool anVec3::operator!=(anVec3 o)
{
	return !operator==(o);
}

anVec3& anVec3::operator=(anVec3 o)
{
	this->x = o.x;
	this->y = o.y;
	this->z = o.z;

	return *this;
}

anVec3& anVec3::operator=(float o)
{
	this->x = this->y = this->z = o;

	return *this;
}

anVec3 anVec3::operator+(anVec3 o)
{
	return anVec3(this->x + o.x, this->y + o.y, this->z + o.z);
}

anVec3& anVec3::operator+=(anVec3 o)
{
	this->x += o.x;
	this->y += o.y;
	this->z += o.z;

	return *this;
}

anVec3 anVec3::operator+(float o)
{
	return anVec3(this->x + o, this->y + o, this->z + o);
}

anVec3& anVec3::operator+=(float o)
{
	this->x += o;
	this->y += o;
	this->z += o;

	return *this;
}

anVec3 anVec3::operator-(anVec3 o)
{
	return anVec3(this->x - o.x, this->y - o.y, this->z - o.z);
}

anVec3& anVec3::operator-=(anVec3 o)
{
	this->x -= o.x;
	this->y -= o.y;
	this->z -= o.z;

	return *this;
}

anVec3 anVec3::operator-(float o)
{
	return anVec3(this->x - o, this->y - o, this->z - o);
}

anVec3& anVec3::operator-=(float o)
{
	this->x -= o;
	this->y -= o;
	this->z -= o;

	return *this;
}

void anVec3::Clear()
{
	this->x = this->y = this->z = 0.f;
}
