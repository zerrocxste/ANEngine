#include "../../ANSDK.h"

anVec3::anVec3() : x(0.f), y(0.f), z(0.f)
{

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

anVec3 anVec3::operator+(anVec3 o)
{
	return anVec3(this->x + o.x, this->y + o.y, this->z + o.z);
}

void anVec3::operator+=(anVec3 o)
{
	this->x += o.x;
	this->y += o.y;
	this->z += o.z;
}
