#include "../../ANSDK.h"

anVec2::anVec2() : x(0.f), y(0.f)
{

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

anVec2 anVec2::operator+(anVec2 o)
{
	return anVec2(this->x + o.x, this->y + o.y);
}

void anVec2::operator+=(anVec2 o)
{
	this->x += o.x;
	this->y += o.y;
}
